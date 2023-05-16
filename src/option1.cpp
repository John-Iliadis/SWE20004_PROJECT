/*
 * File option1.cpp
 * Created on 3/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 * */

#include "../include/option1.hpp"

void option1()
{
    std::ifstream patient_details("../patient_details.txt");
    std::ifstream symptoms_file("../symptoms.txt");
    std::ifstream high_risk_loc_file("../high_risk_covid_locations.txt");

    // checking if all files are opened
    if (patient_details.fail() || symptoms_file.fail() || high_risk_loc_file.fail())
        throw std::runtime_error("Option1() - Failed to open all files");

    // checking if symptoms database is populated
    if (empty_database(symptoms_file))
    {
        std::cout << "UNABLE TO RECOMMEND COVID TEST - SYMPTOMS DATABASE EMPTY\n";
        patient_details.close();
        symptoms_file.close();
        high_risk_loc_file.close();
        return;
    }

    PatientRecord record;
    get_id(patient_details, record);
    get_name(record);
    get_dob(record);
    get_address(record);
    get_overseas_travel(record);
    pick_symptoms(record, symptoms_file);
    pick_high_risk_visited_locations(record, high_risk_loc_file);
    record.visited_location = "null";
    record.covid_test = "null";
    record.status = "null";

    patient_details.close();
    symptoms_file.close();
    high_risk_loc_file.close();

    // insert the new record in the database
    insert_patient_record(record, "../patient_details.txt");

    // finally recommend a test
    recommend_covid_test(record);
}

void get_id(std::ifstream& file, PatientRecord& record)
{
    std::cout << "Enter patient id:";
    std::getline(std::cin, record.id);

    // id must be unique and numeric
    while (check_id_exists(file, record.id) || !is_num(record.id))
    {
        std::cout << "\nPATIENT ID SHOULD BE NUMERIC AND UNIQUE\n";
        std::cout << "Enter patient id:";
        std::getline(std::cin, record.id);
    }
}

void get_name(PatientRecord& record)
{
    std::regex reg("^[a-zA-Z ]{1,50}$");

    std::cout << "Enter full name:";
    std::getline(std::cin, record.name);

    while (!std::regex_match(record.name, reg))
    {
        std::cout << "\nINVALID NAME : Name should only contain letters and have 1-50 length\n";
        std::cout << "Enter full name:";
        std::getline(std::cin, record.name);
    }
}

void get_dob(PatientRecord& record)
{
    std::cout << "Enter date of birth in this format (dd-mm-yyyy):";
    std::getline(std::cin, record.dob);

    while (!check_date_format(record.dob))
    {
        std::cout << "\nDATE FORMAT SHOULD BE (dd-mm-yyyy)\n";
        std::cout << "Enter date of birth in this format (dd-mm-yyyy):";
        std::getline(std::cin, record.dob);
    }
}

void get_address(PatientRecord& record)
{
    std::regex reg("^[a-zA-Z0-9,\\s]{1,255}");

    std::cout << "Enter address:";
    std::getline(std::cin, record.address);

    while (!std::regex_match(record.address, reg))
    {
        std::cout << "\nINVALID ADDRESS : No special characters are allowed and length should be 1-255\n";
        std::cout << "Enter address:";
        std::getline(std::cin, record.address);
    }
}

void get_overseas_travel(PatientRecord& record)
{
    std::cout << "Enter last overseas travel date in this format (dd-mm-yyyy):";
    std::getline(std::cin, record.last_overseas_travel);

    while (!check_date_format(record.last_overseas_travel))
    {
        std::cout << "\nDATE FORMAT SHOULD BE (dd-mm-yyyy)\n";
        std::cout << "Enter last overseas travel date in this format (dd-mm-yyyy):";
        std::getline(std::cin, record.last_overseas_travel);
    }
}

void pick_symptoms(PatientRecord& record, std::ifstream& file)
{
    std::string line;

    // map that stores the id that points to the symptom name and risk
    std::unordered_map<int, std::pair<std::string, std::string>> symptoms_map;
    int id = 1;

    std::cout << "\nSymptoms List:\n";

    // Printing out all the symptoms and adding them to the map
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string symptom;
        std::string risk;
        std::getline(ss, symptom, ';');
        std::getline(ss, risk);
        symptoms_map[id] = std::make_pair(symptom, risk);

        std::cout << id << " - " << str_toupper(symptom) << '\n';
        id++;
    }

    std::cout << "Select all the experienced symptoms, if any. Separate them with a comma (ie 2,5,8)\n"
              << "-->";

    std::getline(std::cin, line);

    if (line == "") return; // if there is no input, the patient has no symptoms

    std::regex reg("^[0-9,]*$");
    while (!std::regex_match(line, reg))
    {
        std::cout << "\nINVALID INPUT : Only numbers and commas allowed\n";
        std::cout << "Select all the experienced symptoms, if any. Separate them with a comma (ie 2,5,8)\n"
                  << "-->";

        std::getline(std::cin, line);
        if (line == "") return;
    }

    std::stringstream ss(line);
    std::string num;
    std::vector<int> selected_symptoms;

    // validating input
    while (std::getline(ss, num, ','))
    {
        try
        {
            int symptom_id = std::stoi(num);

            // checks if num entered is larger than the number of symptom records in the database
            if (symptom_id > symptoms_map.size()) continue;

            selected_symptoms.push_back(symptom_id);
        }
        catch (std::invalid_argument&)
        {
            continue;
        }
    }

    // Local function that adds the selected symptoms.
    // Will check if the symptom is already in the list before adding, so duplicates will be avoided.
    auto add_symptom = [] (std::vector<std::string>& vec, const std::string& str) {
        if (std::find(vec.begin(), vec.end(), str) == vec.end())
            vec.push_back(str);
    };

    Symptoms& symptoms = record.symptoms;

    // add selected symptoms to the Symptoms struct
    for (int symptom_id : selected_symptoms)
    {
        std::pair<std::string, std::string>& symptom = symptoms_map[symptom_id];

        if (symptom.second == "high")
            add_symptom(symptoms.high_risk_symptoms, symptom.first);
        else if (symptom.second == "medium")
            add_symptom(symptoms.medium_risk_symptoms, symptom.first);
        else if (symptom.second == "low")
            add_symptom(symptoms.low_risk_symptoms, symptom.first);
    }
}

void pick_high_risk_visited_locations(PatientRecord& record, std::ifstream& file)
{
    if (empty_database(file))
    {
        std::cout << "NO HIGH RISK LOCATIONS IN DATABASE. This part is skipped.\n";
        return; // there are no high risks locations in database so this part is skipped
    }

    // map that holds the high risk locations
    std::unordered_map<int, std::string> hr_locations_map;
    std::string line;
    int id = 1;

    std::cout << "\nHigh Risk Locations List:\n";

    // printing all locations and adding them to a map
    while (std::getline(file, line))
    {
        hr_locations_map[id] = line;

        std::cout << id << " - " << str_toupper(line) << '\n';

        id++;
    }

    std::cout << "Select all the recently visited high risk locations, if any. Separate them with a comma (ie 2,5,8)\n"
              << "-->";

    std::getline(std::cin, line);

    if (line == "") return; // patient hasn't been to any high risk location

    std::regex reg("^[0-9,]*$");
    while (!std::regex_match(line, reg))
    {
        std::cout << "\nINVALID INPUT : Only numbers and commas allowed\n";
        std::cout << "Select all the recently visited high risk locations, if any. Separate them with a comma (ie 2,5,8)\n"
                  << "-->";

        std::getline(std::cin, line);
        if (line == "") return;
    }

    std::stringstream ss(line);
    std::string num;
    std::vector<int> selected_locations;

    // validating input
    while (std::getline(ss, num, ','))
    {
        try
        {
            int location_id = std::stoi(num);

            // checks if num entered is larger than the number of high risk location records in database
            if (location_id > hr_locations_map.size()) continue;

            selected_locations.push_back(location_id);
        }
        catch (std::invalid_argument&)
        {
            continue;
        }
    }

    std::vector<std::string>& visited_locations = record.visited_high_risk_locations;
    for (int location_id : selected_locations)
    {
        std::string& visited_location = hr_locations_map[location_id];

        // checks if location is already in the list before adding
        if (std::find(visited_locations.begin(), visited_locations.end(), visited_location) == visited_locations.end())
            visited_locations.push_back(visited_location);
    }
}

void recommend_covid_test(PatientRecord& record)
{
    // get date of last overseas travel trip
    std::tm overseas_travel_date = string_to_date(record.last_overseas_travel);

    std::cout << '\n';

    // if a patient has any high risk symptom, recommend a test
    if (!record.symptoms.high_risk_symptoms.empty())
    {
        std::cout << "Result : Get a COVID test.\n";
        return;
    }

    // if patient has visited a high risk location and has any symptoms, a test is recommended
    if (!record.visited_high_risk_locations.empty()
    && (!record.symptoms.low_risk_symptoms.empty()
    || !record.symptoms.medium_risk_symptoms.empty()
    || !record.symptoms.high_risk_symptoms.empty()))
    {
        std::cout << "Result : Get a COVID test.\n";
        return;
    }

    // if patient has traveled overseas within 2 months of the current date, a test is recommended
    if (record.date_time.tm_year == overseas_travel_date.tm_year
    && (record.date_time.tm_mon - overseas_travel_date.tm_mon) <= 2)
    {
        std::cout << "Result : Get a COVID test.\n";
        return;
    }

    // if the patient is 50 years old or older, and has a total of 2 or more low/medium symptoms,
    // or has any high risk symptom a test is recommended
    if (get_age(record) >= 50
    && ((!record.symptoms.high_risk_symptoms.empty())
    || ((record.symptoms.low_risk_symptoms.size() + record.symptoms.medium_risk_symptoms.size()) >= 2)))
    {
        std::cout << "Result : Get a COVID test.\n";
        return;
    }

    // if a patient has not visited any high risk locations and has medium/low risk symptoms,
    // isolation is recommended instead
    if (record.visited_high_risk_locations.empty()
    && (!record.symptoms.medium_risk_symptoms.empty() || !record.symptoms.low_risk_symptoms.empty()))
    {
        std::cout << "Result : Isolate yourself at home.\n";
        return;
    }

    // if no test cases are true, then a covid test is not needed
    std::cout << "Result : No COVID test needed.\n";
}

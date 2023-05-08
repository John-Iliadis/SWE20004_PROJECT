//
// Created by Gianni on 3/05/2023.
//

#include "../include/option1.hpp"

void option1()
{
    std::ifstream patient_details("../patient_details.txt");
    std::ifstream symptoms_file("../symptoms.txt");
    std::ifstream high_risk_loc_file("../high_risk_covid_locations.txt");

    // checking if all files are opened
    if (patient_details.fail() || symptoms_file.fail() || high_risk_loc_file.fail())
        throw std::runtime_error("Option1() - Failed to open all files");

    { // checking is symptoms database is populated
        std::string str;
        std::getline(symptoms_file, str); // skip header
        std::getline(symptoms_file, str);
        symptoms_file.seekg(0); // move pointer back to the start of the file

        if (str == "")
        {
            std::cout << "UNABLE TO RECOMMEND COVID TEST - SYMPTOMS DATABASE EMPTY\n";
            return;
        }
    }

    PatientRecord record;
    get_id(patient_details, record);
    get_name(record);
    get_dob(record);
    get_address(record);
    get_overseas_travel(record);
    pick_symptoms(record, symptoms_file);
    pick_high_risk_visited_locations(record, high_risk_loc_file);

    patient_details.close();
    symptoms_file.close();
    high_risk_loc_file.close();

    insert_record(record);

    recommend_covid_test(record);
}

bool check_id_exists(std::ifstream& file, const std::string& id)
{
    std::string line;
    std::getline(file, line); // discard header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string existing_id;
        std::getline(ss, existing_id, ';');

        if (id == existing_id)
            return true;
    }

    return false;
}

void get_id(std::ifstream& patient_details, PatientRecord& record)
{
    std::cout << "Enter patient id:";
    std::getline(std::cin, record.id);

    while (check_id_exists(patient_details, record.id) || !is_num(record.id))
    {
        std::cout << "PATIENT ID SHOULD BE NUMERIC AND UNIQUE\n";
        std::cout << "Enter patient id:";
        std::getline(std::cin, record.id);
    }
}

void get_name(PatientRecord& record)
{
    // this function gets the fullname of the patient
    // the input must not be empty or contain a comma, since that can mess up searching later

    std::regex reg("^[a-zA-Z]{1,30}$");

    std::cout << "Enter first name:";
    std::getline(std::cin, record.fname);

    while (!std::regex_match(record.fname, reg))
    {
        std::cout << "INVALID NAME : Name should only contain letters and have 1-30 length\n";
        std::cout << "Enter first name:";
        std::getline(std::cin, record.fname);
    }

    std::cout << "Enter last name:";
    std::getline(std::cin, record.lname);

    while (!std::regex_match(record.lname, reg))
    {
        std::cout << "INVALID NAME : Name should only contain letters and have 1-30 length\n";
        std::cout << "Enter last name:";
        std::getline(std::cin, record.lname);
    }
}

void get_dob(PatientRecord& record)
{
    std::cout << "Enter date of birth in this format (dd-mm-yyyy):";
    std::getline(std::cin, record.dob);

    while (!check_date_format(record.dob))
    {
        std::cout << "DATE FORMAT SHOULD BE (dd-mm-yyyy)\n";
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
        std::cout << "INVALID ADDRESS : No special characters are allowed and length should be 1-255\n";
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
        std::cout << "DATE FORMAT SHOULD BE (dd-mm-yyyy)\n";
        std::cout << "Enter last overseas travel date in this format (dd-mm-yyyy):";
        std::getline(std::cin, record.last_overseas_travel);
    }
}

void pick_symptoms(PatientRecord& record, std::ifstream& file)
{
    std::string line;
    std::getline(file, line); // discard header
    std::unordered_map<int, std::pair<std::string, std::string>> symptoms_map;

    int id = 1;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string symptom;
        std::string risk;
        std::getline(ss, symptom, ';');
        std::getline(ss, risk);
        symptoms_map[id] = std::make_pair(symptom, risk);
        std::transform(symptom.begin(), symptom.end(), symptom.begin(), ::toupper);

        std::cout << id << " - " << symptom << '\n';
        id++;
    }

    std::cout << "Select all the experienced symptoms, if any. Separate them with a comma (ie 2,5,8)\n"
              << "-->";

    std::getline(std::cin, line);

    if (line == "") return; // patient has no symptoms

    std::stringstream ss(line);
    std::string num;
    std::vector<int> selected_symptoms;

    // validating input
    while (std::getline(ss, num, ','))
    {
        try
        {
            int symptom_id = std::stoi(num);

            if (symptom_id > symptoms_map.size()) continue; // checks if num entered is larger than the list

            selected_symptoms.push_back(symptom_id);
        }
        catch (std::invalid_argument&)
        {
            continue;
        }
    }

    // checks if the symptom is already in the list. If it isn't, then the symptom will be added
    auto add_symptom = [] (std::vector<std::string>& vec, const std::string& str) {
        if (std::find(vec.begin(), vec.end(), str) == vec.end())
            vec.push_back(str);
    };

    Symptoms& symptoms = record.symptoms;

    for (int symptom_id : selected_symptoms)
    {
        auto& symptom = symptoms_map[symptom_id];

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
    { // checking if database is empty
        std::string str;
        std::getline(file, str);
        file.seekg(0);

        if (str == "")
        {
            std::cout << "NO HIGH RISK LOCATIONS IN DATABASE";
            return; // there are no high risks locations in database so this part is skipped
        }
    }

    std::unordered_map<int, std::string> hr_locations_map;
    std::string line;
    int id = 1;

    // printing all locations and adding them to a map
    while (std::getline(file, line))
    {
        hr_locations_map[id] = line;
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);
        std::cout << id << " - " << line << '\n';

        id++;
    }

    std::cout << "Select all the recently visited high risk locations, if any. Separate them with a comma (ie 2,5,8)\n"
              << "-->";

    std::getline(std::cin, line);

    if (line == "") return; // patient hasn't been to any high risk location

    std::stringstream ss(line);
    std::string num;
    std::vector<int> selected_locations;

    // validating input
    while (std::getline(ss, num, ','))
    {
        try
        {
            int location_id = std::stoi(num);

            if (location_id > hr_locations_map.size()) continue;  // checks if num entered is larger than the list

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

// This function inserts a row of data into the patient
// details table.
void insert_record(PatientRecord& record)
{
    std::ofstream patient_details("../patient_details.txt", std::ios::app);

    if (patient_details.fail())
        throw std::runtime_error("insert_record() - Failed to open file");

    std::time_t current_time = std::time(nullptr);

    record.date_time = *std::localtime(&current_time);
    record.date_time.tm_year += 1900;

    std::string row {
        record.id + ';' +
        record.fname + ' ' + record.lname + ';' +
        record.dob + ';' +
        record.address + ';' +
        "null" + ';' +
        record.last_overseas_travel + ';' +
        "null" + ';' +
        "null" + ';' +
        date_to_string(record.date_time) + ' ' + time_to_string(record.date_time)
    };

    patient_details << row << std::endl;
    patient_details.close();
}

void recommend_covid_test(PatientRecord& record)
{
    if (!record.visited_high_risk_locations.empty()
    && (!record.symptoms.low_risk_symptoms.empty()
    || !record.symptoms.medium_risk_symptoms.empty()
    || !record.symptoms.high_risk_symptoms.empty()))
    {
        std::cout << "Result : Get a COVID test.";
    }
    else if (record.visited_high_risk_locations.empty()
    && record.symptoms.high_risk_symptoms.empty())
    {
        std::cout << "Result : Isolate yourself at home.";
    }
}

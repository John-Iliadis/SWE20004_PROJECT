//
// Created by Gianni on 3/05/2023.
//

#include "../include/functions.hpp"

void prompt()
{
    std::cout << "Press 1 - Enter details for a COVID test recommendation\n";
    std::cout << "Press 2 - Submit COVID test status & update location database\n";
    std::cout << "Press 3 - Display the updated location (high risk for COVID)\n";
    std::cout << "Press 4 - Update COVID patient details\n";
    std::cout << "Press 5 - Display all positive COVID patients details\n";
    std::cout << "Press 6 - Exit\n";
    std::cout << "Option -->";
}

void option1()
{
    std::ifstream patient_details("../patient_details.txt");
    std::ifstream symptoms_file("../symptoms.txt");
    std::ifstream high_risk_loc_file("../high_risk_covid_locations.txt");

    // checking if all files are opened
    if (!patient_details.is_open() || !symptoms_file.is_open() || !high_risk_loc_file.is_open())
        throw std::runtime_error("Option1() - Failed to open all files");

    { // checking is symptoms database is populated
        std::string str;
        std::getline(symptoms_file, str); // skip header
        std::getline(symptoms_file, str);
        symptoms_file.seekg(0);

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

    // implement algorithm for recommending test
}

bool check_id_exists(std::ifstream& file, const std::string& id)
{
    std::string line;
    std::getline(file, line); // discard header

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string existing_id;
        std::getline(ss, existing_id, ',');

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

    std::cout << "Enter first name:";
    std::getline(std::cin, record.fname);

    while (record.fname == "" || record.fname.contains(','))
    {
        std::cout << "INVALID NAME\n";
        std::cout << "Enter first name:";
        std::getline(std::cin, record.fname);
    }

    std::cout << "Enter last name:";
    std::getline(std::cin, record.lname);

    while (record.lname == "" || record.lname.contains(','))
    {
        std::cout << "INVALID NAME\n";
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
    std::cout << "Enter address:";
    std::getline(std::cin, record.address);

    while (record.address == "" || record.address.contains(','))
    {
        std::cout << "INVALID ADDRESS\n";
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
        std::getline(ss, symptom, ',');
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

        // check if symptom is already in vector
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
            std::cout << "NO HIGH RISK LOCATIONS IN DATABASE";;
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

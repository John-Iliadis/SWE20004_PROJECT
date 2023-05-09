//
// Created by Gianni on 9/05/2023.
//

#include "../include/option2.hpp"

void option2()
{
    std::string patient_file_loc = "../patient_details.txt";
    std::string temp_file_loc = "../temp.txt";

    // open the file to get an existing patient record
    std::ifstream patient_details_i(patient_file_loc);
    std::ofstream temp_file_o(temp_file_loc, std::ios::trunc);

    if (patient_details_i.fail() || temp_file_o.fail())
        throw std::runtime_error("option2() : Failed to open files.");

    if (empty_database(patient_details_i))
    {
        std::cout << "The patient details database is empty\n";
        patient_details_i.close();
        return;
    }

    std::string id;
    std::string covid_test_result;

    get_id(patient_details_i, id);
    get_covid_test_result(covid_test_result);

    // get the record from the file, and turn it into a PatientRecord struct
    PatientRecord record = get_patient_record(patient_details_i, id);
    record.covid_test = covid_test_result;

    if (covid_test_result == "positive")
    {
        get_visited_location(record);
        update_high_risk_location_database(record.visited_location);
    }

    copy_to_temp(patient_details_i, temp_file_o, record);

    patient_details_i.close();
    temp_file_o.close();

    std::ofstream patient_file_o(patient_file_loc);
    std::ifstream temp_file_i(temp_file_loc);


    repopulate_main(temp_file_i, patient_file_o);

    temp_file_i.close();
    patient_file_o.close();
}

void get_id(std::ifstream& file, std::string& id)
{
    std::cout << "Enter patient id:";
    std::getline(std::cin, id);

    while (!check_id_exists(file, id))
    {
        std::cout << "THIS ID DOES NOT EXIST IN THE DATABASE\n";
        std::cout << "Enter an existing id:";

        std::getline(std::cin, id);
    }
}

void get_covid_test_result(std::string& covid_test_result)
{
    std::regex reg("\\b(positive|negative)\\b");

    std::cout << "Enter covid test result (positive/negative):";
    std::getline(std::cin, covid_test_result);
    str_tolower(covid_test_result);

    while (!std::regex_match(covid_test_result, reg))
    {
        std::cout << "INVALID INPUT : Enter positive or negative\n";
        std::cout << "Enter covid test result (positive/negative):";
        std::getline(std::cin, covid_test_result);
        str_tolower(covid_test_result);
    }
}

void get_visited_location(PatientRecord& record)
{
    std::regex reg("^[a-zA-Z ]{1,60}$");

    std::cout << "Enter a recently visited location:";
    std::getline(std::cin, record.visited_location);

    while (!std::regex_match(record.visited_location, reg))
    {
        std::cout << "INVALID INPUT : Location can only contain letters and have 1-60 length\n";
        std::cout << "Enter a recently visited location:";
        std::getline(std::cin, record.visited_location);
    }
}

void update_high_risk_location_database(const std::string& location)
{
    std::ofstream file("../high_risk_covid_locations.txt", std::ios::app);

    if (file.fail())
        throw std::runtime_error("update_high_risk_location_database() : Failed to open file");

    file << location << std::endl;

    file.close();
}

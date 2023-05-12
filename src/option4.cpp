//
// Created by Gianni on 9/05/2023.
//

#include "../include/option4.hpp"

void option4()
{
    std::string patient_file_loc = "../patient_details.txt";
    std::string temp_file_loc = "../temp.txt";

    std::ifstream patient_details_i(patient_file_loc);
    std::ofstream temp_file_o(temp_file_loc, std::ios::trunc);

    if (patient_details_i.fail())
        throw std::runtime_error("option4() : Failed to open file");

    if (empty_database(patient_details_i))
    {
        std::cout << "\nThe patient details database is empty\n";
        patient_details_i.close();
        return;
    }

    std::vector<std::string> rows;
    std::string row;

    // get all records in a vector
    while (std::getline(patient_details_i, row))
    {
        rows.push_back(std::move(row));
    }

    // find the most recent covid patient
    PatientRecord record = find_positive_patient(rows);

    // If none of the patients have covid, the function is terminated
    if (record.covid_test == "negative")
    {
        std::cout << "\nNone of the patients have covid\n";
        return;
    }

    get_status(record); // input the new status

    copy_to_temp(patient_details_i, temp_file_o, record); // copy file to temp

    patient_details_i.close();
    temp_file_o.close();

    // open the patient details database for writing
    std::ofstream patient_details_o(patient_file_loc, std::ios::trunc);
    std::ifstream temp_file_i(temp_file_loc);

    repopulate_main(temp_file_i, patient_details_o);

    patient_details_o.close();
    temp_file_i.close();
}

PatientRecord find_positive_patient(std::vector<std::string>& vec)
{
    PatientRecord record;

    // reverse iterate so we get the most recent covid patient
    for (auto& row : std::ranges::views::reverse(vec))
    {
        record = get_patient_record(row);

        if (record.covid_test == "positive")
            break;
    }

    return record;
}

void get_status(PatientRecord& record)
{
    std::regex reg("\\b(dead|alive|cured)\\b");

    std::cout << "Enter the patients new status (dead/alive/cured):";
    std::getline(std::cin, record.status);
    str_tolower(record.status);

    while (!std::regex_match(record.status, reg))
    {
        std::cout << "\nINVALID INPUT - Value should be in (dead/alive/cured)\n";
        std::cout << "Enter the patients new status (dead/alive/cured):";
        std::getline(std::cin, record.status);
        str_tolower(record.status);
    }
}

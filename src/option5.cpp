//
// Created by Gianni on 9/05/2023.
//

#include "../include/option5.hpp"

void option5()
{
    std::ifstream patient_details("../patient_details.txt");

    if (patient_details.fail())
        throw std::runtime_error("option5() : Failed to open file");

    if (empty_database(patient_details))
    {
        std::cout << "THE DATABASE IS EMPTY\n";
        patient_details.close();
        return;
    }

    table_t table;

    { // remove later
        std::string line;
        std::getline(patient_details, line); // discard header
    }

    table.push_back(
            {"PATIENT ID", "NAME", "DATE OF BIRTH", "VISITED LOCATION", "LAST OVERSEAS TRAVEL", "COVID TEST RESULT",
             "STATUS"});

    std::string row;

    while (std::getline(patient_details, row))
    {
        PatientRecord record = get_patient_record(row);
        table.push_back(std::move(patient_record_to_arr(record)));
    }

    std::unordered_map<int,int> field_widths = get_field_width(table);

    print_records(table, field_widths);

    patient_details.close();
}

std::vector<std::string> patient_record_to_arr(PatientRecord& record)
{
    std::vector<std::string> vec;
    vec.push_back(std::move(record.id));
    vec.push_back(std::move(record.name));
    vec.push_back(std::move(record.dob));
    vec.push_back(std::move(record.visited_location));
    vec.push_back(std::move(record.last_overseas_travel));
    vec.push_back(std::move(record.covid_test));
    vec.push_back(std::move(record.status));

    return vec;
}

std::unordered_map<int,int> get_field_width(const table_t& table)
{
    std::unordered_map<int,int> field_widths;

    for (int i = 1; i < table.size(); ++i)
    {
        for (int j = 0; j < table[i].size(); ++j)
        {
            int current_field = table[i][j].size();
            int prev = table[i - 1][j].size();

            // bug here
            if (current_field > prev)
                field_widths[j] = current_field;
            else
                field_widths[j] = prev;
        }
    }

    return field_widths;
}

void print_records(table_t& table, std::unordered_map<int,int>& field_widths)
{
    for (int i = 0; i < table.size(); ++i)
    {
        for (int j = 0; j < table[i].size(); ++j)
        {
            std::cout << std::setw(field_widths[j]) << std::left << str_toupper(table[i][j]);
        }

        std::cout << '\n';
    }
}

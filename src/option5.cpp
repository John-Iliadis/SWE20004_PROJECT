/*
 * File option5.cpp
 * Created on 9/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 * */

#include "../include/option5.hpp"

void option5()
{
    std::ifstream patient_details("../patient_details.txt");

    if (patient_details.fail())
        throw std::runtime_error("option5() : Failed to open file");

    // check if the database is empty
    if (empty_database(patient_details))
    {
        std::cout << "THE PATIENT DETAILS DATABASE IS EMPTY\n";
        patient_details.close();
        return;
    }

    // vector that holds all the rows
    table_t table;

    // push back the table headers
    table.push_back(
            {"PATIENT ID", "NAME", "DATE OF BIRTH", "ADDRESS", "VISITED LOCATION", "LAST OVERSEAS TRAVEL", "COVID TEST RESULT",
             "STATUS"});

    std::string row;
    while (std::getline(patient_details, row))
    {
        // get all the records in the vector
        PatientRecord record = get_patient_record(row);
        table.push_back(std::move(patient_record_to_arr(record)));
    }

    // a map that holds the largest width of each field. Used for formatting
    std::unordered_map<int,int> field_widths = get_field_width(table);

    print_records(table, field_widths);

    patient_details.close();
}

std::unordered_map<int,int> get_field_width(const table_t& table)
{
    std::unordered_map<int,int> field_widths;

    // put the initial values into the map
    for (int i = 0; i < table[0].size(); ++i)
    {
        field_widths[i] = table[0][i].size();
    }

    // search and find the largest width of each field
    for (int i = 1; i < table.size(); ++i)
    {
        for (int j = 0; j < table[i].size(); ++j)
        {
            int current_field = table[i][j].size();

            if (current_field > field_widths[j])
                field_widths[j] = current_field;
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
            std::cout << std::setw(field_widths[j] + 5) << std::left << str_toupper(table[i][j]);
        }

        std::cout << '\n';
    }
}

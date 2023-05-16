/*
 * File option3.cpp
 * Created on 9/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 * */

#include "../include/option3.hpp"

void option3()
{
    std::ifstream high_risk_location_file("../high_risk_covid_locations.txt");

    if (high_risk_location_file.fail())
        throw std::runtime_error("option3() : Failed to open files");

    // checks if high risk location database is empty
    if (empty_database(high_risk_location_file))
    {
        std::cout << "THE HIGH RISK LOCATION DATABASE IS EMPTY\n";
        return;
    }

    high_risk_location_file.seekg(-3, std::ios::end); // set file pointer before the newline of the last record

    int current_pos = high_risk_location_file.tellg(); // get current pos of file pointer

    // start iterating backwards until a newline is found
    for (int i = current_pos; i >= 0; --i)
    {
        if (high_risk_location_file.peek() == '\n')
        {
            // when a new line is found, the file pointer gets incremented by 1,
            // which places it at the start of the last record
            high_risk_location_file.get();
            break;
        }

        // if there is only one record, then the pointer will be end up back at the start
        high_risk_location_file.seekg(i, std::ios::beg);
    }

    std::string location;
    std::getline(high_risk_location_file, location);

    std::cout << "The most recent COVID high risk location is " << location << '\n';

    high_risk_location_file.close();
}

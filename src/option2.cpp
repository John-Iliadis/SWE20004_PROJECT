//
// Created by Gianni on 9/05/2023.
//

#include "../include/option2.hpp"

void option2()
{
    std::ifstream patient_details("../patient_details.txt");
    if (patient_details.fail())
        throw std::runtime_error("option2() : Failed to open file.");

    std::string id;
    std::string covid_test_result;

    get_id(patient_details, id);
    get_covid_test_result(covid_test_result);

    // continue here
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
    str_toupper(covid_test_result);

    while (!std::regex_match(covid_test_result, reg))
    {
        std::cout << "INVALID INPUT : Enter positive or negative\n";
        std::cout << "Enter covid test result (positive/negative):";
        std::getline(std::cin, covid_test_result);
        str_tolower(covid_test_result);
    }
}

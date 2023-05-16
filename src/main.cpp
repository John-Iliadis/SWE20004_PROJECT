/*
 * File main.cpp
 * Created on 3/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 * */

#include "../include/includes.hpp"

int main()
{
    std::map<int,void(*)()> options {
            {1, &option1},
            {2, &option2},
            {3, &option3},
            {4, &option4},
            {5, &option5},
    };

    std::string input;
    int option{};

    while (true)
    {
        prompt();

        std::getline(std::cin, input);

        try
        {
            option = std::stoi(input);
        }
        catch (std::invalid_argument&)
        {
            std::cout << "\nONLY NUMBERS ALLOWED\n\n";
            continue;
        }

        if (option > 6)
        {
            std::cout << "\nNOT A VALID OPTION\n\n";
            continue;
        }
        else if (option == 6)
        {
            std::cout << "\nGOODBYE\n";
            break;
        }

        std::cout << std::endl;
        options[option]();
        std::cout << std::endl;
    }

    return 0;
}

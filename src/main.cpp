#include <iostream>
#include "../include/option1.hpp"
#include "../include/option2.hpp"
#include "../include/option3.hpp"
#include "../include/option4.hpp"
#include "../include/option5.hpp"

int main()
{
    /*bool program_running = true;
    std::string input;
    int option{};

         //std::vector<void(*)()> funcs;


    while (program_running)
    {
        prompt();

        std::getline(std::cin, input);

        try
        {
            option = std::stoi(input);
        }
        catch (std::invalid_argument&)
        {
            std::cout << "ONLY NUMBERS ALLOWED\n";
            continue;
        }

        switch (option)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                program_running = false;
                break;
            default:
                std::cout << "UNKNOWN SELECTION, PLEASE TRY AGAIN\n";
        }
    }*/

    // testing

    option2();

   /* std::vector<std::vector<std::string>> vec {
            {"1", "333", "666666"},
            {"22", "4444", "1"},
            {"88888888", "22", "1"},
            {"1", "55555", "22"}
    };

    auto m = get_field_width(vec);*/

    return 0;
}

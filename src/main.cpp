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
            std::cout << "ONLY NUMBERS ALLOWED\n";
            continue;
        }

        if (option > 6)
        {
            std::cout << "NOT A VALID OPTION\n";
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

    // testing

   /* std::vector<std::vector<std::string>> vec {
            {"1", "333", "666666"},
            {"22", "4444", "1"},
            {"88888888", "22", "1"},
            {"1", "55555", "22"}
    };

    auto m = get_field_width(vec);*/

    return 0;
}

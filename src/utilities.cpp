//
// Created by Gianni on 3/05/2023.
//

#include "../include/utilities.hpp"


bool check_date_format(const std::string& date)
{
    std::regex reg(R"(\b(0?[1-9]|[1-2][0-9]|3[0-1])-(0?[1-9]|1[0-2])-\d{4}\b)");

    if (std::regex_match(date, reg))
        return true;

    return false;
}

std::tm string_to_date(const std::string& str_date)
{
    std::tm date;
    std::stringstream ss(str_date);
    std::string value;
    std::vector<std::string> vec;

    while (std::getline(ss, value, '-'))
        vec.push_back(value);

    date.tm_mday = std::stoi(vec[0]);
    date.tm_mon = std::stoi(vec[1]);
    date.tm_year = std::stoi(vec[2]);

    return date;
}

std::string date_to_string(std::tm& date)
{
    std::string day = std::to_string(date.tm_mday);
    std::string month = std::to_string(date.tm_mon);
    std::string year = std::to_string(date.tm_year);

    return day + '-' + month + '-' + year;
}

std::string time_to_string(std::tm& time)
{
    std::string seconds = std::to_string(time.tm_sec);
    std::string minutes = std::to_string(time.tm_min);
    std::string hours = std::to_string(time.tm_hour);

    return hours + ':' + minutes + ':' + seconds;
}

bool is_num(const std::string& str)
{
    if (std::ranges::all_of(str.begin(), str.end(), [] (char c) {
        return std::isdigit(c) == 1;
    }))
    {
        return true;
    }

    return false;
}

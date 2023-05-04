//
// Created by Gianni on 3/05/2023.
//

#ifndef PROJECT_CODE_UTILITIES_HPP
#define PROJECT_CODE_UTILITIES_HPP
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include "patient_record.hpp"

void prompt();
bool check_date_format(const std::string& date);
std::tm string_to_date(const std::string& str_date);
std::string date_to_string(std::tm& date);
std::string time_to_string(std::tm& time);
bool is_num(const std::string& str);

#endif //PROJECT_CODE_UTILITIES_HPP

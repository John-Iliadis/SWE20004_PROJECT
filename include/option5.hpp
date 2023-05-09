//
// Created by Gianni on 9/05/2023.
//

#ifndef PROJECT_CODE_OPTION5_HPP
#define PROJECT_CODE_OPTION5_HPP
#include <iomanip>
#include <map>
#include "utilities.hpp"
#include "option4.hpp"

typedef std::vector<std::vector<std::string>> table_t;

void option5();
std::vector<std::string> patient_record_to_arr(PatientRecord& record);
std::unordered_map<int,int> get_field_width(const table_t& table);
void print_records(table_t& table, std::unordered_map<int,int>& field_widths);

#endif //PROJECT_CODE_OPTION5_HPP

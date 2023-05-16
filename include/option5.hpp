/*
 * File option5.hpp
 * Created on 9/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 *
 * Description: Option 5 is used to print out the patient details database in a table format.
 * */

#ifndef PROJECT_CODE_OPTION5_HPP
#define PROJECT_CODE_OPTION5_HPP
#include <iomanip>
#include <map>
#include "utilities.hpp"

typedef std::vector<std::vector<std::string>> table_t;

void option5();

// This function returns a map that contains the largest width
// out of every column in the database
std::unordered_map<int,int> get_field_width(const table_t& table);

// Prints the database as a table
void print_records(table_t& table, std::unordered_map<int,int>& field_widths);

#endif //PROJECT_CODE_OPTION5_HPP

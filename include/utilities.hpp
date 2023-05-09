//
// Created by Gianni on 3/05/2023.
//

#ifndef PROJECT_CODE_UTILITIES_HPP
#define PROJECT_CODE_UTILITIES_HPP
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "patient_record.hpp"

void prompt();

bool check_id_exists(std::ifstream& file, const std::string& id);
bool check_date_format(const std::string& date);
bool empty_database(std::ifstream& file);

std::tm string_to_date(const std::string& str_date);
std::string date_to_string(std::tm& date);
std::string time_to_string(std::tm& time);

bool is_num(const std::string& str);

std::string& str_toupper(std::string& str);
std::string& str_tolower(std::string& str);

// This function inserts a patient record into a database.
void insert_patient_record(PatientRecord& record, const std::string& file_name);
void insert_patient_record(PatientRecord& record, std::ofstream& file);

// Returns a PatientRecord struct from a file, given the id.
// Make sure id exists before using this, otherwise an empty record will get returned
PatientRecord get_patient_record(std::ifstream& file, const std::string& id);
PatientRecord get_patient_record(const std::string& row);

// copies all the contents from one file to another.
// The file that is written to, will get truncated
void copy_file(const std::string& copy_from, const std::string& copy_to);

void copy_to_temp(std::ifstream& input_file, std::ofstream& output_file, PatientRecord& record);
void repopulate_main(std::ifstream& input_file, std::ofstream& output_file);


#endif //PROJECT_CODE_UTILITIES_HPP

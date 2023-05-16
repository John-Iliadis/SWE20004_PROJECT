/*
 * File utilities.hpp
 * Created on 3/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 *
 * Description: Some common utility functions which are used throughout the project.
 * */

#ifndef PROJECT_CODE_UTILITIES_HPP
#define PROJECT_CODE_UTILITIES_HPP
#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include "patient_record.hpp"

// prompts all the options
void prompt();

// checks if a patient id already exists in the database
bool check_id_exists(std::ifstream& file, const std::string& id);

// checks if string entered fits the dd-mm-yyyy format
bool check_date_format(const std::string& date);

// checks if the database is populated
bool empty_database(std::ifstream& file);

std::string date_to_string(std::tm& date);
std::string time_to_string(std::tm& time);
std::tm string_to_date(const std::string& str_date);

// get the age of a patient
int get_age(const PatientRecord& record);

// checks is the string is numeric
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

// copy the database to a temporary file along with the updated record
void copy_to_temp(std::ifstream& input_file, std::ofstream& output_file, PatientRecord& record);
// copy the records back to the original file
void repopulate_main(std::ifstream& input_file, std::ofstream& output_file);

// Splits a PatientRecord struct into a vector
std::vector<std::string> patient_record_to_arr(PatientRecord& record);


#endif //PROJECT_CODE_UTILITIES_HPP

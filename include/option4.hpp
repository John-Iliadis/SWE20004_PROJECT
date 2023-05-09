//
// Created by Gianni on 9/05/2023.
//

#ifndef PROJECT_CODE_OPTION4_HPP
#define PROJECT_CODE_OPTION4_HPP
#include <ranges>
#include "utilities.hpp"

void option4();
bool empty_database(std::ifstream& file);
PatientRecord find_positive_patient(std::vector<std::string>& vec);
void get_status(PatientRecord& record);
void copy_to_temp(std::ifstream& input_file, std::ofstream& output_file, PatientRecord& record);
void repopulate_main(std::ifstream& input_file, std::ofstream& output_file);

#endif //PROJECT_CODE_OPTION4_HPP

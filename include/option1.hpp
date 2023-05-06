//
// Created by Gianni on 3/05/2023.
//

#ifndef PROJECT_CODE_OPTION1_HPP
#define PROJECT_CODE_OPTION1_HPP
#include <fstream>
#include <iostream>
#include <algorithm>
#include "utilities.hpp"

void option1();

bool check_id_exists(std::ifstream& file, const std::string& id);
void get_id(std::ifstream& patient_details, PatientRecord& record);
void get_name(PatientRecord& record);
void get_dob(PatientRecord& record);
void get_address(PatientRecord& record);
void get_overseas_travel(PatientRecord& record);

void pick_symptoms(PatientRecord& record, std::ifstream& file);

void pick_high_risk_visited_locations(PatientRecord& record, std::ifstream& file);

void insert_record(PatientRecord& record);

void recommend_covid_test(PatientRecord& record);

#endif //PROJECT_CODE_OPTION1_HPP

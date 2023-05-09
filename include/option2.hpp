//
// Created by Gianni on 9/05/2023.
//

#ifndef PROJECT_CODE_OPTION2_HPP
#define PROJECT_CODE_OPTION2_HPP
#include "utilities.hpp"

void option2();

void get_id(std::ifstream& file, std::string& id);
void get_covid_test_result(std::string& covid_test_result);
void get_visited_location(PatientRecord& record);
void update_high_risk_location_database(const std::string& location);

#endif //PROJECT_CODE_OPTION2_HPP

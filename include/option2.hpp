/*
 * File option2.hpp
 * Created on 9/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 *
 * Description: Option 2 is used to get the patients COVID test results. If the result
 * is positive, then a recently visited location will also be recorded. Finally, the
 * database is updated with the new data.
 * */

#ifndef PROJECT_CODE_OPTION2_HPP
#define PROJECT_CODE_OPTION2_HPP
#include "utilities.hpp"

void option2();

void get_id(std::ifstream& file, std::string& id);
void get_covid_test_result(std::string& covid_test_result);
void get_visited_location(PatientRecord& record);
void update_high_risk_location_database(const std::string& location);

#endif //PROJECT_CODE_OPTION2_HPP

/*
 * File option4.hpp
 * Created on 9/05/2023
 *
 * Ioannis Iliadis - 104010553
 * Jiin Wen Tan - 102846565
 * Jamie Liddicoat - 103985278
 *
 * Description: Option 4 is used to update the most recent positive patients' status,
 * which would be dead, alive, or cured. The database will be updated with the new data
 * */

#ifndef PROJECT_CODE_OPTION4_HPP
#define PROJECT_CODE_OPTION4_HPP
#include <ranges>
#include "utilities.hpp"

void option4();

// gets the most recent positive covid patient
PatientRecord find_positive_patient(std::vector<std::string>& vec);

void get_status(PatientRecord& record);

#endif //PROJECT_CODE_OPTION4_HPP

//
// Created by Gianni on 3/05/2023.
//

#ifndef PROJECT_CODE_FUNCTIONS_HPP
#define PROJECT_CODE_FUNCTIONS_HPP
#include <fstream>
#include <iostream>
#include "utilities.hpp"

void prompt();

// option 1 functions
void option1();
bool check_id_exists(std::ifstream& file, const std::string& id);
Symptoms pick_symptoms(std::ifstream& file);
std::vector<std::string> pick_high_risk_visited_locations(std::ifstream& file);

#endif //PROJECT_CODE_FUNCTIONS_HPP

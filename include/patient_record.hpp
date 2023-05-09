//
// Created by Gianni on 3/05/2023.
//

#ifndef PROJECT_CODE_PATIENT_RECORD_HPP
#define PROJECT_CODE_PATIENT_RECORD_HPP
#include <ctime>
#include <vector>

struct Symptoms
{
    std::vector<std::string> low_risk_symptoms;
    std::vector<std::string> medium_risk_symptoms;
    std::vector<std::string> high_risk_symptoms;
};

struct PatientRecord
{
    std::string id;
    std::string name;
    std::string dob;
    std::string address;
    std::string visited_location;
    std::tm date_time;
    std::string last_overseas_travel;
    std::string covid_test;
    std::string status;

    Symptoms symptoms;
    std::vector<std::string> visited_high_risk_locations;
};


#endif //PROJECT_CODE_PATIENT_RECORD_HPP

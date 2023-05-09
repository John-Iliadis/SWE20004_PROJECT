//
// Created by Gianni on 3/05/2023.
//

#include "../include/utilities.hpp"

void prompt()
{
    std::cout << "Press 1 - Enter details for a COVID test recommendation\n";
    std::cout << "Press 2 - Submit COVID test status\n";
    std::cout << "Press 3 - Display the updated location (high risk for COVID)\n";
    std::cout << "Press 4 - Update COVID patient details\n";
    std::cout << "Press 5 - Display all positive COVID patients details\n";
    std::cout << "Press 6 - Exit\n";
    std::cout << "Option -->";
}

bool check_id_exists(std::ifstream& file, const std::string& id)
{
    std::string line;
    file.clear();
    file.seekg(0);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string existing_id;
        std::getline(ss, existing_id, ';');

        if (id == existing_id)
            return true;
    }

    return false;
}

// checks if string entered fits the dd-mm-yyyy format
bool check_date_format(const std::string& date)
{
    std::regex reg(R"(\b(0?[1-9]|[1-2][0-9]|3[0-1])-(0?[1-9]|1[0-2])-\d{4}\b)");

    if (std::regex_match(date, reg))
        return true;

    return false;
}

bool empty_database(std::ifstream& file)
{
    std::string line;
    std::getline(file, line);

    file.clear();
    file.seekg(0);

    if (line == "")
        return true;

    return false;
}

std::tm string_to_date(const std::string& str_date)
{
    std::tm date;
    std::stringstream ss(str_date);
    std::string value;
    std::vector<std::string> vec;

    while (std::getline(ss, value, '-'))
        vec.push_back(value);

    date.tm_mday = std::stoi(vec[0]);
    date.tm_mon = std::stoi(vec[1]);
    date.tm_year = std::stoi(vec[2]);

    return date;
}

std::string date_to_string(std::tm& date)
{
    std::string day = std::to_string(date.tm_mday);
    std::string month = std::to_string(date.tm_mon);
    std::string year = std::to_string(date.tm_year);

    return day + '-' + month + '-' + year;
}

std::string time_to_string(std::tm& time)
{
    std::string seconds = std::to_string(time.tm_sec);
    std::string minutes = std::to_string(time.tm_min);
    std::string hours = std::to_string(time.tm_hour);

    return hours + ':' + minutes + ':' + seconds;
}

// checks is the string is numeric
bool is_num(const std::string& str)
{
    if (std::ranges::all_of(str.begin(), str.end(), [] (char c) {
        return std::isdigit(c) == 1;
    }))
    {
        return true;
    }

    return false;
}

std::string& str_toupper(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    return str;
}

std::string& str_tolower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;
}

void insert_patient_record(PatientRecord& record, const std::string& file_name)
{
    std::ofstream patient_details(file_name, std::ios::app);

    if (patient_details.fail())
        throw std::runtime_error("insert_patient_record() - Failed to open file");

    std::time_t current_time = std::time(nullptr);

    record.date_time = *std::localtime(&current_time);
    record.date_time.tm_year += 1900;

    std::string row {
            record.id + ';' +
            record.name + ';' +
            record.dob + ';' +
            record.address + ';' +
            record.visited_location + ';' +
            record.last_overseas_travel + ';' +
            record.covid_test + ';' +
            record.status + ';' +
            date_to_string(record.date_time) + ' ' + time_to_string(record.date_time)
    };

    patient_details << row << std::endl;
    patient_details.close();
}

void insert_patient_record(PatientRecord& record, std::ofstream& file)
{
    std::time_t current_time = std::time(nullptr);

    record.date_time = *std::localtime(&current_time);
    record.date_time.tm_year += 1900;

    std::string row {
            record.id + ';' +
            record.name + ';' +
            record.dob + ';' +
            record.address + ';' +
            record.visited_location + ';' +
            record.last_overseas_travel + ';' +
            record.covid_test + ';' +
            record.status + ';' +
            date_to_string(record.date_time) + ' ' + time_to_string(record.date_time)
    };

    file << row << std::endl;
}

PatientRecord get_patient_record(std::ifstream& file, const std::string& id)
{
    file.clear();
    file.seekg(0);

    std::string line;
    PatientRecord record;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string found_id;
        std::getline(ss, found_id, ';');

        if (id == found_id)
        {
            record.id = id;
            std::getline(ss, record.name, ';');
            std::getline(ss, record.dob, ';');
            std::getline(ss, record.address, ';');
            std::getline(ss, record.visited_location, ';');
            std::getline(ss, record.last_overseas_travel, ';');
            std::getline(ss, record.covid_test, ';');
            std::getline(ss, record.status, ';');
            return record;
        }
    }

    return PatientRecord();
}

PatientRecord get_patient_record(const std::string& row)
{
    PatientRecord record;

    std::stringstream ss(row);

    std::getline(ss, record.id, ';');
    std::getline(ss, record.name, ';');
    std::getline(ss, record.dob, ';');
    std::getline(ss, record.address, ';');
    std::getline(ss, record.visited_location, ';');
    std::getline(ss, record.last_overseas_travel, ';');
    std::getline(ss, record.covid_test, ';');
    std::getline(ss, record.status, ';');

    return record;
}

void copy_file(const std::string& copy_from, const std::string& copy_to)
{
    std::ifstream input_file(copy_from);
    std::ofstream output_file(copy_to, std::ios::trunc);

    if (input_file.fail() || output_file.fail())
        throw std::runtime_error("copy_file() : Failed to open files");

    std::string line;
    while (std::getline(input_file, line))
    {
        output_file << line << '\n';
    }

    input_file.close();
    output_file.close();
}

void copy_to_temp(std::ifstream& input_file, std::ofstream& output_file, PatientRecord& record)
{
    input_file.clear();
    input_file.seekg(0);

    std::string line;

    while (std::getline(input_file, line))
    {
        std::stringstream ss(line);
        std::string found_id;
        std::getline(ss, found_id, ';');

        if (found_id == record.id) continue;

        output_file << line << std::endl;
    }

    insert_patient_record(record, output_file);
}


void repopulate_main(std::ifstream& input_file, std::ofstream& output_file)
{
    std::string line;

    while (std::getline(input_file, line))
    {
        output_file << line << std::endl;
    }
}

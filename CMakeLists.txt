cmake_minimum_required(VERSION 3.25)
project(Project_Code)

set(CMAKE_CXX_STANDARD 23)

add_executable(Project_Code src/main.cpp src/functions.cpp include/functions.hpp include/patient_record.hpp src/utilities.cpp include/utilities.hpp)

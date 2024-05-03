cmake_minimum_required(VERSION 3.27)
project(csms)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(csms src/main.cpp
        src/computer.cpp
        include/computer.h
        src/employee.cpp
        include/employee.h
        src/task.cpp
        include/task.h)

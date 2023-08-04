cmake_minimum_required(VERSION 3.26)
project(finalpark)

set(CMAKE_CXX_STANDARD 23)

add_executable(finalpark main.cpp
        Customer.cpp
        Customer.h
        Accommodations.cpp
        Accommodations.h
        LuxuryLevel.cpp
        LuxuryLevel.h)

cmake_minimum_required(VERSION 3.26)
project(finalpark)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(finalpark main.cpp
        Sys/User.cpp
        Sys/User.h
        Accommodations.h
        LuxuryLevel.cpp
        LuxuryLevel.h
        Cabin.cpp
        Cabin.h
        HotelRoom.cpp
        HotelRoom.h
        Booking.cpp
        Booking.h
        Parcs.cpp
        Parcs.h
        VacationParcs.cpp
        VacationParcs.h
        Shared.h
        Customer.cpp
        Customer.h
        Sys/Owner.cpp
        Sys/Owner.h
        Sys/Employee.cpp
        Sys/Employee.h
        Sys/OS.cpp
        Sys/OS.h)

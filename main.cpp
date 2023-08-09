#include <iostream>
#include "Parcs.h"
#include "VacationParcs.h"
#include "Sys/Owner.h"
#include "Booking.h"
#include "Sys/Employee.h"
#include "Sys/OS.h"
#include "HotelRoom.h"
#include "Cabin.h"
#include "Sys/FileIO.h"
#include <vector>

int main(){
    VacationParcs vp = VacationParcs("Owner's Vacation Park", "Brusselsesteenweg 80J 2800 Mechelen",
                       "BE280030045567", *new std::vector<Parcs*>, *new std::vector<Customer*>);
    FileIO os(vp);
}
//TODO see vorige todo-s before pushing new main.cpp
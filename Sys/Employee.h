//
// Created by Admin on 8/5/2023.
//

#ifndef FINALPARK_EMPLOYEE_H
#define FINALPARK_EMPLOYEE_H


#include "../Customer.h"
#include "../VacationParcs.h"
#include "../Accommodations.h"
#include "../Booking.h"

class Employee: public Customer{
public:
    //    dunder
    friend std::ostream& operator<<(std::ostream& os, const Employee& obj) {
        os << "Employee ( ID: " << obj.getID() << ", name: " << obj.getName() << ", address: " << obj.getAddress()
           << ", mail: " << obj.getMail() << ", isOnLeave: " << obj.isOnLeave<<" ) ";
        return os;
    }

    Employee(std::string name,std::string address, std::string mail, std::string paymentMethod,bool isOnLeave);
private:
    bool isOnLeave;
};


#endif //FINALPARK_EMPLOYEE_H

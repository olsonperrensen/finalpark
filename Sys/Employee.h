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
//    doing cd ../../
    bool operator==(const User& other) const override {
        const Employee* derivedOther = dynamic_cast<const Employee*>(&other);
        if (derivedOther == nullptr) {
            // The other object is not of type Derived, so the objects are not equal.
            return false;
        }

        // Compare base class members and derived class members.
        return Customer::operator==(other) && (this->isOnLeave==derivedOther->isOnLeave);
    }
    Employee(std::string name,std::string address, std::string mail, std::string paymentMethod,bool isOnLeave);
private:
    bool isOnLeave;
};


#endif //FINALPARK_EMPLOYEE_H

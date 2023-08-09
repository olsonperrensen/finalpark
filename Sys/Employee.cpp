//
// Created by Admin on 8/5/2023.
//

#include "Employee.h"

Employee::Employee(std::string name, std::string address, std::string mail, std::string password,
                   std::string location,std::string paymentMethod,bool isOnLeave) :
Customer(name,address,mail,password,location,paymentMethod),isOnLeave(isOnLeave){}

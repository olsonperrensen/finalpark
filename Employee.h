//
// Created by Admin on 8/5/2023.
//

#ifndef FINALPARK_EMPLOYEE_H
#define FINALPARK_EMPLOYEE_H


#include "Customer.h"
#include "VacationParcs.h"
#include "Accommodations.h"
#include "Booking.h"

class Employee: public Customer{
public:
    //    Acc MGMT
    void modifyAccommodation(VacationParcs &company, int parkID, int accommodationID, const Accommodations &updatedAccommodation);
// Usr MGMT
    void createCustomer(VacationParcs &company, const Customer &newCustomer);
    void modifyCustomer(VacationParcs &company, int customerID, const Customer &updatedCustomer);
    void deleteCustomer(VacationParcs &company, int customerID);
//    Booking MGMT
    void createBooking(VacationParcs &company, int customerID, const Booking &newBooking);
    void modifyBooking(VacationParcs &company, int customerID, int bookingID, const Booking &updatedBooking);
    void deleteBooking(VacationParcs &company, int customerID, int bookingID);

    Employee(std::string name,std::string address, std::string mail, std::string paymentMethod,bool isOnLeave);
private:
    bool isOnLeave;
};


#endif //FINALPARK_EMPLOYEE_H

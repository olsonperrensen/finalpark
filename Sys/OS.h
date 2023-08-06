//
// Created by Admin on 8/6/2023.
//

#ifndef FINALPARK_OS_H
#define FINALPARK_OS_H


#include <vector>
#include "../Customer.h"
#include "../VacationParcs.h"

class OS {
private:
//    TODO since VP already has customers array... maybe discard?
    std::vector<Customer> customers;

    std::vector<VacationParcs> parks;
public:
    void modifyCustomer(VacationParcs &company, int userID, const Customer &updatedCustomer);
    void modifyBooking(VacationParcs &company, int bookingID, const Booking &updatedBooking);
    //    Acc MGMT
    void modifyAccommodation(VacationParcs &company, int parkID, int accommodationID, const Accommodations &updatedAccommodation);
// Usr MGMT
    void createCustomer(VacationParcs &company, const Customer &newCustomer);

    void deleteCustomer(VacationParcs &company, int userID);
//    Booking MGMT
    void createBooking(VacationParcs &company, int customerID, int accommodationID, const Booking& newBooking);

    void deleteBooking(VacationParcs &company, int bookingID);
//    VP part
//    individual Customer adding
//    CLI execs fun
    void registerCustomer(VacationParcs &company,const Customer &newCustomer);
};


#endif //FINALPARK_OS_H

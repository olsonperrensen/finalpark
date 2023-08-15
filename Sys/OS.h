//
// Created by r0834721 - vak YT6254 on 8/6/2023.
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
    static void modifyCustomer(VacationParcs* company, int userID, Customer* updatedCustomer);
    static void modifyBooking(VacationParcs* company, int bookingID, Booking* updatedBooking);
// Usr MGMT
    void createCustomer(VacationParcs* company, Customer* newCustomer);

    static void deleteCustomer(VacationParcs* company, int userID);
//    Booking MGMT
    static void bookAccommodation(VacationParcs* company, int customerID, int accommodationID, Booking* newBooking);

    static void deleteBooking(VacationParcs* company, int bookingID);
};


#endif //FINALPARK_OS_H

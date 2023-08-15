//
// Created by r0834721 - vak YT6254 on 8/6/2023.
//

#include "OS.h"

void OS::modifyCustomer(VacationParcs* company, int userID,  Customer* updatedCustomer) {
    if (Customer* customer = findItemByID(company->getCustomers(), userID)) {
//        MUST DEREFERENCE OTHERWISE DOESN'T WORK...
        *customer = *updatedCustomer;
        std::cout << "modifyCustomer -> Customer " << std::to_string(userID) << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "modifyCustomer -> Error: Customer " << std::to_string(userID) << " not found.\n";
}

void OS::modifyBooking(VacationParcs* company, int bookingID,  Booking* updatedBooking) {
    if (Booking* booking = findItemByID(company->getBookings(), bookingID)) {
        //        MUST DEREFERENCE OTHERWISE DOESN'T WORK...
        *booking = *updatedBooking;
        std::cout << "modifyBooking -> Booking " << std::to_string(bookingID) << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "modifyBooking -> Error: Booking " << std::to_string(bookingID) << " not found.\n";
}

void OS::deleteCustomer(VacationParcs* company, int userID) {
    // Find the booking with the given ID in the list of bookings.
    if (Customer* c = findItemByID(company->getCustomers(), userID)) {
        removeItem(company->getCustomers(),userID);
        std::cout << "deleteCustomer -> Customer " << std::to_string(userID) << " has been deleted successfully." << std::endl;
        return;
    }
    // If the booking is not found, print an error message.
    std::cout << "deleteCustomer -> Error: Customer " << std::to_string(userID) << " not found.\n";
}

void OS::bookAccommodation(VacationParcs* company, int customerID, int accommodationID,  Booking* newBooking) {
    // MUST reference otherwise copy-work :(.
    std::vector<Customer*>& customers = company->getCustomers();
    Customer* customer = findItemByID(customers, customerID);
    if (!customer) {
        std::cout << "bookAccommodation -> Error: Customer " << std::to_string(customerID) << " not found.\n";
        return;
    }

    // CHECK FOR DUPLICATE BOOKINGS
    std::vector<Booking*>& existingBookings = company->getBookings();
    for (Booking* existingBooking : existingBookings) {
        if (existingBooking == newBooking) { // Adapt this comparison to match your needs.
            std::cout << "This booking is already registered.\n";
            return;
        }
    }

    // Find the accommodation with the given ID in the list of accommodations.
    std::vector<Parcs*>& parcs = company->getParcs();
    for (Parcs* parc : parcs) {
        std::vector<Accommodations*>& accommodations = parc->getAccommodations();
        for (auto e: accommodations) {
            std::cout << "bookAccommodation -> GETTING ID: " << *e << std::endl;
        }
        Accommodations* accommodation = findItemByID(accommodations, accommodationID);
        if (accommodation) {
            // Add the new booking to the list of bookings.
            company->addBooking(newBooking);
            std::cout << "bookAccommodation -> Booking " << newBooking->getID() << " has been created successfully.\n";
            return;
        }
    }

    std::cout << "bookAccommodation -> Error: Accommodation " << std::to_string(accommodationID) << " not found.\n";
}


void OS::deleteBooking(VacationParcs* company, int bookingID) {
    // Find the booking with the given ID in the list of bookings.
    if (Booking* booking = findItemByID(company->getBookings(), bookingID)) {
        removeItem(company->getBookings(),bookingID);
        std::cout << "deleteBooking -> Booking " << std::to_string(bookingID) << " has been deleted successfully." << std::endl;
        return;
    }
    // If the booking is not found, print an error message.
    std::cout << "deleteBooking -> Error: Booking " << std::to_string(bookingID) << " not found.\n";
}

void OS::createCustomer(VacationParcs* company, Customer* newCustomer) {
    // CHECK FOR DUPLICATES
    std::vector<Customer*>& existingCustomers = company->getCustomers();
    std::cout << "createCustomer -> Attempting to create user ... First checking for duplicates...\n";
    for (Customer* existingCustomer : existingCustomers) {
        if (*existingCustomer == *newCustomer) {
            std::cout << "createCustomer -> This customer is already registered.\n";
            return;
        }
    }
    // If no duplicate found, register the new customer
    company->registerCustomer(newCustomer);
}

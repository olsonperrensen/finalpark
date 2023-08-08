//
// Created by Admin on 8/6/2023.
//

#include "OS.h"

void OS::modifyCustomer(VacationParcs &company, int userID,  Customer* updatedCustomer) {
    if (Customer* customer = findItemByID(company.getCustomers(), userID)) {
//        MUST DEREFERENCE OTHERWISE DOESN'T WORK...
        *customer = *updatedCustomer;
        std::cout << "modifyCustomer -> Customer " << userID << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "modifyCustomer -> Error: Customer not found.\n";
}

void OS::modifyBooking(VacationParcs &company, int bookingID,  Booking* updatedBooking) {
    if (Booking* booking = findItemByID(company.getBookings(), bookingID)) {
        //        MUST DEREFERENCE OTHERWISE DOESN'T WORK...
        *booking = *updatedBooking;
        std::cout << "modifyBooking -> Booking " << bookingID << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "modifyBooking -> Error: Booking not found.\n";
}

void OS::modifyAccommodation(VacationParcs &company, int parkID, int accommodationID,Accommodations* updatedAccommodation) {
//    POLYMORPHISM happens right here. It is here that the pointer is getting the right call to which function to execute
// based on the right derived class (HotelRoom) or (Cabin) the pointer is pointing to
    // Find the park with the given ID in the list of parks.
    std::vector<Parcs*>& parcs = company.getParcs();  // MUST reference otherwise copy-work :(

    if (Parcs* parc = findItemByID(parcs, parkID)) {
        // Find the accommodation with the given ID in the list of accommodations.
//        NESTED var init (again) so mem doesn't get wasted
        if (Accommodations* accommodation = findItemByID(parc->getAccommodations(), accommodationID)) {
            *accommodation = *updatedAccommodation;
            std::cout << "modifyAccommodation -> Accommodation " << accommodationID << " has been modified successfully." << std::endl;
            return;
        }
        std::cout << "modifyAccommodation -> Error: Accommodation not found.\n";
        return;
    }
    std::cout << "modifyAccommodation -> Error: Park not found.\n";
}

void OS::deleteCustomer(VacationParcs &company, int userID) {
    // Find the booking with the given ID in the list of bookings.
    if (Customer* c = findItemByID(company.getCustomers(), userID)) {
        removeItem(company.getCustomers(),userID);
        std::cout << "deleteCustomer -> Customer " << userID << " has been deleted successfully." << std::endl;
        return;
    }
    // If the booking is not found, print an error message.
    std::cout << "deleteCustomer -> Error: Customer not found.\n";
}

void OS::bookAccommodation(VacationParcs &company, int customerID, int accommodationID,  Booking* newBooking) {
    // MUST reference otherwise copy-work :(.
    std::vector<Customer*>& customers = company.getCustomers();
    Customer* customer = findItemByID(customers, customerID);
    if (!customer) {
        std::cout << "bookAccommodation -> Error: Customer not found.\n";
        return;
    }

    // CHECK FOR DUPLICATE BOOKINGS
    std::vector<Booking*>& existingBookings = company.getBookings();
    for (Booking* existingBooking : existingBookings) {
        if (existingBooking == newBooking) { // Adapt this comparison to match your needs.
            std::cout << "This booking is already registered.\n";
            return;
        }
    }

    // Find the accommodation with the given ID in the list of accommodations.
    std::vector<Parcs*>& parcs = company.getParcs();
    for (Parcs* parc : parcs) {
        std::vector<Accommodations*>& accommodations = parc->getAccommodations();
        for (auto e: accommodations) {
            std::cout << "bookAccommodation -> GETTING ID: " << *e << std::endl;
        }
        Accommodations* accommodation = findItemByID(accommodations, accommodationID);
        if (accommodation) {
            // Add the new booking to the list of bookings.
            company.addBooking(newBooking);
            std::cout << "bookAccommodation -> Booking " << newBooking->getID() << " has been created successfully.\n";
            return;
        }
    }

    std::cout << "bookAccommodation -> Error: Accommodation not found.\n";
}


void OS::deleteBooking(VacationParcs &company, int bookingID) {
    // Find the booking with the given ID in the list of bookings.
    if (Booking* booking = findItemByID(company.getBookings(), bookingID)) {
        removeItem(company.getBookings(),bookingID);
        std::cout << "deleteBooking -> Booking " << bookingID << " has been deleted successfully." << std::endl;
        return;
    }
    // If the booking is not found, print an error message.
    std::cout << "deleteBooking -> Error: Booking not found.\n";
}

void OS::createCustomer(VacationParcs &company, Customer* newCustomer) {
    // CHECK FOR DUPLICATES
    std::vector<Customer*>& existingCustomers = company.getCustomers();
    std::cout << "createCustomer -> Attempting to create user ... First checking for duplicates...\n";
    for (Customer* existingCustomer : existingCustomers) {
        if (*existingCustomer == *newCustomer) {
            std::cout << "createCustomer -> This customer is already registered.\n";
            return;
        }
    }
    // If no duplicate found, register the new customer
    company.registerCustomer(newCustomer);
}

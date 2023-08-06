//
// Created by Admin on 8/6/2023.
//

#include "OS.h"

void OS::modifyCustomer(VacationParcs &company, int userID, const Customer &updatedCustomer) {
    if (Customer* customer = findItemByID(company.getCustomers(), userID)) {
        *customer = updatedCustomer;
        std::cout << "modifyCustomer -> Customer " << userID << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "modifyCustomer -> Error: Customer not found.\n";
}

void OS::modifyBooking(VacationParcs &company, int bookingID, const Booking &updatedBooking) {
    if (Booking* booking = findItemByID(company.getBookings(), bookingID)) {
        *booking = updatedBooking;
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
            std::cout << "Accommodation " << accommodationID << " has been modified successfully." << std::endl;
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
    // Find the customer with the given ID in the list of customers.
    std::vector<Customer*>& customers = company.getCustomers();  // MUST reference otherwise copy-work :(
    Customer* customer = findItemByID(customers, customerID);
    if (!customer) {
        std::cout << "bookAccommodation -> Error: Customer not found.\n";
        return;
    }

    // Find the accommodation with the given ID in the list of accommodations.
    std::vector<Parcs*>& parcs = company.getParcs();  // MUST reference otherwise copy-work :(
    for (Parcs* parc : parcs) {
        std::vector<Accommodations*>& accommodations = parc->getAccommodations();  // MUST reference otherwise copy-work :(
//        DEBUG
//        for (auto e:accommodations) {
//            std::cout << "bookAccommodation -> GETTING ID: " << *e << std::endl;
//        }
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
    company.registerCustomer(newCustomer);
}
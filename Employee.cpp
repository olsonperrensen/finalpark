//
// Created by Admin on 8/5/2023.
//

#include "Employee.h"

Employee::Employee(std::string name, std::string address, std::string mail, std::string paymentMethod,bool isOnLeave) :
Customer(name,address,mail,paymentMethod),isOnLeave(isOnLeave){

}

void Employee::createCustomer(VacationParcs &company, const Customer &newCustomer) {
    company.addCustomer(newCustomer);
}

void Employee::modifyCustomer(VacationParcs &company, int userID, const Customer &updatedCustomer) {
    if (Customer* customer = findItemByID(company.getCustomers(), userID)) {
        *customer = updatedCustomer;
        std::cout << "Customer " << userID << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "Error: Customer not found.\n";
}

void Employee::deleteBooking(VacationParcs &company, int bookingID) {
    // Find the booking with the given ID in the list of bookings.
    if (Booking* booking = findItemByID(company.getBookings(), bookingID)) {
        // If the booking is found, remove it from the list of bookings.
//        Good to know: Before calling .remove be sure you have a way to compare 2 full Objects and not its attributes...
//        Use operator== overloading to achieve this
        company.getBookings().erase(std::remove(company.getBookings().begin(), company.getBookings().end(), *booking), company.getBookings().end());
        std::cout << "Booking " << bookingID << " has been deleted successfully." << std::endl;
        return;
    }
    // If the booking is not found, print an error message.
    std::cout << "Error: Booking not found.\n";
}


void Employee::createBooking(VacationParcs &company, int customerID, int accommodationID, const Booking& newBooking) {
    // Find the customer with the given ID in the list of customers.
    std::vector<Customer>& customers = company.getCustomers();  // MUST reference otherwise copy-work :(
    Customer* customer = findItemByID(customers, customerID);
    if (!customer) {
        std::cout << "Error: Customer not found.\n";
        return;
    }

    // Find the accommodation with the given ID in the list of accommodations.
    std::vector<Parcs>& parcs = company.getParcs();  // MUST reference otherwise copy-work :(
    for (Parcs& parc : parcs) {
        std::vector<Accommodations>& accommodations = parc.getAccommodations();  // MUST reference otherwise copy-work :(
        Accommodations* accommodation = findItemByID(accommodations, accommodationID);
        if (accommodation) {
            // Add the new booking to the list of bookings.
            company.addBooking(newBooking);
            std::cout << "Booking " << newBooking.getID() << " has been created successfully.\n";
            return;
        }
    }

    std::cout << "Error: Accommodation not found.\n";
}

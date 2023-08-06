//
// Created by Admin on 8/4/2023.
//

#include <algorithm>
#include "VacationParcs.h"
#include "Customer.h"

const std::string &VacationParcs::getVAT() const {
    return VAT;
}

void VacationParcs::setVAT(const std::string &vat) {
    VAT = vat;
}

 std::vector<Customer> &VacationParcs::getCustomers()  {
    return customers;
}

void VacationParcs::setCustomers(const std::vector<Customer> &customers) {
    VacationParcs::customers = customers;
}

VacationParcs::VacationParcs(std::string bizName, std::string bizAddress,
                             std::string VAT, std::vector<Parcs*> parcs, std::vector<Customer> customers)
                             : bizName(bizName),bizAddress(bizAddress),VAT(VAT),parcs(parcs),customers(customers){}

void VacationParcs::addPark(Parcs* park) {
    addItem(parcs, park);
}

void VacationParcs::removePark(int id) {
    removeItem(parcs, id);
}

void VacationParcs::modifyPark(int parkID, const Parcs &updatedPark) {
    // Find the park with the given ID in the list of parks.

//        std::cout << "preivous id: " << park.getID() << " checking with given ID" << parkID;
        if (Parcs* parc = findItemByID(parcs, parkID)) {
            // If the park is found, modify its attributes.
//            IMPORTANT: Derenfece pointer otherwise your only changing where it points to!
            *parc = updatedPark;
            std::cout << "Park " << parkID <<" has been modified successfully." << std::endl;
            return;
        }

    // If the park is not found, print an error message.
    std::cout << "Error: Park not found.\n";
}

const std::string &VacationParcs::getBizName() const {
    return bizName;
}

void VacationParcs::setBizName(const std::string &bizName) {
    this->bizName = bizName;
}

const std::string &VacationParcs::getBizAddress() const {
    return bizAddress;
}

void VacationParcs::setBizAddress(const std::string &bizAddress) {
    this->bizAddress = bizAddress;
}

void VacationParcs::changeParkSrv(int parcID,int srvToBeChanged,bool state) {
    if (Parcs* parc = findItemByID(parcs, parcID)) {
        switch (srvToBeChanged) {
            using enum ESERVICES;
            case static_cast<int>(SUBTROPIC_SWIMMING_POOL):
                parc->getServices().setSubtropicSwimmingPool(state);
                std::cout << "Subtropic swimming pool service has been turned "<< (state?"on":"off") << "." << std::endl;
                break;
            case static_cast<int>(SPORTS_INFRASTRUCTURE):
                parc->getServices().setSportsInfrastructure(state);
                std::cout << "Sports infrastructure service has been turned "<< (state?"on":"off") << "." << std::endl;
                break;
            case static_cast<int>(BOWLING_ALLEY):
                parc->getServices().setBowlingAlley(state);
                std::cout << "Bowling alley service has been turned "<< (state?"on":"off") << "." << std::endl;
                break;
            case static_cast<int>(BICYCLE_RENT):
                parc->getServices().setBicycleRent(state);
                std::cout << "Bicycle rent service has been turned "<< (state?"on":"off") << "." << std::endl;
                break;
            case static_cast<int>(CHILDRENS_PARADISE):
                parc->getServices().setChildrensParadise(state);
                std::cout << "Children's paradise service has been turned "<< (state?"on":"off") << "." << std::endl;
                break;
            case static_cast<int>(WATER_BIKES):
                parc->getServices().setWaterBikes(state);
                std::cout << "Water bikes service has been turned off "<< (state?"on":"off") << "." << std::endl;
                break;
            default:
                std::cout << "Invalid service ID." << std::endl;
                break;
        }
    } else {
        std::cout << "Could not find a park with the given ID." << std::endl;
    }
}

void VacationParcs::addCustomer(const Customer& neuCustomer) {
//    Vanilla - No checks!
    customers.push_back(neuCustomer);
}

void VacationParcs::registerCustomer(const Customer &newCustomer) {
    // TODO With if checks so all data is valid
    addCustomer(newCustomer);
    std::cout << "Customer " << newCustomer.getID() << " has registered successfully." << std::endl;
}


 std::vector<Booking> &VacationParcs::getBookings() {
    return bookings;
}

void VacationParcs::setBookings(const std::vector<Booking> &bookings) {
    VacationParcs::bookings = bookings;
}

void VacationParcs::addBooking(const Booking &newBooking) {
    bookings.push_back(newBooking);
}

 std::vector<Parcs *> &VacationParcs::getParcs()  {
    return parcs;
}

void VacationParcs::setParcs(const std::vector<Parcs *> &parcs) {
    VacationParcs::parcs = parcs;
}

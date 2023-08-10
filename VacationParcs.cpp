//
// Created by Admin on 8/4/2023.
//
#include "VacationParcs.h"
#include "Customer.h"

const std::string &VacationParcs::getVAT() const {
    return VAT;
}

void VacationParcs::setVAT(const std::string &vat) {
    VAT = vat;
}

VacationParcs::VacationParcs(std::string bizName, std::string bizAddress,
                             std::string VAT, std::vector<Parcs*> parcs, std::vector<Customer*> customers)
                             : bizName(bizName),bizAddress(bizAddress),VAT(VAT),parcs(parcs),customers(customers){}

void VacationParcs::addPark(Parcs* park) {
    addItem(parcs, park);
}

void VacationParcs::removePark(int id) {
    std::cout << "removePark -> Attempting to delete parc " << std::to_string(id) << std::endl;
    removeItem(parcs, id);
}

Parcs* VacationParcs::findParcByID(int parkID) {
    // Find the park with the given ID in the list of parks.
        if (Parcs* parc = findItemByID(parcs, parkID)) {
            // If the park is found.
            return parc;
        }

    // If the park is not found, print an error message.
    std::cout << "modifyPark -> Error: Parcs " << std::to_string(parkID) << " not found.\n";
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
                parc->getServices()->setSubtropicSwimmingPool(state);
                std::cout << "changeParkSrv -> Subtropic swimming pool service has been turned "<< (state?"on":"off") << ".";
                break;
            case static_cast<int>(SPORTS_INFRASTRUCTURE):
                parc->getServices()->setSportsInfrastructure(state);
                std::cout << "changeParkSrv -> Sports infrastructure service has been turned "<< (state?"on":"off") << ".";
                break;
            case static_cast<int>(BOWLING_ALLEY):
                parc->getServices()->setBowlingAlley(state);
                std::cout << "changeParkSrv -> Bowling alley service has been turned "<< (state?"on":"off") << ".";
                break;
            case static_cast<int>(BICYCLE_RENT):
                parc->getServices()->setBicycleRent(state);
                std::cout << "changeParkSrv -> Bicycle rent service has been turned "<< (state?"on":"off") << ".";
                break;
            case static_cast<int>(CHILDRENS_PARADISE):
                parc->getServices()->setChildrensParadise(state);
                std::cout << "changeParkSrv -> Children's paradise service has been turned "<< (state?"on":"off") << ".";
                break;
            case static_cast<int>(WATER_BIKES):
                parc->getServices()->setWaterBikes(state);
                std::cout << "changeParkSrv -> Water bikes service has been turned off "<< (state?"on":"off") << ".";
                break;
            default:
                std::cout << "changeParkSrv -> Invalid service ID.";
                break;
        }
        std::cout << "Applies only to Parc: " << parc->getID() << " " << parc->getName()<< std::endl;
    } else {
        std::cout << "changeParkSrv -> Could not find a park with the given ID.";
    }
}

void VacationParcs::addCustomer(Customer* neuCustomer) {
//    Vanilla - No checks!
    customers.push_back(neuCustomer);
}

void VacationParcs::registerCustomer(Customer* newCustomer) {

    addCustomer(newCustomer);
    std::cout << "registerCustomer -> Customer " << newCustomer->getID() << " has registered successfully." << std::endl;
}

void VacationParcs::addBooking(Booking* newBooking) {
    bookings.push_back(newBooking);
}

 std::vector<Parcs *> &VacationParcs::getParcs()  {
    return parcs;
}

void VacationParcs::setParcs(const std::vector<Parcs *> &parcs) {
    VacationParcs::parcs = parcs;
}

 std::vector<Booking *> &VacationParcs::getBookings()  {
    return bookings;
}

void VacationParcs::setBookings(const std::vector<Booking *> &bookings) {
    VacationParcs::bookings = bookings;
}

 std::vector<Customer *> &VacationParcs::getCustomers()  {
    return customers;
}

void VacationParcs::setCustomers(const std::vector<Customer *> &customers) {
    VacationParcs::customers = customers;
}
//        trouwens use of Constructor Overloading
VacationParcs::VacationParcs(std::string name, std::string address, std::string VAT, std::vector<Parcs *> parcs,
                             std::vector<Customer *> customers, std::vector<Booking *> bookings)
                             :bizName(name),bizAddress(address),VAT(VAT),parcs(parcs),customers(customers),bookings(bookings){

}

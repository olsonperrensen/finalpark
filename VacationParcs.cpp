//
// Created by Admin on 8/4/2023.
//

#include <algorithm>
#include "VacationParcs.h"
#include "Customer.h"

const std::string &VacationParcs::getVat() const {
    return VAT;
}

void VacationParcs::setVat(const std::string &vat) {
    VAT = vat;
}

const std::vector<Parcs> &VacationParcs::getParcs() const {
    return parcs;
}

void VacationParcs::setParcs(const std::vector<Parcs> &parcs) {
    VacationParcs::parcs = parcs;
}

const std::vector<Customer> &VacationParcs::getCustomers() const {
    return customers;
}

void VacationParcs::setCustomers(const std::vector<Customer> &customers) {
    VacationParcs::customers = customers;
}

VacationParcs::VacationParcs(std::string name, std::string address, ParcServices services,
                             std::vector<Accommodations> accommodations, std::string VAT, std::vector<Parcs> parcs,
                             std::vector<Customer> customers) : Parcs(name, address, services, accommodations),
                                                            VAT(VAT), parcs(parcs), customers(customers){

}

void VacationParcs::addPark(const Parcs &park) {
    addItem(parcs, park);
}

void VacationParcs::removePark(int id) {
    removeItem(parcs, id);
}

void VacationParcs::modifyPark(int parkID, const Parcs &updatedPark) {
    // Find the park with the given ID in the list of parks.
    for (Parcs& park : parcs) {
//        std::cout << "preivous id: " << park.getID() << " checking with given ID" << parkID;
        if (park.getID() == parkID) {
            // If the park is found, modify its attributes.
            park = updatedPark;
            std::cout << "Park " << parkID <<" has been modified successfully." << std::endl;
            return;
        }
    }

    // If the park is not found, print an error message.
    std::cout << "Error: Park not found.\n";
}

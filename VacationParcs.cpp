//
// Created by Admin on 8/4/2023.
//

#include <algorithm>
#include "VacationParcs.h"

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
                             VAT(VAT),parcs(parcs),customers(customers){

}

void VacationParcs::addPark(Parcs park) {
//    As the function name suggests, push to vector
    parcs.push_back(park);
}

void VacationParcs::removePark(int parkID)
{
    // Find the park to be removed using std::find_if and a lambda function
    auto parkToRemove = std::find_if(parcs.begin(), parcs.end(), [&](const Parcs& p) {
        return p.getParcId() == parkID;
    });

    // If the park was found, erase it from the vector
    if (parkToRemove != parcs.end()) {
        parcs.erase(parkToRemove);
        std::cout << "Deleted park with ID " << parkID << std::endl;
    } else {
        std::cout << "Park with ID " << parkID << " not found." << std::endl;
    }
}



//
// Created by Admin on 8/4/2023.
//

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

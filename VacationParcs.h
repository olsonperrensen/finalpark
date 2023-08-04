//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_VACATIONPARCS_H
#define FINALPARK_VACATIONPARCS_H
#include <string>
#include <vector>
#include "Parcs.h"
#include "Customer.h"

class VacationParcs: public Parcs{
private:
    std::string VAT;
//    Voor alle duidelijkheid:
// ***********************************************************************************************
//    This attribute represents the collection of all the parks that the vacation company manages.
//    Each item in the vector is an instance of the Parcs class, which represents a single park.
//    This is necessary because a vacation company typically manages multiple parks.
//    If VacationParcs is meant to represent a company that manages multiple parks,
//    then it would make sense for it to have a std::vector<Parcs> parcs attribute.
// ***********************************************************************************************
    std::vector<Parcs> parcs;
    std::vector<Customer> customers;
public:
    VacationParcs(std::string name, std::string address, ParcServices services,
                  std::vector<Accommodations> accommodations, std::string VAT, std::vector<Parcs> parcs,
                  std::vector<Customer> customers);

//    Own methods needed for the program to work
    void addPark(Parcs park);
    void removePark(int parkID);

    const std::string &getVat() const;

    void setVat(const std::string &vat);

    const std::vector<Parcs> &getParcs() const;

    void setParcs(const std::vector<Parcs> &parcs);

    const std::vector<Customer> &getCustomers() const;

    void setCustomers(const std::vector<Customer> &customers);
};


#endif //FINALPARK_VACATIONPARCS_H

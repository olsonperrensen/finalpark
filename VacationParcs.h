//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_VACATIONPARCS_H
#define FINALPARK_VACATIONPARCS_H
#include <string>
#include <vector>
#include "Parcs.h"
#include "User.h"
#include "Shared.h"
#include "Customer.h"

// Inheriting from Parcs would cause duplicates since a VacationParc could have by its own:
// vp.getAccommodations().at(0); and at the same time
//   vp.getParcs().at(0).getAccommodations().at(0);
// Not worth the hassle. So no inheritance taking place. More of a composition relationship
// Note below
class VacationParcs{
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
//    Managing a business so these attributes from Parc are redefined here for sole convenience
    std::string bizName;
    std::string bizAddress;
public:
    const std::string &getBizName() const;

    void setBizName(const std::string &bizName);

    const std::string &getBizAddress() const;

    void setBizAddress(const std::string &bizAddress);

public:
    friend std::ostream& operator<<(std::ostream& os, const VacationParcs& obj) {
        os << "VacationParcs ( name: " << obj.getBizName() << ", address: " << obj.getBizAddress()
           << ", VAT: " << obj.getVAT() << ", Parcs: " << obj.getParcs().at(0) << ", Customers: " <<
           obj.getCustomers().at(0) << " ) "; // TODO vectorize output
        return os;
    }
    VacationParcs(std::string name, std::string address,
                  std::string VAT, std::vector<Parcs> parcs,
                  std::vector<Customer> customers);

//    Make good use of templates
    void addPark(const Parcs& park);
    void removePark(int id);

    const std::string &getVAT() const;

    void setVAT(const std::string &vat);

    const std::vector<Parcs> &getParcs() const;

    void setParcs(const std::vector<Parcs> &parcs);

    const std::vector<Customer> &getCustomers() const;

    void setCustomers(const std::vector<Customer> &customers);

//    Own logic for MGMT
    void modifyPark(int parkID, const Parcs &updatedPark);
};


#endif //FINALPARK_VACATIONPARCS_H

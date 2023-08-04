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
    std::vector<Parcs> parcs;
    std::vector<Customer> customers;
public:
    VacationParcs(std::string name, std::string address, ParcServices services,
                  std::vector<Accommodations> accommodations, std::string VAT, std::vector<Parcs> parcs,
                  std::vector<Customer> customers);

    const std::string &getVat() const;

    void setVat(const std::string &vat);

    const std::vector<Parcs> &getParcs() const;

    void setParcs(const std::vector<Parcs> &parcs);

    const std::vector<Customer> &getCustomers() const;

    void setCustomers(const std::vector<Customer> &customers);
};


#endif //FINALPARK_VACATIONPARCS_H

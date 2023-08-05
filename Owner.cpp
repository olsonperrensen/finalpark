//
// Created by Admin on 8/5/2023.
//

#include "Owner.h"

Owner::Owner(std::string name, std::string address, std::string mail) : User(name, address, mail) {

}

void Owner::createPark(VacationParcs &company, const Parcs &park) {
    company.addPark(park);
    std::cout << "A new parc has been created" << std::endl;
}

void Owner::modifyPark(VacationParcs &company, int parkID, const Parcs &updatedPark) {
    company.modifyPark(parkID, updatedPark);
}

void Owner::deletePark(VacationParcs &company, int parkID) {
    company.removePark(parkID);
    std::cout << "Parc " << parkID << " has been deleted" << std::endl;
}

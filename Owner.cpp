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
}

void Owner::createAccommodation(VacationParcs &company, int parkID, const Accommodations &newAccommodation) {
     std::vector<Parcs> parcs = company.getParcs();
//     Ampersand needed (reference) in order for changes to take effect (call by reference)
    for (Parcs &parc:parcs) {
        if (parc.getID() == parkID) {
            // Add the new accommodation to the park
            parc.addAccommodation(newAccommodation);
        } else {
            std::cout << "Your Parc number does not match with our records. Nothing could be found.\n";
        }
    }
}

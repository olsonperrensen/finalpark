//
// Created by Admin on 8/5/2023.
//

#include "Owner.h"

Owner::Owner(std::string name, std::string address, std::string mail) : User(name, address, mail) {

}

void Owner::createPark(VacationParcs &company, Parcs* park) {
    company.addPark(park);
    std::cout << "createPark -> A new parc (ID: " << park->getID() << ", Name: "<< park->getName() <<") has been created" << std::endl;
}

void Owner::modifyPark(VacationParcs &company, int parkID, const Parcs &updatedPark) {
    company.modifyPark(parkID, updatedPark);
}

void Owner::deletePark(VacationParcs &company, int parkID) {
    company.removePark(parkID);
}

void Owner::createAccommodation(VacationParcs &company, int parkID, Accommodations *newAccommodation) {
    std::vector<Parcs*>& parcs = company.getParcs();  // MUST reference otherwise copy-work :(
    for (Parcs* parc : parcs) {
        if (parc->getID() == parkID) {
            // Add the new accommodation to the park
            parc->addAccommodation(newAccommodation);
        } else {
            std::cout << "createAccommodation -> Your Parc number does not match with our records. Nothing could be found.\n";
        }
    }
}

void Owner::modifyAccommodations(VacationParcs &company, int parkID,  std::vector<Accommodations*> &updatedAccommodations) {
    std::vector<Parcs*>& parcs = company.getParcs();  // MUST reference otherwise copy-work :(
            // Add the new accommodationS IN BULK to the park
            //             for one modification only ipv bulk... check modifyAccommodation
    if (Parcs* parc = findItemByID(parcs, parkID))
    {
        parc->setAccommodations(updatedAccommodations);
        std::cout << "modifyAccommodations -> Bulk accommodation modification completed!\n";
    }
     else
        std::cout << "modifyAccommodations -> Your Parc number does not match with our records. Nothing could be found.\n";
}

void Owner::deleteAccommodation(VacationParcs &company, int parkID, int accommodationID) {
    std::vector<Parcs*>& parcs = company.getParcs();  // MUST reference otherwise copy-work :(

    if (Parcs* parc = findItemByID(parcs, parkID))
        parc->removeAccommodation(accommodationID);
    else
        std::cout << "deleteAccommodation -> Your Parc number does not match with our records. Nothing could be found.\n";
}

void Owner::changeService(VacationParcs &company, int parkID, const int srvToBeChanged, const bool state) {
    company.changeParkSrv(parkID,srvToBeChanged,state);
}

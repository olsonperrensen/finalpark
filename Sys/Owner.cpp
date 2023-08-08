//
// Created by Admin on 8/5/2023.
//

#include "Owner.h"

Owner::Owner(std::string name, std::string address, std::string mail,std::string password) :
User(name, address, mail),password(password) {}

void Owner::createPark(VacationParcs &company, Parcs* park) {
    // CHECK FOR DUPLICATES
    std::cout << "createPark -> Attempting to add park. First checking against duplicates.\n";
    std::vector<Parcs*>& existingParks = company.getParcs();
    for (Parcs* existingPark : existingParks) {
        if (existingPark == park) { // Adapt this comparison to match your needs.
            std::cout << "createPark -> This park is already registered.\n";
            return;
        }
    }
    // If no duplicate found, add the new park
    company.addPark(park);
    std::cout << "createPark -> A new parc (ID: " << park->getID() << ", Name: "<< park->getName() <<") has been created" << std::endl;
}

void Owner::modifyPark(VacationParcs &company, int parkID, const Parcs &updatedPark) {
    company.modifyPark(parkID, updatedPark);
}

void Owner::deletePark(VacationParcs &company, int parkID) {
    std::cout << "deletePark -> Attempting to delete parc " << parkID << std::endl;
    company.removePark(parkID);
}

void Owner::createAccommodation(VacationParcs &company, int parkID, Accommodations *newAccommodation) {
    std::vector<Parcs*>& parcs = company.getParcs();
    for (Parcs* parc : parcs) {
        if (parc->getID() == parkID) {
            std::cout << "createAccommodation -> Trying to add new accommodation " << "to Parc (parkID): " << parkID << std::endl;
            // CHECK FOR DUPLICATES
            std::vector<Accommodations*>& existingAccommodations = parc->getAccommodations();
            for (Accommodations* existingAccommodation : existingAccommodations) {
                if (*existingAccommodation == *newAccommodation) { // DEREFERENCE NEEDED OTHERWISE COMPARING by identity (i.e., they are the same object).
//                    actually need to compare by their data and operator== overloading helps solve this!
                    std::cout << "createAccommodation -> This accommodation already exists in this park.\n";
                    return;
                }
            }
            // If no duplicate found, add the new accommodation
            parc->addAccommodation(newAccommodation);
            return;
        }
    }
    std::cout << "createAccommodation -> Your Parc number does not match with our records. Nothing could be found. Using user-given ParcID: " << parkID << "\n";
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

const std::string &Owner::getPassword() const {
    return password;
}

void Owner::setPassword(const std::string &password) {
    Owner::password = password;
}

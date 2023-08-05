//
// Created by Admin on 8/5/2023.
//

#ifndef FINALPARK_OWNER_H
#define FINALPARK_OWNER_H


#include "User.h"
#include "Parcs.h"
#include "VacationParcs.h"

class Owner: public User{
public:
//    dunder normally comes from User but output is also User, so I prefer making custom overloading
    friend std::ostream& operator<<(std::ostream& os, const Owner& obj) {
        os << "Owner ( name: " << obj.getName() << ", address: " << obj.getAddress() << " ) ";
        return os;
    }
    Owner(std::string name, std::string address, std::string mail);

// Parc-related own funs for MGMT
    static void createPark(VacationParcs& company, const Parcs& park);
    void modifyPark(VacationParcs& company, int parkID, const Parcs& updatedPark);
    void deletePark(VacationParcs& company, int parkID);

//    Accommodation-related own funs for MGMT
    void createAccommodation(VacationParcs &company, int parkID, const Accommodations &newAccommodation);
    void modifyAccommodations(VacationParcs &company, int parkID, const std::vector<Accommodations> &updatedAccommodation);
    void deleteAccommodation(VacationParcs &company, int parkID, int accommodationID);
};


#endif //FINALPARK_OWNER_H

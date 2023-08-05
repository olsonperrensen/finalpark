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
    Owner(std::string name, std::string address, std::string mail);
    static void createPark(VacationParcs& company, const Parcs& park);
    void modifyPark(VacationParcs& company, int parkID, const Parcs& updatedPark);
    void deletePark(VacationParcs& company, int parkID);
};


#endif //FINALPARK_OWNER_H

//
// Created by Admin on 8/4/2023.
//

#include "Accommodations.h"

unsigned short int Accommodations::aantalAccommodations = 0;

unsigned short int Accommodations::getID() const {
    return accommodationID;
}

int Accommodations::getNrPeople() const {
    return nrPeople;
}

void Accommodations::setNrPeople(int nrPeople) {
    Accommodations::nrPeople = nrPeople;
}

int Accommodations::getSize() const {
    return size;
}

void Accommodations::setSize(int size) {
    Accommodations::size = size;
}

bool Accommodations::isBathroomWithBath() const {
    return bathroomWithBath;
}

void Accommodations::setBathroomWithBath(bool bathroomWithBath) {
    Accommodations::bathroomWithBath = bathroomWithBath;
}

LuxuryLevel *Accommodations::getLuxuryLevel() const {
    return luxuryLevel;
}

void Accommodations::setLuxuryLevel(LuxuryLevel *luxuryLevel) {
    Accommodations::luxuryLevel = luxuryLevel;
}

Accommodations::Accommodations(int nrPeople, int size, bool bathroomWithBath, LuxuryLevel* luxuryLevel):
       nrPeople(nrPeople),size(size),bathroomWithBath(bathroomWithBath){

    this->luxuryLevel = luxuryLevel;
    this->accommodationID = ++Accommodations::aantalAccommodations;
}
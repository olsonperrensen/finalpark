//
// Created by Admin on 8/4/2023.
//

#include "Cabin.h"

int Cabin::getBedrooms() const {
    return bedrooms;
}

void Cabin::setBedrooms(int bedrooms) {
    Cabin::bedrooms = bedrooms;
}

Cabin::Cabin(int id, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int bedrooms)
// Since it is a derived class, calling Base is needed, otherwise complaints.
        : Accommodations(), bedrooms(bedrooms) {

}

int Cabin::getID() const  {
    return ID;
}

void Cabin::setId(int id) {
    ID = id;
}

int Cabin::getNrPeople() const {
    return nrPeople;
}

void Cabin::setNrPeople(int nrPeople) {
    Cabin::nrPeople = nrPeople;
}

int Cabin::getSize() const {
    return size;
}

void Cabin::setSize(int size) {
    Cabin::size = size;
}

bool Cabin::isBathroomWithBath() const {
    return bathroomWithBath;
}

void Cabin::setBathroomWithBath(bool bathroomWithBath) {
    Cabin::bathroomWithBath = bathroomWithBath;
}

const LuxuryLevel &Cabin::getLuxuryLevel() const {
    return luxuryLevel;
}

void Cabin::setLuxuryLevel(const LuxuryLevel &luxuryLevel) {
    Cabin::luxuryLevel = luxuryLevel;
}

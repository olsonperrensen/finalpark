//
// Created by r0834721 - vak YT6254 on 8/4/2023.
//

#include "Cabin.h"

int Cabin::getBedrooms() const {
    return bedrooms;
}

void Cabin::setBedrooms(int bedrooms) {
    Cabin::bedrooms = bedrooms;
}

Cabin::Cabin(int nrPeople, int size, bool bathroomWithBath, LuxuryLevel* luxuryLevel,int bedrooms): bedrooms(bedrooms) {
    this->nrPeople = nrPeople;
    this->size = size;
    this->bathroomWithBath = bathroomWithBath;
    this->luxuryLevel = luxuryLevel;
}

unsigned short int Cabin::getID() const  {
    return accommodationID;
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

LuxuryLevel *Cabin::getLuxuryLevel() const {
    return luxuryLevel;
}

void Cabin::setLuxuryLevel(LuxuryLevel *luxuryLevel) {
    Cabin::luxuryLevel = luxuryLevel;
}

void Cabin::setAccommodationId(unsigned short accommodationId) {
    accommodationID = accommodationId;
}

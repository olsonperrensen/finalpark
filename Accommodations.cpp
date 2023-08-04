//
// Created by Admin on 8/4/2023.
//

#include "Accommodations.h"

int Accommodations::getId() const {
    return ID;
}

void Accommodations::setId(int id) {
    ID = id;
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

const LuxuryLevel &Accommodations::getLuxuryLevel() const {
    return luxuryLevel;
}

void Accommodations::setLuxuryLevel(const LuxuryLevel &luxuryLevel) {
    Accommodations::luxuryLevel = luxuryLevel;
}

Accommodations::Accommodations(int ID, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel):
ID(ID),nrPeople(nrPeople),size(size),bathroomWithBath(bathroomWithBath),luxuryLevel(luxuryLevel){

}

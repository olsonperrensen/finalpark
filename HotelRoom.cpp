//
// Created by Admin on 8/4/2023.
//

#include "HotelRoom.h"

int HotelRoom::getFloor() const {
    return floor;
}

void HotelRoom::setFloor(int floor) {
    HotelRoom::floor = floor;
}

int HotelRoom::getNrBeds() const {
    return nrBeds;
}

void HotelRoom::setNrBeds(int nrBeds) {
    HotelRoom::nrBeds = nrBeds;
}

bool HotelRoom::isChildrenBed() const {
    return childrenBed;
}

void HotelRoom::setChildrenBed(bool childrenBed) {
    HotelRoom::childrenBed = childrenBed;
}

const std::string &HotelRoom::getLocation() const {
    return location;
}

void HotelRoom::setLocation(const std::string &location) {
    HotelRoom::location = location;
}

HotelRoom::HotelRoom(int floor, std::string location, int nrBeds, bool childrenBed, int nrPeople, int size,
                     bool bathroomWithBath, LuxuryLevel* luxuryLevel):floor(floor),location(location),nrBeds(nrBeds),childrenBed(childrenBed) {
    this->nrPeople = nrPeople;
    this->size = size;
    this->bathroomWithBath = bathroomWithBath;
    this->luxuryLevel = luxuryLevel;
}

// De-abstract from parent

unsigned short int HotelRoom::getID() const  {
    return accommodationID;
}

int HotelRoom::getNrPeople() const {
    return nrPeople;
}

void HotelRoom::setNrPeople(int nrPeople) {
    HotelRoom::nrPeople = nrPeople;
}

int HotelRoom::getSize() const {
    return size;
}

void HotelRoom::setSize(int size) {
    HotelRoom::size = size;
}

bool HotelRoom::isBathroomWithBath() const {
    return bathroomWithBath;
}

void HotelRoom::setBathroomWithBath(bool bathroomWithBath) {
    HotelRoom::bathroomWithBath = bathroomWithBath;
}

LuxuryLevel *HotelRoom::getLuxuryLevel() const {
    return luxuryLevel;
}

void  HotelRoom::setLuxuryLevel(LuxuryLevel *luxuryLevel) {
    HotelRoom::luxuryLevel = luxuryLevel;
}
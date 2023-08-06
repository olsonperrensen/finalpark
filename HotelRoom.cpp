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

HotelRoom::HotelRoom(int floor, std::string location, int nrBeds, bool childrenBed, int ID, int nrPeople, int size,
                     bool bathroomWithBath, LuxuryLevel luxuryLevel):Accommodations(ID,nrPeople,size,bathroomWithBath,luxuryLevel),
                     floor(floor),location(location),nrBeds(nrBeds),childrenBed(childrenBed) {

}

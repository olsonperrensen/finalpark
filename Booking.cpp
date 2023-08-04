//
// Created by Admin on 8/4/2023.
//

#include "Booking.h"

Booking::Booking(int ID, Customer customer, std::vector<Accommodations> accomodations, bool activityPass,
                 bool sportsPass, bool bicycleRent, bool swimmingPass):ID(ID), customer(customer),accomodations(accomodations),
                 activityPass(activityPass){

}

int Booking::getID() const {
    return ID;
}

void Booking::setId(int id) {
    ID = id;
}

const Customer &Booking::getCustomer() const {
    return customer;
}

void Booking::setCustomer(const Customer &customer) {
    Booking::customer = customer;
}

const std::vector<Accommodations> &Booking::getAccomodations() const {
    return accomodations;
}

void Booking::setAccomodations(const std::vector<Accommodations> &accomodations) {
    Booking::accomodations = accomodations;
}

bool Booking::isActivityPass() const {
    return activityPass;
}

void Booking::setActivityPass(bool activityPass) {
    Booking::activityPass = activityPass;
}

bool Booking::isSportsPass() const {
    return sportsPass;
}

void Booking::setSportsPass(bool sportsPass) {
    Booking::sportsPass = sportsPass;
}

bool Booking::isBicycleRent() const {
    return bicycleRent;
}

void Booking::setBicycleRent(bool bicycleRent) {
    Booking::bicycleRent = bicycleRent;
}

bool Booking::isSwimmingPass() const {
    return swimmingPass;
}

void Booking::setSwimmingPass(bool swimmingPass) {
    Booking::swimmingPass = swimmingPass;
}

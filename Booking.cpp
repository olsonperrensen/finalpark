//
// Created by Admin on 8/4/2023.
//

#include "Booking.h"
#include "Customer.h"

Booking::Booking(int ID, Customer* customer, std::vector<Accommodations*> accommodations, bool activityPass,
                 bool sportsPass, bool bicycleRent, bool swimmingPass): ID(ID), customer(customer), accommodations(accommodations),
                                                                        activityPass(activityPass){

}

int Booking::getID() const {
    return ID;
}

void Booking::setId(int id) {
    ID = id;
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
Customer *Booking::getCustomer() const {
    return customer;
}

void Booking::setCustomer(Customer *customer) {
    Booking::customer = customer;
}

const std::vector<Accommodations *> &Booking::getAccommodations() const {
    return accommodations;
}

void Booking::setAccommodations(const std::vector<Accommodations *> &accommodations) {
    Booking::accommodations = accommodations;
}
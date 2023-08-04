//
// Created by Admin on 8/4/2023.
//

#include "Parcs.h"

bool Parcs::ParcServices::isSubtropicSwimmingPool() const {
    return subtropicSwimmingPool;
}

void Parcs::ParcServices::setSubtropicSwimmingPool(bool subtropicSwimmingPool) {
    ParcServices::subtropicSwimmingPool = subtropicSwimmingPool;
}

bool Parcs::ParcServices::isSportsInfrastructure() const {
    return sportsInfrastructure;
}

void Parcs::ParcServices::setSportsInfrastructure(bool sportsInfrastructure) {
    ParcServices::sportsInfrastructure = sportsInfrastructure;
}

bool Parcs::ParcServices::isBowlingAlley() const {
    return bowlingAlley;
}

void Parcs::ParcServices::setBowlingAlley(bool bowlingAlley) {
    ParcServices::bowlingAlley = bowlingAlley;
}

bool Parcs::ParcServices::isBicycleRent() const {
    return bicycleRent;
}

void Parcs::ParcServices::setBicycleRent(bool bicycleRent) {
    ParcServices::bicycleRent = bicycleRent;
}

bool Parcs::ParcServices::isChildrensParadise() const {
    return childrensParadise;
}

void Parcs::ParcServices::setChildrensParadise(bool childrensParadise) {
    ParcServices::childrensParadise = childrensParadise;
}

bool Parcs::ParcServices::isWaterBikes() const {
    return waterBikes;
}

void Parcs::ParcServices::setWaterBikes(bool waterBikes) {
    ParcServices::waterBikes = waterBikes;
}

Parcs::ParcServices::ParcServices(bool subtropicSwimmingPool, bool sportsInfrastructure, bool bowlingAlley,
                                  bool bicycleRent, bool childrensParadise, bool waterBikes):
                                  subtropicSwimmingPool(subtropicSwimmingPool),sportsInfrastructure(sportsInfrastructure),
                                  bowlingAlley(bowlingAlley),bicycleRent(bicycleRent),childrensParadise(childrensParadise),
                                  waterBikes(waterBikes){

}

Parcs::Parcs(std::string name, std::string address, ParcServices services,
             std::vector<Accommodations> accommodations): name(name), address(address), services(services),
                                              accommodations(accommodations) {
// have IDs get some value at birth based on previous born and dead instances
    this->parcID = aantalParcs++;
}

int Parcs::getParcId() const {
    return parcID;
}

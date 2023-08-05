//
// Created by Admin on 8/4/2023.
//

#include "LuxuryLevel.h"

bool LuxuryLevel::isBbq() const {
    return BBQ;
}

void LuxuryLevel::setBBQ(bool bbq) {
    BBQ = bbq;
}

bool LuxuryLevel::isSurroundSystem() const {
    return surroundSystem;
}

void LuxuryLevel::setSurroundSystem(bool surroundSystem) {
    LuxuryLevel::surroundSystem = surroundSystem;
}

bool LuxuryLevel::isBreakfastService() const {
    return breakfastService;
}

void LuxuryLevel::setBreakfastService(bool breakfastService) {
    LuxuryLevel::breakfastService = breakfastService;
}

bool LuxuryLevel::isCleaningService() const {
    return cleaningService;
}

void LuxuryLevel::setCleaningService(bool cleaningService) {
    LuxuryLevel::cleaningService = cleaningService;
}

const std::string &LuxuryLevel::getAccommodationKind() const {
    return accommodationKind;
}

void LuxuryLevel::setAccommodationKind(const std::string &accommodationKind) {
    LuxuryLevel::accommodationKind = accommodationKind;
}

LuxuryLevel::LuxuryLevel(bool BBQ, bool surroundSystem, bool breakfastService, bool cleaningService):BBQ(BBQ),surroundSystem(surroundSystem),
breakfastService(breakfastService),cleaningService(cleaningService){

}

void LuxuryLevel::getAllFacilitiesAtOnce() {
    printBooleans(
            LUXURIES[0],LuxuryLevel::isBbq(),
            LUXURIES[1], LuxuryLevel::isSurroundSystem(),
            LUXURIES[2],LuxuryLevel::isBreakfastService(),
            LUXURIES[3],LuxuryLevel::isCleaningService()
    );
}

void LuxuryLevel::setAllFacilitiesAtOnce(bool BBQ, bool surroundSystem, bool breakfastService, bool cleaningService) {
    setBooleans(*this, &LuxuryLevel::setBBQ, BBQ, &LuxuryLevel::setSurroundSystem, surroundSystem,
                &LuxuryLevel::setBreakfastService, breakfastService, &LuxuryLevel::setCleaningService, cleaningService);
}

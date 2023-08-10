//
// Created by Admin on 8/4/2023.
//

#include "LuxuryLevel.h"

bool LuxuryLevel::isBBQ() const {
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
    if(std::find(ACCO_KINDS.begin(),ACCO_KINDS.end(),accommodationKind)!=ACCO_KINDS.end())
       LuxuryLevel::accommodationKind = accommodationKind;
    else
        throw std::invalid_argument("\nPlease choose a valid accommodation kind. Valid options:\n- "
                                    + ACCO_KINDS[0] + "\n- " + ACCO_KINDS[1] +
                                    "\nYour option was:\n- "+accommodationKind+"\nTry again.\n");
}

LuxuryLevel::LuxuryLevel(bool BBQ, bool surroundSystem, bool breakfastService, bool cleaningService,
                         std::string accommodationKind):BBQ(BBQ),
surroundSystem(surroundSystem),
breakfastService(breakfastService),cleaningService(cleaningService){
//    Can't list init accommo kind since no checking happens. Must be in body block
    setAccommodationKind(accommodationKind);
}

void LuxuryLevel::getAllFacilitiesAtOnce() {
    printBooleans(
            LUXURIES[0],LuxuryLevel::isBBQ(),
            LUXURIES[1], LuxuryLevel::isSurroundSystem(),
            LUXURIES[2],LuxuryLevel::isBreakfastService(),
            LUXURIES[3],LuxuryLevel::isCleaningService()
    );
}

void LuxuryLevel::setAllFacilitiesAtOnce(bool BBQ, bool surroundSystem, bool breakfastService, bool cleaningService) {
    setBooleans(*this, &LuxuryLevel::setBBQ, BBQ, &LuxuryLevel::setSurroundSystem, surroundSystem,
                &LuxuryLevel::setBreakfastService, breakfastService, &LuxuryLevel::setCleaningService, cleaningService);
}

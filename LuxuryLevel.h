//
// Created by r0834721 - vak YT6254 on 8/4/2023.
//

#ifndef FINALPARK_LUXURYLEVEL_H
#define FINALPARK_LUXURYLEVEL_H
#include <string>
#include <iostream>
#include "Shared.h"

class LuxuryLevel {
private:
    bool BBQ, surroundSystem,breakfastService,cleaningService;
    std::string accommodationKind;
public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, const LuxuryLevel& obj) {
        os << "LuxuryLevel ( BBQ: " << obj.isBBQ() << ", surroundSystem: " << obj.isSurroundSystem()
           << ", breakfastService: " << obj.isBreakfastService() << ", cleaningService: " << obj.isCleaningService() <<
           ", accommodationKind: " << obj.getAccommodationKind() <<" ) ";
        return os;
    }


//    handy
    bool operator==(const LuxuryLevel& other) const {
        return (this->BBQ == other.BBQ)&&(this->surroundSystem==other.surroundSystem)&&(this->breakfastService==other.breakfastService)
        &&(this->cleaningService==other.cleaningService)&&(this->accommodationKind==other.accommodationKind);
    }
    LuxuryLevel(bool BBQ, bool surroundSystem,bool breakfastService, bool cleaningService,
                std::string accommodationKind);
//    Accommodations needs a default for this class otherwise complains.
    LuxuryLevel()=default;

    bool isBBQ() const;

    void setBBQ(bool bbq);

    bool isSurroundSystem() const;

    void setSurroundSystem(bool surroundSystem);

    bool isBreakfastService() const;

    void setBreakfastService(bool breakfastService);

    bool isCleaningService() const;

    void setCleaningService(bool cleaningService);

    const std::string &getAccommodationKind() const;

    void setAccommodationKind(const std::string &accommodationKind);

    void getAllFacilitiesAtOnce();

//    For after the object being born, allow bulk modification ~ just like constructor does
    void setAllFacilitiesAtOnce(bool BBQ, bool surroundSystem,bool breakfastService, bool cleaningService);
};


#endif //FINALPARK_LUXURYLEVEL_H

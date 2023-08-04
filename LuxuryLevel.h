//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_LUXURYLEVEL_H
#define FINALPARK_LUXURYLEVEL_H
#include <string>
#include <iostream>

class LuxuryLevel {
private:
    bool BBQ, surroundSystem,breakfastService,cleaningService;
    std::string accommodationKind;
public:
    LuxuryLevel(bool BBQ, bool surroundSystem,bool breakfastService, bool cleaningService);
//    Accommodations needs a default for this class otherwise complains.
    LuxuryLevel()=default;

    bool isBbq() const;

    void setBbq(bool bbq);

    bool isSurroundSystem() const;

    void setSurroundSystem(bool surroundSystem);

    bool isBreakfastService() const;

    void setBreakfastService(bool breakfastService);

    bool isCleaningService() const;

    void setCleaningService(bool cleaningService);

    const std::string &getAccommodationKind() const;

    void setAccommodationKind(const std::string &accommodationKind);
};


#endif //FINALPARK_LUXURYLEVEL_H

//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_CABIN_H
#define FINALPARK_CABIN_H


#include "Accommodations.h"

class Cabin: public Accommodations {
    int bedrooms;
public:
//    Avoid Class = int (implicit conversion) and make births curly-brace mandatory Class(int) ie->xplicit
    explicit Cabin(int id, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int bedrooms);
// dunder
    friend std::ostream& operator<<(std::ostream& os, const Cabin& obj) {
        os << "Cabin(ID: " << obj.getID() << ", bedrooms: " << obj.getBedrooms() << ")";
        return os;
    }

    int getBedrooms() const;

    void setBedrooms(int bedrooms);
};


#endif //FINALPARK_CABIN_H

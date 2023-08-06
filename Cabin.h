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
        os << static_cast<const Accommodations&>(obj)  // Print the base class members
           << ", bedrooms: " << obj.bedrooms << " ) ";
        return os;
    }
    bool operator==(const Accommodations& other) const override {
        const Cabin* derivedOther = dynamic_cast<const Cabin*>(&other);
        if (derivedOther == nullptr) {
            // The other object is not of type Derived, so the objects are not equal.
            return false;
        }

        // Compare base class members and derived class members.
        return Accommodations::operator==(other) && (this->bedrooms == derivedOther->bedrooms);
    }
    int getBedrooms() const;

    void setBedrooms(int bedrooms);
};


#endif //FINALPARK_CABIN_H

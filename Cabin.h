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
    explicit Cabin(int nrPeople, int size, bool bathroomWithBath, LuxuryLevel* luxuryLevel,int bedrooms);
    Cabin()=default;
// dunder
    friend std::ostream& operator<<(std::ostream& os, const Cabin& obj) {
        //TODO also print Base attributes (inc ID)
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

//    De-abstract from parent
    unsigned short int getID() const override;

    void setAccommodationId(unsigned short accommodationId) override;

     int getNrPeople() const  override;

     void setNrPeople(int nrPeople) override;

     int getSize() const override;

     void setSize(int size) override;

     bool isBathroomWithBath() const override;

     void setBathroomWithBath(bool bathroomWithBath) override;

     LuxuryLevel *getLuxuryLevel() const override;

    void setLuxuryLevel(LuxuryLevel *luxuryLevel) override;
};


#endif //FINALPARK_CABIN_H

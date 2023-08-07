//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_ACCOMMODATIONS_H
#define FINALPARK_ACCOMMODATIONS_H
#include <iostream>
#include <string>
#include "LuxuryLevel.h"

class Accommodations {
protected:
    static unsigned short int aantalAccommodations;
    unsigned short int accommodationID;
    int nrPeople,size;
    bool bathroomWithBath;
    LuxuryLevel luxuryLevel;
public:
//    Python-like str-dunder method
    friend std::ostream& operator<<(std::ostream& os, const Accommodations& obj) {
        os << "Accommodations ( ID: " << obj.accommodationID << ", nrPeople: " << obj.nrPeople
           << ", size: " << obj.size<< ", bathroomWithBath: " << obj.bathroomWithBath
           << ", luxuryLevel: " << obj.luxuryLevel << " ) ";
        return os;
    }
// No Accommodations should be initialized
    virtual bool operator==(const Accommodations& other) const {
    return (this->accommodationID==other.accommodationID)&&(this->nrPeople==other.nrPeople)&&(this->size==other.size)
    &&(this->bathroomWithBath==other.bathroomWithBath)&&(this->luxuryLevel==other.luxuryLevel);
}
//NO full constructor!! Never initialize since abstract. I prefer copying list initialization values in the derived classes
// than providing a fake constructor here.
    Accommodations()=default;
    Accommodations(int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel);
    virtual unsigned short int getID() const =0;

    virtual int getNrPeople() const =0;

    virtual void setNrPeople(int nrPeople)=0;

    virtual int getSize() const=0;

    virtual void setSize(int size)=0;

    virtual bool isBathroomWithBath() const=0;

    virtual void setBathroomWithBath(bool bathroomWithBath)=0;

    virtual const LuxuryLevel &getLuxuryLevel() const=0;

    virtual void setLuxuryLevel(const LuxuryLevel &luxuryLevel)=0;
};


#endif //FINALPARK_ACCOMMODATIONS_H

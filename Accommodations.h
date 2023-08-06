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
    int ID,nrPeople,size;
    bool bathroomWithBath;
    LuxuryLevel luxuryLevel;
public:
//    Python-like str-dunder method
    friend std::ostream& operator<<(std::ostream& os, const Accommodations& obj) {
        os << "Accommodations ( ID: " << obj.ID << ", nrPeople: " << obj.nrPeople
           << ", size: " << obj.size<< ", bathroomWithBath: " << obj.bathroomWithBath
           << ", luxuryLevel: " << obj.luxuryLevel << " ) ";
        return os;
    }
// No Accommodations should be initialized
    virtual bool operator==(const Accommodations& other) const {
    return (this->ID==other.ID)&&(this->nrPeople==other.nrPeople)&&(this->size==other.size)
    &&(this->bathroomWithBath==other.bathroomWithBath)&&(this->luxuryLevel==other.luxuryLevel);
}
//NO full constructor!! Never initialize since abstract. I prefer copying list initialization values in the derived classes
// than providing a fake constructor here.
    Accommodations()=default;
    virtual int getID() const =0;

    virtual void setId(int id) =0;

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

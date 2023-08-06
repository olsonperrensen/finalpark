//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_ACCOMMODATIONS_H
#define FINALPARK_ACCOMMODATIONS_H
#include <iostream>
#include <string>
#include "LuxuryLevel.h"

class Accommodations {
private:
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

    bool operator==(const Accommodations& other) const {
    return (this->ID==other.ID)&&(this->nrPeople==other.nrPeople)&&(this->size==other.size)
    &&(this->bathroomWithBath==other.bathroomWithBath)&&(this->luxuryLevel==other.luxuryLevel);
}

    Accommodations()=default;
    Accommodations(int ID,int nrPeople,int size,bool bathroomWithBath,LuxuryLevel luxuryLevel);
    int getID() const;

    void setId(int id);

    int getNrPeople() const;

    void setNrPeople(int nrPeople);

    int getSize() const;

    void setSize(int size);

    bool isBathroomWithBath() const;

    void setBathroomWithBath(bool bathroomWithBath);

    const LuxuryLevel &getLuxuryLevel() const;

    void setLuxuryLevel(const LuxuryLevel &luxuryLevel);
};


#endif //FINALPARK_ACCOMMODATIONS_H

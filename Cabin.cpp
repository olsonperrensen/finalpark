//
// Created by Admin on 8/4/2023.
//

#include "Cabin.h"

int Cabin::getBedrooms() const {
    return bedrooms;
}

void Cabin::setBedrooms(int bedrooms) {
    Cabin::bedrooms = bedrooms;
}

Cabin::Cabin(int id, int nrPeople, int size, bool bathroomWithBath, LuxuryLevel luxuryLevel, int bedrooms)
// Since it is a derived class, calling Base is needed, otherwise complaints.
        : Accommodations(id, nrPeople, size, bathroomWithBath, luxuryLevel),bedrooms(bedrooms) {

}

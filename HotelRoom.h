//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_HOTELROOM_H
#define FINALPARK_HOTELROOM_H
#include <string>
#include "Accommodations.h"

class HotelRoom: public Accommodations {
private:
    int floor,nrBeds;
    bool childrenBed;
    std::string location;
public:
//  TODO  dunder
    friend std::ostream& operator<<(std::ostream& os, const HotelRoom& obj) {
        os << static_cast<const Accommodations&>(obj)  // Print the base class members
           << ", floor: " << obj.floor << ", nrBeds: " << obj.nrBeds
           << ", childrenBed: " << obj.childrenBed << ", location: " << obj.location << " ) ";
        return os;
    }
    bool operator==(const Accommodations& other) const override {
        const HotelRoom* derivedOther = dynamic_cast<const HotelRoom*>(&other);
        if (derivedOther == nullptr) {
            // The other object is not of type Derived, so the objects are not equal.
            return false;
        }

        // Compare base class members and derived class members.
        return Accommodations::operator==(other) && (this->floor == derivedOther->floor);
    }
    HotelRoom(int floor, std::string location, int nrBeds, bool childrenBed,
              int ID,int nrPeople,int size,bool bathroomWithBath,LuxuryLevel luxuryLevel);

    int getFloor() const;

    void setFloor(int floor);

    int getNrBeds() const;

    void setNrBeds(int nrBeds);

    bool isChildrenBed() const;

    void setChildrenBed(bool childrenBed);

    const std::string &getLocation() const;

    void setLocation(const std::string &location);
//    De-abstract from parent
//    De-abstract from parent
    int getID() const override;

    void setId(int id)  override;

    int getNrPeople() const  override;

    void setNrPeople(int nrPeople) override;

    int getSize() const override;

    void setSize(int size) override;

    bool isBathroomWithBath() const override;

    void setBathroomWithBath(bool bathroomWithBath) override;

    const LuxuryLevel &getLuxuryLevel() const override;

    void setLuxuryLevel(const LuxuryLevel &luxuryLevel) override;
};


#endif //FINALPARK_HOTELROOM_H

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
    //TODO also print Base attributes (inc ID)
    friend std::ostream& operator<<(std::ostream& os, const HotelRoom& obj) {
        os << static_cast<const Accommodations&>(obj)  // Print the base class members
                << ", childrenBed: " << obj.childrenBed << ", floor: " << obj.floor
            << ", location: " << obj.location << ", nrBeds: " << obj.nrBeds << " ) ";
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
    explicit HotelRoom(int nrPeople,int size,bool bathroomWithBath,LuxuryLevel* luxuryLevel,bool childrenBed,
              int floor, std::string location, int nrBeds);
    HotelRoom()=default;
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


#endif //FINALPARK_HOTELROOM_H

//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_HOTELROOM_H
#define FINALPARK_HOTELROOM_H
#include <string>

class HotelRoom {
private:
    int floor,nrBeds;
    bool childrenBed;
    std::string location;
public:
//  TODO  dunder

    HotelRoom(int floor, std::string location, int nrBeds, bool childrenBed);

    int getFloor() const;

    void setFloor(int floor);

    int getNrBeds() const;

    void setNrBeds(int nrBeds);

    bool isChildrenBed() const;

    void setChildrenBed(bool childrenBed);

    const std::string &getLocation() const;

    void setLocation(const std::string &location);
};


#endif //FINALPARK_HOTELROOM_H

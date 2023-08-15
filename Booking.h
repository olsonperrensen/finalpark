//
// Created by r0834721 - vak YT6254 on 8/4/2023.
//

#ifndef FINALPARK_BOOKING_H
#define FINALPARK_BOOKING_H
#include <vector>
#include "Accommodations.h"
#include "Customer.h"
#include "Sys/Datum.h"
#include "Shared.h"
#include "HotelRoom.h"
#include "Cabin.h"

class Booking {
private:
    int ID;
    Customer* customer;
    std::vector<Accommodations*> accommodations;
//    OWN LOGIC
    Datum* beginDate;
public:
    Datum *getBeginDate() const;

    void setBeginDate(Datum *beginDate);

    Datum *getEndDate() const;

    void setEndDate(Datum *endDate);

private:
    Datum* endDate;
    std::string status;
public:
    const std::string &getStatus() const;

    void setStatus(const std::string &status);

public:

    Customer *getCustomer() const;

    void setCustomer(Customer *customer);

private:
    bool activityPass,sportsPass,bicycleRent,swimmingPass;
public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, const Booking& obj) {
        os << "Booking ( ID: " << obj.getID() << ", customer: " << *obj.getCustomer()
           << ", accommodations: [";

        const std::vector<Accommodations*>& dunderAccommodations = obj.getAccommodations();
        for (size_t i = 0; i < dunderAccommodations.size(); ++i) {
            // Dynamic casting to determine the type of Accommodations
            if (HotelRoom* hotelRoom = dynamic_cast<HotelRoom*>(dunderAccommodations[i])) {
                os << *hotelRoom;
            } else if (Cabin* cabin = dynamic_cast<Cabin*>(dunderAccommodations[i])) {
                os << *cabin;
            }

            // If not the last element, add a comma and a space
            if (i != dunderAccommodations.size() - 1) {
                os << ", ";
            }
        }

        os << "] , activityPass: " << obj.activityPass
           << ", sportsPass: " << obj.sportsPass << ", bicycleRent: " << obj.bicycleRent
           << ", swimmingPass: " << obj.swimmingPass
           << ", Begin date: " << *obj.beginDate // print beginDate
           << ", End date: " << *obj.endDate
           << ", status: " << obj.status << " ) ";

        return os;
    }

    const std::vector<Accommodations *> &getAccommodations() const;

    void setAccommodations(const std::vector<Accommodations *> &accommodations);

//    Important! :
//    BE ABLE TO COMPARE TWO FULL OBJECTS against each other
    bool operator==(const Booking& other) const {
        return (this->ID == other.ID)&&(this->customer==other.customer)&&(this->accommodations==other.accommodations)
        &&(this->activityPass==other.activityPass)&&(this->sportsPass==other.sportsPass)&&(this->bicycleRent==other.bicycleRent)
        &&(this->swimmingPass==other.swimmingPass);
    }

    int getID() const;

    void setId(int id);

    bool isActivityPass() const;

    void setActivityPass(bool activityPass);

    bool isSportsPass() const;

    void setSportsPass(bool sportsPass);

    bool isBicycleRent() const;

    void setBicycleRent(bool bicycleRent);

    bool isSwimmingPass() const;

    void setSwimmingPass(bool swimmingPass);

    Booking(int ID, Customer* customer, std::vector<Accommodations*> accommodations, bool activityPass,
            bool sportsPass, bool bicycleRent, bool swimmingPass,Datum* beginDate, Datum* endDate,std::string status);
    Booking()=default;
};


#endif //FINALPARK_BOOKING_H

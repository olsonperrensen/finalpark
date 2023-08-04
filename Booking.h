//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_BOOKING_H
#define FINALPARK_BOOKING_H
#include <vector>

#include "Customer.h"
#include "Accommodations.h"

class Booking {
private:
    int ID;
    Customer customer;
    std::vector<Accommodations> accomodations;
    bool activityPass,sportsPass,bicycleRent,swimmingPass;
public:
    int getID() const;

    void setId(int id);

    const Customer &getCustomer() const;

    void setCustomer(const Customer &customer);

    const std::vector<Accommodations> &getAccomodations() const;

    void setAccomodations(const std::vector<Accommodations> &accomodations);

    bool isActivityPass() const;

    void setActivityPass(bool activityPass);

    bool isSportsPass() const;

    void setSportsPass(bool sportsPass);

    bool isBicycleRent() const;

    void setBicycleRent(bool bicycleRent);

    bool isSwimmingPass() const;

    void setSwimmingPass(bool swimmingPass);

    Booking(int ID,Customer customer,std::vector<Accommodations> accomodations,bool activityPass,
            bool sportsPass,bool bicycleRent,bool swimmingPass);
};


#endif //FINALPARK_BOOKING_H

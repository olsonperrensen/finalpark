//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_BOOKING_H
#define FINALPARK_BOOKING_H
#include <vector>
#include "Accommodations.h"
#include "Customer.h"

class Booking {
private:
    int ID;
    Customer customer;
    std::vector<Accommodations> accommodations;
    bool activityPass,sportsPass,bicycleRent,swimmingPass;
public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, const Booking& obj) {
        os << "Booking ( ID: " << obj.getID() << ", customer: " << obj.getCustomer()
           << ", accommodations: [";

        const std::vector<Accommodations>& accommodations = obj.getAccommodations();
        for (size_t i = 0; i < accommodations.size(); ++i) {
            os << accommodations[i];

            // If not the last element, add a comma and a space
            if (i != accommodations.size() - 1) {
                os << ", ";
            }
        }

        os << "], activityPass: " << obj.activityPass
           << ", sportsPass: " << obj.sportsPass << ", bicycleRent: " << obj.bicycleRent
           << ", swimmingPass: " << obj.swimmingPass << " ) ";

        return os;
    }

    int getID() const;

    void setId(int id);

    const Customer &getCustomer() const;

    void setCustomer(const Customer &customer);

    const std::vector<Accommodations> &getAccommodations() const;

    void setAccommodations(const std::vector<Accommodations> &accommodations);

    bool isActivityPass() const;

    void setActivityPass(bool activityPass);

    bool isSportsPass() const;

    void setSportsPass(bool sportsPass);

    bool isBicycleRent() const;

    void setBicycleRent(bool bicycleRent);

    bool isSwimmingPass() const;

    void setSwimmingPass(bool swimmingPass);

    Booking(int ID, Customer customer, std::vector<Accommodations> accommodations, bool activityPass,
            bool sportsPass, bool bicycleRent, bool swimmingPass);
};


#endif //FINALPARK_BOOKING_H
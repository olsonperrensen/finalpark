//
// Created by r0834721 - vak YT6254 on 8/4/2023.
//

#ifndef FINALPARK_PARCS_H
#define FINALPARK_PARCS_H
#include <string>
#include <vector>
#include "Accommodations.h"
#include "Shared.h"
#include "Cabin.h"
#include "HotelRoom.h"
#include "Cabin.h"

class Parcs {
public:
    unsigned short int getID() const;
//NESTED class - careful here
    class ParcServices{
    public:
//        nested dunder!
        friend std::ostream& operator<<(std::ostream& os, const ParcServices& obj) {
            os << "ParcServices ( subtropicSwimmingPool: " << obj.isSubtropicSwimmingPool()
               << ", sportsInfrastructure: " << obj.isSportsInfrastructure()
               << ", bowlingAlley: " << obj.isBowlingAlley()
               << ", bicycleRent: " << obj.isBicycleRent()
               << ", childrensParadise: " << obj.isChildrensParadise()
               << ", waterBikes: " << obj.isWaterBikes() << " ) ";
            return os;
        }
        bool operator==(const Parcs::ParcServices& other) const {
            return (this->subtropicSwimmingPool==other.subtropicSwimmingPool)&&
                    (this->sportsInfrastructure==other.sportsInfrastructure)&&
                    (this->bowlingAlley==other.bowlingAlley)&&(this->bicycleRent==other.bicycleRent)
                    &&(this->childrensParadise==other.childrensParadise)&&(this->waterBikes==other.waterBikes);
}
//        Idem as other default bc it is being used by another class otherwise it complains;
        ParcServices()=default;
        ParcServices(bool subtropicSwimmingPool,
                     bool sportsInfrastructure, bool bowlingAlley,bool bicycleRent,bool childrensParadise,
                     bool waterBikes);

        bool isSubtropicSwimmingPool() const;

        void setSubtropicSwimmingPool(bool subtropicSwimmingPool);

        bool isSportsInfrastructure() const;

        void setSportsInfrastructure(bool sportsInfrastructure);

        bool isBowlingAlley() const;

        void setBowlingAlley(bool bowlingAlley);

        bool isBicycleRent() const;

        void setBicycleRent(bool bicycleRent);

        bool isChildrensParadise() const;

        void setChildrensParadise(bool childrensParadise);

        bool isWaterBikes() const;

        void setWaterBikes(bool waterBikes);

//        shortcut fun
        void getAllServicesAtOnce();
        //    For after the object being born, allow bulk modification ~ just like constructor does
        void setAllServicesAtOnce(bool subtropicSwimmingPool,
                                  bool sportsInfrastructure, bool bowlingAlley,bool bicycleRent,bool childrensParadise,bool waterBikes);

    private:
        bool subtropicSwimmingPool,sportsInfrastructure,bowlingAlley,bicycleRent,childrensParadise,waterBikes;
    };
private:
    std::string name,address;
    ParcServices* services{};
public:
    ParcServices *getServices() const;

    void setServices(ParcServices *services);

private:
    std::vector<Accommodations*> accommodations;
public:
     std::vector<Accommodations *> &getAccommodations();

    void setAccommodation(int accommodationID,Accommodations* updatedAccommodation);

public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, Parcs obj) {
        os << "Parcs ( ID: " << obj.getID() << ", name: " << obj.getName() << ", address: " << obj.getAddress() <<
           ", services: " << *obj.getServices() << ", accommodations: [";

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

        os << "] ) ";

        return os;
    }
    bool operator==(const Parcs& other) const {
    return (this->name==other.name)&&(this->accommodations==other.accommodations)&&
    (this->services==other.services)&&(this->address==other.address);
}
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getAddress() const;

    void setAddress(const std::string &address);

private:
//    own identification to pop it as element from VacationParcs
    static unsigned short int aantalParcs;
    unsigned short int parcID{};


public:
//        Make good use of tempaltes again
    void addAccommodation( Accommodations* accommodation);
    void removeAccommodation(unsigned short int id);
    Parcs(std::string name, std::string address, ParcServices* services, std::vector<Accommodations*> accommodations);
    Parcs()=default;
    std::string serialize() const;
    void deserialize(const std::string& data);
};


#endif //FINALPARK_PARCS_H

//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_PARCS_H
#define FINALPARK_PARCS_H
#include <string>
#include <vector>
#include "Accommodations.h"
#include "Shared.h"

class Parcs {
public:
    int getID() const;
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
                     bool sportsInfrastructure, bool bowlingAlley,bool bicycleRent,bool childrensParadise,bool waterBikes);

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
    ParcServices services;
    std::vector<Accommodations> accommodations;
public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, Parcs obj) {
        os << "Parcs ( ID: " << obj.getID() << ", name: " << obj.getName() << ", address: " << obj.getAddress() <<
           ", services: " << obj.getServices() << ", accommodations: [";

        const std::vector<Accommodations>& dunderAccommodations = obj.getAccommodations();
        for (size_t i = 0; i < dunderAccommodations.size(); ++i) {
            os << dunderAccommodations[i];

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

     ParcServices &getServices();

    void setServices(const ParcServices &services);

     std::vector<Accommodations> &getAccommodations() ;

    void setAccommodations(const std::vector<Accommodations> &accommodations);

private:
//    own identification to pop it as element from VacationParcs
    static int aantalParcs;
    int parcID;


public:
//        Make good use of tempaltes again
    void addAccommodation(const Accommodations& accommodation);
    void removeAccommodation(int id);
    Parcs(std::string name, std::string address, ParcServices services, std::vector<Accommodations> accommodations);
};


#endif //FINALPARK_PARCS_H

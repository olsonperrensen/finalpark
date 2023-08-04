//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_PARCS_H
#define FINALPARK_PARCS_H
#include <string>
#include <vector>
#include "Accommodations.h"

class Parcs {
public:
    int getParcId() const;

    class ParcServices{
    public:
//        Idem as other default bc it is being used by another class otherwise it complains;
//        ParcServices()=default;
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

    private:
        bool subtropicSwimmingPool,sportsInfrastructure,bowlingAlley,bicycleRent,childrensParadise,waterBikes;
    };
private:
    std::string name,address;
    ParcServices services;
    std::vector<Accommodations> accommodations;
//    own identification to pop it as element from VacationParcs
    static int aantalParcs;
    int parcID;


public:
    Parcs(std::string name, std::string address, ParcServices services, std::vector<Accommodations> accommodations);
};


#endif //FINALPARK_PARCS_H

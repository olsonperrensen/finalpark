//
// Created by Admin on 8/4/2023.
//

#include "Parcs.h"

// Have no parks at the beginning of the program
unsigned short int Parcs::aantalParcs = 0;

bool Parcs::ParcServices::isSubtropicSwimmingPool() const {
    return subtropicSwimmingPool;
}

void Parcs::ParcServices::setSubtropicSwimmingPool(bool subtropicSwimmingPool) {
    ParcServices::subtropicSwimmingPool = subtropicSwimmingPool;
}

bool Parcs::ParcServices::isSportsInfrastructure() const {
    return sportsInfrastructure;
}

void Parcs::ParcServices::setSportsInfrastructure(bool sportsInfrastructure) {
    ParcServices::sportsInfrastructure = sportsInfrastructure;
}

bool Parcs::ParcServices::isBowlingAlley() const {
    return bowlingAlley;
}

void Parcs::ParcServices::setBowlingAlley(bool bowlingAlley) {
    ParcServices::bowlingAlley = bowlingAlley;
}

bool Parcs::ParcServices::isBicycleRent() const {
    return bicycleRent;
}

void Parcs::ParcServices::setBicycleRent(bool bicycleRent) {
    ParcServices::bicycleRent = bicycleRent;
}

bool Parcs::ParcServices::isChildrensParadise() const {
    return childrensParadise;
}

void Parcs::ParcServices::setChildrensParadise(bool childrensParadise) {
    ParcServices::childrensParadise = childrensParadise;
}

bool Parcs::ParcServices::isWaterBikes() const {
    return waterBikes;
}

void Parcs::ParcServices::setWaterBikes(bool waterBikes) {
    ParcServices::waterBikes = waterBikes;
}

Parcs::ParcServices::ParcServices(bool subtropicSwimmingPool, bool sportsInfrastructure, bool bowlingAlley,
                                  bool bicycleRent, bool childrensParadise, bool waterBikes):
                                  subtropicSwimmingPool(subtropicSwimmingPool),sportsInfrastructure(sportsInfrastructure),
                                  bowlingAlley(bowlingAlley),bicycleRent(bicycleRent),childrensParadise(childrensParadise),
                                  waterBikes(waterBikes){

}

void Parcs::ParcServices::getAllServicesAtOnce() {
    printBooleans(
            SERVICES[0],subtropicSwimmingPool,
            SERVICES[1], sportsInfrastructure,
            SERVICES[2],bowlingAlley ,
            SERVICES[3],bicycleRent ,
            SERVICES[4],childrensParadise ,
            SERVICES[5],waterBikes
    );
}
// avoid individual function calling
void
Parcs::ParcServices::setAllServicesAtOnce(bool subtropicSwimmingPool,
                                          bool sportsInfrastructure, bool bowlingAlley,bool bicycleRent,
                                          bool childrensParadise,bool waterBikes) {
    setBooleans(*this, &ParcServices::setSubtropicSwimmingPool, subtropicSwimmingPool,
                &ParcServices::setSportsInfrastructure, sportsInfrastructure, &ParcServices::setBowlingAlley, bowlingAlley,
                &ParcServices::setBicycleRent,bicycleRent,
                &ParcServices::setChildrensParadise,childrensParadise,&ParcServices::setWaterBikes,waterBikes);
}

void Parcs::addAccommodation(Accommodations *accommodation) {
    addItem(accommodations,accommodation);
}

void Parcs::removeAccommodation(unsigned short int id) {
    removeItem(accommodations,id);
}


Parcs::Parcs(std::string name, std::string address, ParcServices* services,
             std::vector<Accommodations*> accommodations): name(name), address(address), services(services),
                                              accommodations(accommodations) {
// have IDs get some value at birth based on previous born and dead instances
    this->parcID = ++Parcs::aantalParcs;
}

unsigned short int Parcs::getID() const {
    return parcID;
}

const std::string &Parcs::getName() const {
    return name;
}

void Parcs::setName(const std::string &name) {
    Parcs::name = name;
}

const std::string &Parcs::getAddress() const {
    return address;
}

void Parcs::setAddress(const std::string &address) {
    Parcs::address = address;
}

std::vector<Accommodations *> &Parcs::getAccommodations() {
    return accommodations;
}

void Parcs::setAccommodation(int accommodationID,Accommodations* updatedAccommodation) {
    if (Accommodations* accommodation = findItemByID(accommodations, accommodationID)) {
        *accommodation = *updatedAccommodation;
        std::cout << "modifyAccommodation -> Accommodation " << std::to_string(accommodationID) << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "modifyAccommodation -> Error: Accommodation " << std::to_string(accommodationID) << " not found.\n";
    return;
}

Parcs::ParcServices *Parcs::getServices() const {
    return services;
}

void Parcs::setServices(Parcs::ParcServices *services) {
    Parcs::services = services;
    std::cout << "setServices -> services set successfully." << std::endl;
}

std::string Parcs::serialize() const {
    std::string res;
    res = std::to_string(parcID) + "_" + name + "_" + address + "_" +
          std::to_string(this->services->isSubtropicSwimmingPool()) + "_" +
          std::to_string(this->services->isSportsInfrastructure()) + "_" +
          std::to_string(this->services->isBowlingAlley()) + "_" +
          std::to_string(this->services->isBicycleRent()) + "_" +
          std::to_string(this->services->isChildrensParadise()) + "_" +
          std::to_string(this->services->isWaterBikes()) + "_";

    for (auto* e : this->accommodations) {
        // Check for derived class and serialize accordingly
        HotelRoom* hotelRoom = dynamic_cast<HotelRoom*>(e);
        Cabin* cabin = dynamic_cast<Cabin*>(e);
        if (hotelRoom)res += "H_";
        else if (cabin)res += "C_";
            // Serialize common attributes for all accommodations
        res += std::to_string(e->getID()) + "_" +
               std::to_string(e->getNrPeople()) + "_" +
               std::to_string(e->getSize()) + "_" +
               std::to_string(e->isBathroomWithBath()) + "_" +
               std::to_string(e->getLuxuryLevel()->isBBQ()) + "_" +
               std::to_string(e->getLuxuryLevel()->isSurroundSystem()) + "_" +
               std::to_string(e->getLuxuryLevel()->isBreakfastService()) + "_" +
               std::to_string(e->getLuxuryLevel()->isCleaningService()) + "_" +
               e->getLuxuryLevel()->getAccommodationKind() + "_";

        if (hotelRoom) {
            res += std::to_string(hotelRoom->isChildrenBed()) + "_" +
                   std::to_string(hotelRoom->getFloor()) + "_" +
                   hotelRoom->getLocation() + "_" +
                   std::to_string(hotelRoom->getNrBeds()) + "_";
        } else if (cabin) {
            res += std::to_string(cabin->getBedrooms()) + "_";
        } else {
            // Handle unknown derived class or base class
            std::cerr << "serialize -> Unknown derived class for accommodation.\n";
        }
    }

    return res;
}


void Parcs::deserialize(const std::string& data) {
    if (!this->services) {
        this->services = new ParcServices();
    }
//    if (this->accommodations.empty()) {
//        this->accommodations.push_back(new Cabin());  // or the derived class you want to initialize
//    }
    std::stringstream ss(data);
    std::string tmp;

    std::getline(ss, tmp, '_');
//    DEBUG
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    parcID = std::stoi(tmp);
    std::getline(ss, name, '_');
//    std::cout << "deserialize -> reading " << name << " ...\n";
    std::getline(ss, address, '_');
//    std::cout << "deserialize -> reading " << address << " ...\n";
    std::getline(ss, tmp, '_');
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    this->services->setSubtropicSwimmingPool(std::stoi(tmp));
    std::getline(ss, tmp, '_');
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    this->services->setSportsInfrastructure(tmp == "1");
    std::getline(ss, tmp, '_');
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    this->services->setBowlingAlley(tmp == "1");
    std::getline(ss, tmp, '_');
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    this->services->setBicycleRent(tmp == "1");
    std::getline(ss, tmp, '_');
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    this->services->setChildrensParadise(tmp == "1");
    std::getline(ss, tmp, '_');
//    // std::cout << "deserialize -> reading " << tmp << " ...\n";
    this->services->setWaterBikes(tmp == "1");
    for (int i = 0; i < 3; ++i) {
        char type;
        ss >> type;  // Read the type identifier
        ss.ignore();  // Ignore the following delimiter
//        std::cout << type << " as accommo found!\n";
        if (ss.eof()) {
            break;  // Exit if we've reached the end of the stream
        }

        Accommodations* accommodation = nullptr;
        HotelRoom* hotelRoom = nullptr;
        Cabin* cabin = nullptr;
        if (type == 'H') {
            hotelRoom = new HotelRoom();
            accommodation = hotelRoom;
//            std::cout << " HR found!\n";
        } else if (type == 'C') {
            cabin = new Cabin();
            accommodation = cabin;
//            std::cout << " Cab found!\n";
        } else {
            // Handle unexpected type identifier
            std::cerr << "deserialize -> Unexpected type identifier: " << type << " where H or C as only valid options." <<std::endl;
            continue;
        }
            accommodation->setLuxuryLevel(new LuxuryLevel());

        // Deserialize the accommodation data
        std::getline(ss, tmp, '_');
        // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->setAccommodationId(std::stoi(tmp));
        std::getline(ss, tmp, '_');

    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->setNrPeople(std::stoi(tmp));
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->setSize(std::stoi(tmp));
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->setBathroomWithBath((tmp == "1"));
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->getLuxuryLevel()->setBBQ((tmp == "1"));
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->getLuxuryLevel()->setSurroundSystem((tmp == "1"));
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->getLuxuryLevel()->setBreakfastService(tmp == "1");
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->getLuxuryLevel()->setCleaningService(tmp == "1");
        std::getline(ss, tmp, '_');
    // std::cout << "deserialize -> reading " << tmp << " ...\n";
        accommodation->getLuxuryLevel()->setAccommodationKind(tmp);
        
//        manage special derived classes
        if (hotelRoom) {
            // Call HotelRoom-specific methods
//            bool childrenBed,
//              int floor, std::string location, int nrBeds
            std::getline(ss, tmp, '_');
            hotelRoom->setChildrenBed(tmp == "1");
            std::getline(ss, tmp, '_');
            hotelRoom->setFloor(std::stoi(tmp));
            std::getline(ss, tmp, '_');
            hotelRoom->setLocation(tmp);
            std::getline(ss, tmp, '_');
            hotelRoom->setNrBeds(std::stoi(tmp));
        } else if (cabin) {
            // Call Cabin-specific methods
            std::getline(ss, tmp, '_');
            cabin->setBedrooms(std::stoi(tmp));
        }
//        std::cout << "deserialize -> pushing acco" << " ...\n";
        this->accommodations.push_back(accommodation);
    }
    std::getline(ss, tmp, '_');
}


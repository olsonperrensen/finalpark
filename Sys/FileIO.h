//// LEGACY CODE OF A PREVIOUS VERSION THAT BECAME TOO COMPLEX AND PROBLEMATIC TO MAINTAIN...
//// Created by r0834721 - vak YT6254 on 31/7/2023
////
//
//#ifndef FINALPARK_FileIO_H
//#define FINALPARK_FileIO_H
//
//#include <regex>
//#include <vector>
//#include "../Parcs.h"
//#include "../VacationParcs.h"
//#include "Owner.h"
//#include "Datum.h"
//#include "../Customer.h"
//#include "../Booking.h"
//#include "../Accommodations.h"
//#include "../Cabin.h"
//#include "../HotelRoom.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include "../Shared.h"
//#include <sstream>
//#include "OS.h"
//#include <filesystem>
//
//class Datum;
//class User;
//class Owner;
//class Customer;
//class Parcs;
//
////     ADAPT TO WHERE PROGRAM IS BEING EXECUTED
//#define CUSTOMERS_BESTAND R"(C:\Users\Admin\CLionProjects\finalpark\Sys\Data\customers.dat)"
//#define PARCS_BESTAND R"(C:\Users\Admin\CLionProjects\finalpark\Sys\Data\parcs.dat)"
//#define BOOKINGS_BESTAND R"(C:\Users\Admin\CLionProjects\finalpark\Sys\Data\booking.dat)"
//#define VACATIONPARKS_BESTAND R"(Data/.vacationparcs.dat)"
//#define OWNER_BESTAND R"(C:\Users\Admin\CLionProjects\finalpark\Sys\Data\owner.dat)"
//
//class FileIO {
//public:
//    inline static unsigned short int idGenerator=0;
//    std::vector<Customer *> abonnees;
//    Owner *owner;
//    std::vector<Parcs *> parkVector;
//    VacationParcs vp;
//    Customer *huidigUser = nullptr;
//    Parcs *huidigUserPark;
//    std::vector<Parcs *> abonneeSuitableParkLijst;
//    FileIO(VacationParcs vp);
//    static inline std::string strSnijden(std::string &str);
//    static inline bool stringToBool(const std::string& s);
//    inline static std::vector<std::string> mijnStrTok(const std::string& str, char sep);
//    inline static bool isNumGeldig(std::string &inputStr);
//    inline static bool isDouble(std::string &inputStr);
//    inline static bool isWachtGeldig(std::string &wachtwoord);
//    inline bool isGebrGeldig(std::string &gebruikersnaam);
//    inline static bool geldigeMail(std::string &umail);
//    inline static bool isValidKrediet(Customer *abn, Parcs *park);
//    inline static bool isValidLuxuryLevel(Customer *abn, Parcs *park);
//    inline static bool isDatumGeldig(std::string datum);
//    inline static bool isJuisteDatumOrder(Datum* begin, Datum *eind);
//    inline static int menuKeuze(int begin, int eind);
//    inline void hoofdScherm();
//    inline void beheerderMenu();
//    inline void beheerderLoginMenu();
//    inline void employeeLoginMenu();
//    inline void toonBookingSent();
//    inline void employeeZieAbonneeMenu();
//    inline void beheerderZieParkMenu();
//    inline void beheerderZieAccMenu();
//    inline void loginAbnMenu();
//    inline void abonneeMenu();
//    inline void changeCustomer();
//    inline void parkHuurvrijMenu();
//    inline void rateTenantMenu(int leaveID);
//    inline bool getInfoLijstParkMenu();
//    inline bool enterParkInfo();
//    inline void validParkMenu(std::string locatie);
//    inline void searchValidParkMenu();
//    inline bool abnBookingPark(Datum *beginDatum, Datum *eindDatum, int parkId);
//    inline void zieBookingMenu();
//    inline void actionBookingMenu(int bookingID);
//    inline void gehuurdeParkTonen();
//    inline void cancelBookingMenu(int ID);
//    inline bool isValidCityParks(std::string locatie);
//    inline bool isValidEndParks(Datum *eind, Customer *abn, Parcs *park, std::string locatie);
//    inline bool getGeldigeParks(std::string locatie);
//    inline bool deleteInRentPark();
//    inline void inputParkToSys();
//    inline void inputBeheerderToSys();
//    inline void inputAbnParkToSys();
//    inline void inputParkLijstToSys();
//    inline void inputAbonneeToSys();
//    inline void inputBookingToSys();
//    inline void outputBeheerderNaarBestand();
//    inline void outputBookingNaarBestand();
//    inline void outputParkNaarBestand();
//    inline void outputAbonneeNaarBestand();
//    //    FUN OVERLOADING!
//    inline void outputAbonneeNaarBestand(std::vector<Customer *> newabonnee);
//    inline void abonneeRegistreren();
//    inline bool abonneeInloggen(std::string gebruikersnaam, std::string wachtwoord);
//    inline Datum *stringToDatum(std::string &datum);
//};
//#endif //FINALPARK_FileIO_H

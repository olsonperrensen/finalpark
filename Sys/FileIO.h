//
// Created by r0834721 on 31/7/2023
//

#ifndef FINALPARK_FileIO_H
#define FINALPARK_FileIO_H

#include <regex>
#include <vector>
#include "../Parcs.h"
#include "Owner.h"
#include "Datum.h"
#include "../Customer.h"
#include "../Booking.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../Shared.h"
#include <sstream>
#include "OS.h"

class Datum;
class User;
class Beheerder;
class Abonnee;
class Park;

#define CUSTOMERS_BESTAND R"(Data/customers.dat)"
#define PARCS_BESTAND R"(Data/parcs.dat)"
#define BOOKINGS_BESTAND R"(Data/bookings.dat)"
#define VACATIONPARKS_BESTAND R"(Data/.vacationparcs.dat)"
#define OWNER_BESTAND R"(Data/owner.dat)"

class FileIO {
public:
    std::vector<Abonnee *> abonnees;
    Beheerder *beheerder;
    std::vector<Park *> parkVector;
    Abonnee *huidigUser = nullptr;
    Park *huidigUserPark;
    std::vector<Park *> abonneeSuitableParkLijst;
    FileIO();
    static inline std::wstring strSnijden(std::wstring &str);
    inline static std::vector<std::wstring> mijnStrTok(const std::wstring& str, wchar_t sep);
    inline static bool isNumGeldig(std::wstring &inputStr);
    inline static bool isDouble(std::wstring &inputStr);
    inline static bool isWachtGeldig(std::wstring &wachtwoord);
    inline bool isGebrGeldig(std::wstring &gebruikersnaam);
    inline static bool geldigeMail(std::wstring &umail);
    inline static bool isValidKrediet(Abonnee *abn, Park *park);
    inline static bool isValidLuxuryLevel(Abonnee *abn, Park *park);
    inline static bool isDatumGeldig(std::wstring datum);
    inline static bool isJuisteDatumOrder(Datum* begin, Datum *eind);
    inline static int menuKeuze(int begin, int eind);
    inline void hoofdScherm();
    inline void beheerderMenu();
    inline void beheerderLoginMenu();
    inline void toonBookingSent();
    inline void beheerderZieAbonneeMenu();
    inline void beheerderZieParkMenu();
    inline void loginAbnMenu();
    inline void abonneeMenu();
    inline void parkHuurvrijMenu();
    inline void rateTenantMenu(int leaveID);
    inline bool getInfoLijstParkMenu();
    inline bool enterParkInfo();
    inline void validParkMenu(Datum *begin, Datum *eind, std::wstring locatie);
    inline void searchValidParkMenu();
    inline bool abnBookingPark(Datum *beginDatum, Datum *eindDatum, int parkId);
    inline void zieBookingMenu();
    inline void actionBookingMenu(int bookingID);
    inline void gehuurdeParkTonen();
    inline void cancelBookingMenu(int ID);
    inline bool isValidBeginParks(Datum *begin, Abonnee *abn, Park *park, std::wstring locatie);
    inline bool isValidEndParks(Datum *eind, Abonnee *abn, Park *park, std::wstring locatie);
    inline bool getGeldigeBeginParks(Datum *begin, std::wstring locatie);
    inline bool getGeldigeEndParks(Datum *eind, std::wstring locatie);
    inline bool deleteInRentPark();
    inline void inputParkToSys();
    inline void inputBeheerderToSys();
    inline void inputAbnParkToSys();
    inline void inputParkLijstToSys();
    inline void inputAbonneeToSys();
    inline void inputBookingToSys();
    inline void outputBeheerderNaarBestand();
    inline void outputBookingNaarBestand();
    inline void outputParkNaarBestand();
    inline void outputParkLijstNaarBestand();
    inline void outputAbonneeNaarBestand();
    //    FUN OVERLOADING!
    inline void outputAbonneeNaarBestand(std::vector<Abonnee *> newabonnee);
    inline void abonneeRegistreren();
    inline bool abonneeInloggen(std::wstring gebruikersnaam, std::wstring wachtwoord);
    inline Datum *stringToDatum(std::wstring &datum);
};
#endif //FINALPARK_FileIO_H

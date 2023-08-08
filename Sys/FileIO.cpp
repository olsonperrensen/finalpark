//
// Created by r0834721 on 31/7/2023
//

#include "FileIO.h"

FileIO::FileIO() {
    inputBeheerderToSys();
    inputAbonneeToSys();
    inputParkToSys();
    inputAbnParkToSys();
    inputParkLijstToSys();
    inputBookingToSys();
    hoofdScherm();
}

inline std::wstring FileIO::strSnijden(std::wstring &str) {

    std::wstring goeieStr;
    for (wchar_t c: str) {
        if (c == L' ') {
            continue;
        } else {
            goeieStr += c;
        }
    }
    return goeieStr;

}

inline std::vector<std::wstring> FileIO::mijnStrTok(const std::wstring& str, wchar_t sep) {
    std::vector<std::wstring> gegLijst;
    std::wstringstream stroom;
    stroom << str;
    std::wstring cell;
    while (std::getline(stroom, cell, sep)) {
        gegLijst.push_back(cell);
    }
    return gegLijst;
}


inline bool FileIO::isNumGeldig(std::wstring &iStr) {
    for (int i = 0; i < iStr.length(); i++) {
        if (i == 0) {
            if (iStr[i] == L'-') {
                continue;
            }
        }
        if (!std::isdigit(iStr[i])) {
            return false;
        }
    }
    return true;
}

inline bool FileIO::isDouble(std::wstring &iStr) {
    int aantaalPuntjes = 0;
    for (int i = 0; i < iStr.length(); i++) {
        if (i == 0) {
            if (iStr[i] == L'.') {
                aantaalPuntjes++;
                continue;
            }
        }
        if (iStr[i] == L'.') {
            aantaalPuntjes++;
            continue;
        }

        if (!std::isdigit(iStr[i])) {
            std::wcout  << L"Is geen nummer!!! :( Nogeens: " ;
            return false;
        }
        if (aantaalPuntjes > 1) {
            std::wcout  << L"Is geen nummer :( Nogeens" ;
            return false;
        }
    }
    return true;
}

inline bool FileIO::isWachtGeldig(std::wstring &wachtwoord) {
    //nw: min8-10 tekens, één hletter + kleine letter, cijfer + symbol:
    // w: doorgaan
    std::wregex regu(L"^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,10}$");
    wachtwoord = strSnijden(wachtwoord);
    if (std::regex_match(wachtwoord, regu)) {
        return true;
    } else {
        std::wcout

                << L"min8-10 tekens, één hletter + kleine letter, cijfer + symbol, doe nog eens: \n";
        return false;
    }
}

inline bool FileIO::isGebrGeldig(std::wstring &gebruikersnaam) {
    std::wregex regu(L"\\s");
    if (std::regex_match(gebruikersnaam, regu)) {
        std::wcout  << L"Geen spaties toegelaten... Opnieuw \n" ;
        return false;
    } else {
        if (8 > gebruikersnaam.length() || gebruikersnaam.length() > 16) {
            std::wcout  << L"Tussen 8/16 tekens. Opnieuw? \n" ;
            return false;
        } else {
            for (auto abonnee: abonnees) {
                if (abonnee->gebruikersnaam == gebruikersnaam ) {
                    std::wcout  << L"Duplicaat. Probeer het opnieuw met een andere gebruiker: \n" ;
                    return false;
                }
            }
            return true;
        }
    }
}

inline bool FileIO::geldigeMail(std::wstring &umail) {
    std::wregex regul(L"^[a-zA-Z0-9._%+-]{1,10}@[a-zA-Z0-9.-]{1,10}\\.[a-zA-Z]{2,}$");
    umail = strSnijden(umail);
    if (std::regex_match(umail, regul)) {
        return true;
    } else {
        std::wcout  << L"Tot 10 chars voor en na @\n" ;
        return false;
    }
}

inline bool FileIO::isValidKrediet(Abonnee *abn, Park *park) {
    if (abn->krediet <
        (park->consumingPointsPerDag * (park->eindDatum->countDatum() - park->beginDatum->countDatum()))) {
        return false;
    }
    return true;
}

inline bool FileIO::isValidLuxuryLevel(Abonnee *abn, Park *park) {
    if (abn->user_requested_luxury_level < park->minLuxuryLevel) {
        return false;
    }
    return true;
}

inline bool FileIO::isDatumGeldig(std::wstring datum) {
    std::wstring dag = datum.substr(0, 2);
    std::wstring maand = datum.substr(3, 2);
    std::wstring jaar = datum.substr(6, 4);

    for (int i = 0; i < datum.length(); i++) {
        if (i == 2 || i == 5) {
            if (datum[i] != L'/') {
                std::wcout  << L"xx/xx/xxxx Datum format aub. Opnieuw proberen \n" ;
                return false;
            }
        } else if (!std::isdigit(datum[i])) {
            std::wcout  << L"Niet geldig. Opnieuw \n" ;
            return false;
        } else if (std::stoi(maand) > 13 || std::stoi(maand) < 1) {
            std::wcout  << L"Niet geldig. Opnieuw \n" ;
            return false;
        } else if (std::stoi(dag) > DAG_VSCH_MAAND[std::stoi(maand) - 1]) {
            std::wcout  << L"Niet geldig. Opnieuw \n" ;
            return false;
        }
    }
    return true;
}

inline bool FileIO::isJuisteDatumOrder(Datum *begin, Datum *eind) {
    if (eind->countDatum() - begin->countDatum() > 0) {
        return true;
    } else {
        return false;
    }
}


inline int FileIO::menuKeuze(int begin, int eind) {
    int finalKeuze;
    std::wstring tmpKeuze;
    bool flag;

    do {
        std::wcout  << LR"(Uw keuze invoeren:   )" ;
        std::wcin >> tmpKeuze;
        if (!isNumGeldig(tmpKeuze)) {
            std::wcout  << L"\nKeuze is only number! Try again: " ;
            flag = false;
            continue;
        }
        finalKeuze = std::stoi(tmpKeuze);
        if (finalKeuze < begin || finalKeuze > eind) {
            std::wcout  << L"Tussen " << begin << L" en " << eind << L" Opnieuw: " ;
            flag = false;
            continue;
        } else {
            flag = true;
        }
    } while (!flag);

    return finalKeuze;
}
inline void FileIO::hoofdScherm() {
    int keuze;
    std::wcout << LR"---(
                            Discover Vacation Parks: Your Gateway to an unforgettable Escapes and Luxury Stays
      ::::.
        _____A_             Explore Our Parks, Choose Your Ideal Accommodation
       /      /\            Book with Ease, Modify and Create Memories
    __/__/\__/  \___        Empowering Owners, Assisting Employees, :) Customers
---/__|" '' "| /___/\----   Your Dream: Getaway | Our Mission: Manage
   |''|"'||'"| |' '||
   `""`""))""`"`""""        created by r0834721 for a summer retake. All rights reserved)---";
    std::wcout  << std::endl << std::endl << std::endl << std::endl ;
    std::wcout  << L" Use the app as:    1. Abonnee   2. Beheerder  3. Staff 4.I've had enough (quit) \n" ;
    std::wcout  << L"----------------------------------------------------------\n\n" ;

    keuze = menuKeuze(1, 4);
    switch (keuze) {
        case 1:
            loginAbnMenu();
            break;
        case 2:
            beheerderLoginMenu();
            break;
        case 3:
//            TODO
        case 4:
            outputAbonneeNaarBestand();
            outputParkNaarBestand();
            outputParkLijstNaarBestand();
            outputBeheerderNaarBestand();
            outputBookingNaarBestand();
            outputLuxuryLevelParkNaarBestand();
            break;
    }
}
//beheerder menu - basic feature
inline void FileIO::beheerderMenu() {
    int keuze;
    std::wcout << LR"(
*****************************************
              BEHEERDER MENU
            1.Zie Abonnee Lijst
            2.Zie Park Lijst
            3.Park te huur openbaar maken
            4.Back to main menu
*****************************************
)" << std::endl;

    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            beheerderZieAbonneeMenu();
            break;
        case 2:
            beheerderZieParkMenu();
            break;
        case 3:
            parkHuurvrijMenu();
            break;
        case 4:
            hoofdScherm();
            break;
    }


}

inline void FileIO::beheerderZieAbonneeMenu() {
    int index = 1;
    std::wcout  << L"All the abonnee of the systeem: " << L"\n" ;
    std::wcout
            << std::left
            << std::setw(5)
            << L"Index"
            << std::left
            << std::setw(10)
            << L"AbonneeID"
            << std::left
            << std::setw(15)
            << L"Full Name"
            << L"\n" ;
    for (auto abn: abonnees) {
        std::wcout
                << std::left
                << std::setw(5)
                << index
                << std::left
                << std::setw(10)
                << abn->abonneeId
                << std::left
                << std::setw(15)
                << abn->mail
                << L"\n" ;
        index++;
    }
    std::wcout << L"\n";
    std::wcout  << L"\t---1.Zie Abonnee Detail---\n" << L"\t---2.Back to beheerder menu---\n" ;
    int keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::wcout
                    << std::left
                    << std::setw(10)
                    << L"Index"
                    << std::left
                    << std::setw(15)
                    << L"AbonneeID"
                    << std::left
                    << std::setw(15)
                    << L"Full Name"
                    << std::left
                    << std::setw(15)
                    << L"Usersnaam"
                    << std::left
                    << std::setw(8)
                    << L"Krediet"
                    << std::left
                    << std::setw(15)
                    << L"Locatie"
                    << std::left
                    << std::setw(10)
                    << L"Luxury level Score"
                    << L"\n" ;
            for (int i = 0; i < abonnees.size(); i++) {
                std::wcout
                        << std::left
                        << std::setw(10)
                        << i + 1
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->abonneeId
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->mail
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->gebruikersnaam
                        << std::left
                        << std::setw(8)
                        << abonnees[i]->krediet
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->locatie
                        << std::left
                        << std::setw(10)
                        << abonnees[i]->getLuxuryLevel()
                        << L"\n" ;
            }
            std::wcout << L"\n";
            std::wcout  << abonnees.size() + 1 << L".Back to beheerder menu\n" ;
            menuKeuze(abonnees.size() + 1, abonnees.size() + 1);
            beheerderMenu();

        case 2:
            beheerderMenu();
            break;
    }
}

inline void FileIO::beheerderZieParkMenu() {
    int index = 1;
    std::wcout  << L"All park of the systeem: " << L"\n" ;
    std::wcout
            << std::left
            << std::setw(10)
            << L"Index"
            << std::left
            << std::setw(8)
            << L"ParkID"
            << std::left
            << std::setw(15)
            << L"BeheerderID"
            << std::left
            << std::setw(15)
            << L"Locatie"
            << std::left
            << std::setw(35)
            << L"Description"
            << L"\n" ;
    for (auto i: parkVector) {
        std::wcout
                << std::left
                << std::setw(10)
                << index
                << std::left
                << std::setw(8)
                << i->parkID
                << std::left
                << std::setw(15)
                << i->beheerder->abonneeId
                << std::left
                << std::setw(15)
                << i->locatie
                << std::left
                << std::setw(35)
                << i->parkDescription
                << L"\n" ;
        index++;
    }
    std::wcout << L"\n";
    std::wcout  << L"\t---1.Zie Park Detail---\n" << L"\t---2.Back to beheerder menu---\n" ;
    int keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::wcout
                    << std::left
                    << std::setw(10)
                    << L"Index"
                    << std::left
                    << std::setw(10)
                    << L"ParkID"
                    << std::left
                    << std::setw(10)
                    << L"BeheerderID"
                    << std::left
                    << std::setw(20)
                    << L"Begin Datum"
                    << std::left
                    << std::setw(20)
                    << L"End Datum"
                    << std::left
                    << std::setw(25)
                    << L"KredietPerDag"
                    << std::left
                    << std::setw(15)
                    << L"minScore"
                    << std::left
                    << std::setw(20)
                    << L"Locatie"
                    << std::left
                    << std::setw(35)
                    << L"Description"
                    << L"\n" ;
            for (int j = 0; j < parkVector.size(); j++) {
                std::wcout
                        << std::left
                        << std::setw(10)
                        << j + 1
                        << std::left
                        << std::setw(10)
                        << parkVector[j]->parkID
                        << std::left
                        << std::setw(10)
                        << parkVector[j]->beheerder->abonneeId
                        << std::left
                        << std::setw(20)
                        << parkVector[j]->beginDatum->datumNaarString()
                        << std::left
                        << std::setw(20)
                        << parkVector[j]->eindDatum->datumNaarString()
                        << std::left
                        << std::setw(25)
                        << parkVector[j]->consumingPointsPerDag
                        << std::left
                        << std::setw(15)
                        << parkVector[j]->minLuxuryLevel
                        << std::left
                        << std::setw(20)
                        << parkVector[j]->locatie
                        << std::left
                        << std::setw(35)
                        << parkVector[j]->parkDescription
                        << L"\n" ;
            }
            std::wcout << L"\n";
            std::wcout  << parkVector.size() + 1 << L".Back to beheerder menu\n" ;
            menuKeuze(parkVector.size() + 1, parkVector.size() + 1);
            beheerderMenu();
            break;
        case 2:
            beheerderMenu();
            break;
    }


}

inline void FileIO::loginAbnMenu() {
    std::wstring gebruikersnaam, wachtwoord;
    std::wcout << LR"(
|||||||||||||||||||||||||||||||||||||||||
            | ABONNEE PORTAL |
        1. Register as a new abonnee
        2. Login as abonnee
        3. Back to main menu
|||||||||||||||||||||||||||||||||||||||||
)" << std::endl;

    switch (menuKeuze(1, 2)) {
        case 1:
            abonneeRegistreren();
            break;
        case 2:
            std::wcin.ignore();
            std::wcout  << LR"(Uw gebruikersnaam invoeren:   )" ;
            std::getline(std::wcin, gebruikersnaam);
            std::wcout  << LR"(Uw wachtwoord invoeren:   )" ;
            std::getline(std::wcin, wachtwoord);
            if (abonneeInloggen(gebruikersnaam, wachtwoord)) {
                abonneeMenu();
                break;
            }
        case 3:
            hoofdScherm();
            break;
    }


}

inline void FileIO::beheerderLoginMenu() {
    std::wstring gebruikersnaam, wachtwoord;

    std::wcout << LR"(
=======================================
              BEHEERDER MENU
     1.Login As Beheerder
     2.Back to main menu
=======================================
)" << std::endl;
    switch (menuKeuze(1, 2)) {
        case 1:
            std::wcin.ignore();
            std::wcout  << LR"(Uw gebruikersnaam invoeren:   )" ;
            std::getline(std::wcin, gebruikersnaam);
            std::wcout  << LR"(Uw wachtwoord invoeren:   )" ;
            std::getline(std::wcin, wachtwoord);
            if (beheerder->gebruikersnaam == gebruikersnaam && beheerder->wachtwoord == wachtwoord) {
                std::wcout  << L"Succesvol ingelogd... aan het laden... \n\n\n\n" ;
                beheerderMenu();
                break;
            } else {
                std::wcout  << L"\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
            }
        case 2:
            hoofdScherm();
            break;


    }
}


inline void FileIO::abonneeMenu() {
//    TODO Customers can edit their gegevens
    int keuze;
    std::wcout << LR"(
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
          @@@ABONNEE MENU@@@
  1.Zie Account's Information
  2.Zie Available Parks
  3.Handle Bookings
  4.Toon gehuurde menu
  5.Toon Booking Sent
  6.Logout
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
)" << std::endl;
    keuze = menuKeuze(1, 8);
    switch (keuze) {
        case 1:
            huidigUser->toonAccountInfo();
            std::wcout  << L"1. Back to menu...\n" ;
            menuKeuze(1, 1);
            abonneeMenu();
            break;
        case 2:
            searchValidParkMenu();
            break;
        case 3:
            zieBookingMenu();
            break;
        case 4:
            gehuurdeParkTonen();
            break;
        case 5:
            toonBookingSent();
            break;
        case 6:
            huidigUser = nullptr;
            hoofdScherm();
            break;
    }


}

inline void FileIO::parkHuurvrijMenu() {
    std::wcout  << L"\t---UP park FOR RENT MENU ---\n" ;
    if (huidigUser->parkBeheerder != nullptr) {
        if (huidigUser->parkBeheerder->isToegevoegd) {
            std::wcout  << L"You are having a park for rent: \n" ;
            huidigUser->parkBeheerder->zieParkInfo();
            if (huidigUser->parkBeheerder->lijstParkBooking.empty()) {
                std::wcout  << L"\n\n---\t1. Omit the park of renting site ---\n"
                            << L"\t---2. Back to abonnee menu ---\n" ;
                switch (menuKeuze(1, 2)) {
                    case 1:
                        deleteInRentPark();
                        std::wcout  << L"\tCome back to UP park FOR RENT MENU \n" ;
                        parkHuurvrijMenu();
                        break;
                    case 2:
                        abonneeMenu();
                        break;
                }
            } else {
                std::wcout  << L"\tCome back to abonnee menu \n" ;
                abonneeMenu();
            }
        } else {
            std::wcout  << L"You are having a park but not allowing rental yet: \n"
                        << L"1. Add the park for rent\n"
                        << L"2. Back to abonnee menu\n" ;
            switch (menuKeuze(1, 2)) {
                case 1:
                    getInfoLijstParkMenu();
                    std::wcout  << L"\nPark toegevoegd\n\n" ;
                    parkHuurvrijMenu();
                    break;
                case 2:
                    abonneeMenu();
                    break;
            }
        }
    } else {
        std::wcout  << L"Je hebt geen park. Eenje toevoegen: \n" ;
        enterParkInfo();
        parkHuurvrijMenu();
    }
}

inline bool FileIO::getInfoLijstParkMenu() {
    std::wstring beginDatum, eindDatum, minScores, minKrediets;
    std::wcin.ignore();

    std::wcout  << L"\tPlease enter of your rental info\n" ;
    do {
        do {
            std::wcout  << L"Enter the first renting datum " ;
            std::getline(std::wcin, beginDatum);
        } while (!isDatumGeldig(beginDatum));
        do {
            std::wcout  << L"Enter the eind renting datum " ;
            std::getline(std::wcin, eindDatum);
        } while (!isDatumGeldig(eindDatum));
    } while (!isJuisteDatumOrder(stringToDatum(beginDatum), stringToDatum(eindDatum)));

    do {
        std::wcout  << L"Enter the required krediets per dag " ;
        std::getline(std::wcin, minKrediets);
    } while (!isDouble(minKrediets));

    do {
        std::wcout  << L"Enter the required minimum scores of renant " ;
        std::getline(std::wcin, minScores);
    } while (!isDouble(minScores));

    Datum *begin = stringToDatum(beginDatum);
    Datum *eind = stringToDatum(eindDatum);
    huidigUser->parkToevoegen(begin, eind, std::stod(minKrediets), std::stod(minScores), STATUS[0]);
    return true;
}

inline bool FileIO::enterParkInfo() {
    std::wstring parkId, locatie, description;
    int keuze;
    std::wcout  << L"\tPlease enter your park's information\n" ;
    std::wcout  << L"\tKies the supported app locatie: " ;
    std::wcout  << L"\t1. BOOM \t2.WILLEBROEK \t3.RUMST\n" ;
    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            locatie = PLEKKEN[0];
            break;
        case 2:
            locatie = PLEKKEN[1];
            break;
        case 3:
            locatie = PLEKKEN[2];
            break;
    }
    std::wcin.ignore();
    std::wcout  << L"\tEnter the description for your park: \n" ;
    std::getline(std::wcin, description);
    auto *createdPark = new Park(L"PRK" + std::to_wstring(parkVector.size() + 1), locatie, description);
    parkVector.push_back(createdPark);
    huidigUser->createPark(createdPark);
    return true;
}
//TODO convert naar BookingTonen
inline void FileIO::gehuurdeParkTonen() {
    //Check if huidig abonnee ocupying any park
    if (huidigUser->tenantLijst.empty()) {
        std::wcout  << L"\n\t\tThere are no park you are renting\n\n\t\tBack To Abonnee Menu\n" ;
        abonneeMenu();
    }
    std::wcout  << L"\nThe lijst of park you occupied:\n" ;
    huidigUser->zieTenant();
    std::wcout << L"\n---" << huidigUser->tenantLijst.size() + 1 << L".Back to menu\n";
    int keuze = menuKeuze(1, huidigUser->tenantLijst.size() + 1);
    if (keuze == huidigUser->tenantLijst.size() + 1) {
        abonneeMenu();
    }
    auto tenantPark = huidigUser->tenantLijst[keuze - 1]->occupyPark;
    tenantPark->zieParkInfo();
    std::wcout  << L"\n"
                << L"\t\t1.Checkout\n"
                << L"\t\t2.Back to menu\n" ;
    int newKeuze = menuKeuze(1, 2);
    switch (newKeuze) {
        case 1:
            huidigUser->checkout(keuze - 1);
            std::wcout  << L"\n\t\tLeft Park\n" ;
            rateTenantMenu(keuze - 1);
            break;
        case 2:
            abonneeMenu();
            break;
    }

}

inline void FileIO::rateTenantMenu(int leaveID) {
    std::wcout  << L"\n\t\t1.Press 1 to rate the park: " ;

    int keuze = menuKeuze(1, 1);
    if (keuze == 1) {
        auto leaveAbonnee = huidigUser->tenantLijst[leaveID];
        std::wstring luxury_level;

        while (true) {
            std::wcout  << L"\n\t\tPlease leave a luxury_level: " ;
            std::wcin >> luxury_level;
            if (!isNumGeldig(luxury_level)) {
                continue;
            }
            if (std::stoi(luxury_level) < -10 || std::stoi(luxury_level) > 10) {
                std::wcout  << L"The luxury level scores can only be van -10 to 10: " ;
                continue;
            }else{
                break;
            }
        }
        std::wcout  << L"\nPress 2 to back to the abonnee Menu: " ;
        if (menuKeuze(2, 2) == 2) {
            abonneeMenu();
        }

    }
}

inline void FileIO::toonBookingSent() {
    std::wcout  << L"\nEnter the index of booking that you want to cancel:\n" ;
    std::wcout  << L"Lijst of the booking you have sent: \n" ;
    huidigUser->toonBookingSent();
    std::wcout  << huidigUser->bookingLijst.size() + 1 << L".Back to Abonnee Menu\n" ;
    int keuze = menuKeuze(1, huidigUser->bookingLijst.size() + 1);
    if (keuze == huidigUser->bookingLijst.size() + 1) {
        abonneeMenu();
    } else {
        cancelBookingMenu(keuze);
    }

}

inline void FileIO::cancelBookingMenu(int ID) {
    std::wcout  << L"\nPress 1 to cancel the booking\n" ;
    std::wcout  << L"\nPress 2 to back to toon booking sent menu\n" ;
    int keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            for (auto i: parkVector) {
                for (int j = 0; j < i->lijstParkBooking.size(); j++) {
                    if (i->lijstParkBooking[j]->parkID == huidigUser->bookingLijst[ID - 1]->parkID) {
                        i->lijstParkBooking.erase(i->lijstParkBooking.begin() + j);
                    }
                }
            }
            huidigUser->cancelBooking(ID);
            std::wcout  << L"\nBooking canceled\nBack to menu:\n" ;
            toonBookingSent();
            break;

        case 2:
            toonBookingSent();
            break;
    }
}

inline void FileIO::searchValidParkMenu() {
    std::wstring beginDatum;
    std::wstring eindDatum;
    std::wstring locatie;
    Datum *eind, *begin;
    int keuze;
    std::wcout  << L"\tSearch for suitable parks: \n" ;
    std::wcout  << L"\t---1. Search by your begin dag ---\n" << L"\t---2. Search by your eind dag ---\n" ;
    switch (menuKeuze(1, 2)) {
        case 1:
            std::wcin.ignore();
            do {
                std::wcout  << L"Enter when you want to rent (dd/mm/yyyy): " ;
                std::getline(std::wcin, beginDatum);
            } while (!isDatumGeldig(beginDatum));
            std::wcout << beginDatum << L"\n";
            break;

        case 2:
            std::wcin.ignore();
            do {
                std::wcout  << L"Enter when you want to eind renting (dd/mm/yyyy): " ;
                std::getline(std::wcin, eindDatum);
            } while (!isDatumGeldig(eindDatum));
            break;
    }

    std::wcout  << L"\tKies the city you want to stay: \n\n" ;
    std::wcout  << L"\t1. BOOM \t2.WILLEBROEK \t3.RUMST\n" ;
    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            locatie = PLEKKEN[0];
            break;
        case 2:
            locatie = PLEKKEN[1];
            break;
        case 3:
            locatie = PLEKKEN[2];
            break;
    }

    if (eindDatum.length() == 0) {
        eind = nullptr;
    } else {
        eind = stringToDatum(eindDatum);
    }

    if (beginDatum.length() == 0) {
        begin = nullptr;
    } else {
        begin = stringToDatum(beginDatum);
    }

    validParkMenu(begin, eind, locatie);

}

inline void FileIO::validParkMenu(Datum *begin, Datum *eind, std::wstring locatie) {
    abonneeSuitableParkLijst.clear();
    Booking *booking;
    int keuze;
    if (eind == nullptr) {
        getGeldigeBeginParks(begin, locatie);
    } else {
        getGeldigeEndParks(eind, locatie);
    }
    std::wcout  << abonneeSuitableParkLijst.size() + 1 << L". Back to abonnee menu\n" ;
    keuze = menuKeuze(1, abonneeSuitableParkLijst.size() + 1);
    if (keuze == abonneeSuitableParkLijst.size() + 1) {

        abonneeMenu();
    } else {
        abonneeSuitableParkLijst[keuze - 1]->zieParkInfo();
        std::wcout  << L"\n\n--> 1.\tBooking to rent this park\n\n"
                    << L"--> 3.\tBack to park lijst\n" ;
        switch (menuKeuze(1, 3)) {
            case 1: {
                if (eind == nullptr) {
                    booking = new Booking(begin, abonneeSuitableParkLijst[keuze - 1]->eindDatum, huidigUser,
                                          abonneeSuitableParkLijst[keuze - 1]->parkID,
                                          AV_STATUS[0]);
                } else {
                    booking = new Booking(abonneeSuitableParkLijst[keuze - 1]->beginDatum, eind, huidigUser,
                                          abonneeSuitableParkLijst[keuze - 1]->parkID,
                                          AV_STATUS[0]);
                }
                abonneeSuitableParkLijst[keuze - 1]->bookingToevoegenToParkBookingLijst(booking);
                abonneeMenu();
                break; //function send bookings
            }
            case 3:
                validParkMenu(begin, eind, locatie);
                break;
        }
    }
}

inline void FileIO::actionBookingMenu(int bookingID) {
    std::wcout  << L"\n\n1.Accept Booking\n2.Decline Booking\n" ;
    switch (menuKeuze(1, 3)) {
        case 1:
            if (!huidigUser->acceptBooking(bookingID)) {
                std::wcout  << L"\n" << huidigUser->parkBeheerder->lijstParkBooking.size() + 1
                            << L".Back to booking menu\n" ;
                menuKeuze(huidigUser->parkBeheerder->lijstParkBooking.size() + 1,
                          huidigUser->parkBeheerder->lijstParkBooking.size() + 1);
                zieBookingMenu();
            } else {
                std::wcout  << L"\nBooking accepted\n" ;
                abonneeMenu();
                break;
            }
        case 2:
            //Return beheerder to booking menu once there is no valid accept yet
            if (!huidigUser->declineBooking(bookingID)) {
                std::wcout  << L"You can not decline a booking that has been accpeted and declinded" ;
                std::wcout  << L"\n" << huidigUser->parkBeheerder->lijstParkBooking.size() + 1
                            << L".Back to booking menu\n" ;
                menuKeuze(huidigUser->parkBeheerder->lijstParkBooking.size() + 1,
                          huidigUser->parkBeheerder->lijstParkBooking.size() + 1);
                zieBookingMenu();
            } else {
                std::wcout  << L"\nBooking Declined\n" ;
                abonneeMenu();
                break;
            }

    }
}

inline void FileIO::zieBookingMenu() {
    int keuze;
    std::wcout  << L"\n\n\tYour booking vandaag:\n\n" ;
    if (huidigUser->parkBeheerder == nullptr) {
        std::wcout  << L"You do not have a park. So you do not have any booking! \n" ;
        abonneeMenu();
    } else {
        int numberBooking = huidigUser->toonAanvragen();
        std::wcout  << L"\n\tKies your option:\n\n" ;
        std::wcout  << L"\n\n--> 1.\tPoint the Booking:\n\n"
                    << L"--> 2.\tBack to Menu\n" ;
        keuze = menuKeuze(1, 3);
        switch (keuze) {
            case 1: {
                std::wcout  << L"Enter the booking you want to proceed: \n" ;
                int newKeuze = menuKeuze(1, numberBooking);
                actionBookingMenu(newKeuze - 1);
                break;
            }
            case 2:
                abonneeMenu();
                break;
        }
    }

}

inline bool FileIO::abnBookingPark(Datum *beginDatum, Datum *eindDatum, int parkId) {
    if (parkId > abonneeSuitableParkLijst.size()) {
        return false;
    }

}

inline bool FileIO::isValidBeginParks(Datum *begin, Abonnee *abn, Park *park, std::wstring locatie) {

    int count = 0;
    if (!park->isToegevoegd) {
        return false;
    }

    if (park->parkStatus == STATUS[1]) {
        return false;
    }

    if (park == abn->parkBeheerder) {
        return false;
    }

    if (!isValidLuxuryLevel(abn, park)) {
        return false;
    }
    if (!isValidKrediet(abn, park)) {
        return false;
    }

    if (locatie != park->locatie) {
        return false;
    }

    if (park->beginDatum->datumNaarString() == begin->datumNaarString()) {
        return true;
    }
    return false;

}

inline bool FileIO::isValidEndParks(Datum *eind, Abonnee *abn, Park *park, std::wstring locatie) {
    if (!park->isToegevoegd) {
        return false;
    }

    if (park->parkStatus == STATUS[1]) {
        return false;
    }

    if (park == abn->parkBeheerder) {
        return false;
    }

    if (!isValidLuxuryLevel(abn, park)) {
        return false;
    }
    if (!isValidKrediet(abn, park)) {
        return false;
    }

    if (locatie != park->locatie) {
        return false;
    }


    if (park->eindDatum == eind) {
        return true;
    }

    return false;
}

inline bool FileIO::getGeldigeBeginParks(Datum *begin, std::wstring locatie) {
    abonneeSuitableParkLijst.clear();
    for (auto &park: parkVector) {
        if (isValidBeginParks(begin, huidigUser, park, locatie)) {
            abonneeSuitableParkLijst.push_back(park);
        }
    }

    if (abonneeSuitableParkLijst.empty()) {
        std::wcout  << L"\nAsjemenou! Wij konden geen park vinden die voldoet aan uw criteria :(\n" ;
        return false;
    }

    std::wcout  << L"\nThe suitable park lijst:\n\n" ;
    for (int i = 0; i < abonneeSuitableParkLijst.size(); i++) {
        std::wcout  << L"--> " << i + 1 << L". " ;
        std::wcout  << L"Park Id: " << abonneeSuitableParkLijst[i]->parkID << L"\tLocatie: "
                    << abonneeSuitableParkLijst[i]->locatie << L"\tLuxury level: "
                    << abonneeSuitableParkLijst[i]->getLuxuryLevel() << L"\n" ;
    }
    std::wcout << L"\n\n";

    return true;
}

inline bool FileIO::getGeldigeEndParks(Datum *eind, std::wstring locatie) {
    abonneeSuitableParkLijst.clear();
    for (auto &park: parkVector) {
        if (isValidEndParks(eind, huidigUser, park, locatie)) {

            abonneeSuitableParkLijst.push_back(park);
        }
    }

    if (abonneeSuitableParkLijst.empty()) {
        std::wcout  << L"\nAsjemenou! Wij konden geen park vinden die voldoet aan uw criteria :(\n" ;
        return false;
    }

    std::wcout  << L"\nThe suitable park lijst:\n\n" ;
    for (int i = 0; i < abonneeSuitableParkLijst.size(); i++) {
        std::wcout << L"--> " << i + 1 << L". ";
        std::wcout  << L"Park Id: " << abonneeSuitableParkLijst[i]->parkID << L"\tLocatie: "
                    << abonneeSuitableParkLijst[i]->locatie << L"\tLuxury level: "
                    << abonneeSuitableParkLijst[i]->getLuxuryLevel() << L"\n" ;
    }
    std::wcout << L"\n\n";

    return true;
}

inline bool FileIO::deleteInRentPark() {
    if (huidigUser->deletePark()) {
        std::wcout  << L"\nSuccessfully omit the park\n" ;
        return true;
    } else {
        std::wcout  << L"The park have bookings hanging. Resolved all before omitting! \n" ;
        return false;
    }
}

inline void FileIO::inputParkToSys() {
    parkVector.clear();
    std::wstring gegLijn;
    std::wifstream bestandLezen{VACATIONPARKS_BESTAND};
    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << VACATIONPARKS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";

    }
    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        auto *park = new Park(gegLijst[0], gegLijst[2], gegLijst[3]);
        parkVector.push_back(park);
    }
    bestandLezen.close();
}

inline void FileIO::inputBeheerderToSys() {

    std::wifstream bestandLezen{OWNER_BESTAND};
    std::vector<std::wstring> gegLijst{};
    std::wstring gegLijn,gebruikersnaam,wachtw;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << OWNER_BESTAND << L" niet openen. Probeer het eens opnnieuw.\n";
        return;  //  Als 't bestand iets problematisch heeft
    } else std::cout << L"\nAan het laden...\n";

    if (std::getline(bestandLezen, gegLijn)) {
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
    } else {
        std::wcerr << L"Kon uw beheerdergegevens niet lezen.\n";
        return; // Als je een foutieve lijn krijgt
    }

    if (static_cast<int>(gegLijst.size()) < 2) {
        std::wcerr << L"Data is in an incorrect format\n";
        return; // Return immediately if the necessary data is not present
    }
    gebruikersnaam = gegLijst[0];
    wachtw = gegLijst[1];

//    CANNOT DO Beheerder* bc declared at top Classe
    beheerder = new Beheerder(gebruikersnaam, wachtw);
}


inline void FileIO::inputParkLijstToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{PARCS_BESTAND};
    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << PARCS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }
    Abonnee *beheerder;
    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        Datum *beginDatum = stringToDatum(gegLijst[2]);
        Datum *eindDatum = stringToDatum(gegLijst[3]);
        double krediets = std::stod(gegLijst[4]);
        double scores = std::stod(gegLijst[5]);
        std::wstring status = gegLijst[6];
        std::wstring beheerderId = gegLijst[1];
        for (Abonnee *abn: abonnees) {
            if (beheerderId == abn->abonneeId) {
                beheerder = abn;
            }
        }
        beheerder->parkToevoegen(beginDatum, eindDatum, krediets, scores, status);
    }
    bestandLezen.close();
}

inline void FileIO::inputAbnParkToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{VACATIONPARKS_BESTAND};
    Abonnee *targetAbn;
    Park *abnPark;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << VACATIONPARKS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (Park *park: parkVector) {
            if (gegLijst[0] == park->parkID) {
                abnPark = park;
            }
        }
        for (Abonnee *abn: abonnees) {
            if (gegLijst[1] == abn->abonneeId) {
                targetAbn = abn;
            }
        }
        targetAbn->createPark(abnPark);
    }
    bestandLezen.close();

}

inline void FileIO::inputAbonneeToSys() {
    abonnees.clear();
    std::wstring gegLijn;
    std::wifstream bestandLezen{CUSTOMERS_BESTAND};

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << CUSTOMERS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        auto *abonnee = new Abonnee(gegLijst[2], gegLijst[3], gegLijst[0], gegLijst[1],
                                    std::stod(gegLijst[5]), std::stod(gegLijst[6]), gegLijst[4]);
        abonnees.push_back(abonnee);
    }
    bestandLezen.close();
}

inline void FileIO::inputBookingToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{BOOKINGS_BESTAND};
    Abonnee *targetAbn;
    Park *targetPark;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << BOOKINGS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (Park *park: parkVector) {
            if (gegLijst[1] == park->parkID) {
                targetPark = park;
            }
        }
        for (Abonnee *abn: abonnees) {
            if (gegLijst[0] == abn->abonneeId) {
                targetAbn = abn;
            }
        }
        Datum *beginDatum = stringToDatum(gegLijst[2]);
        Datum *eindDatum = stringToDatum(gegLijst[3]);
        std::wstring status = gegLijst[4];
        Booking *av = new Booking(beginDatum, eindDatum, targetAbn, targetPark->parkID, status);
        targetPark->bookingToevoegenToParkBookingLijst(av);
        targetAbn->bookingLijst.push_back(av);
    }
    bestandLezen.close();
}
inline void FileIO::outputBeheerderNaarBestand() {
    std::wofstream bestandSchrijven{OWNER_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << OWNER_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    bestandSchrijven << beheerder->gebruikersnaam << SCHEIDER
                     << beheerder->wachtwoord << L"\n";
}

inline void FileIO::outputBookingNaarBestand() {
    std::wofstream bestandSchrijven{BOOKINGS_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << BOOKINGS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    for (auto &park: parkVector) {
        for (auto &abnBooking: park->lijstParkBooking) {
            bestandSchrijven << abnBooking->aangevraagdByAbonnee->abonneeId << SCHEIDER
                             << park->parkID << SCHEIDER
                             << abnBooking->beginDatum->datumNaarString() << SCHEIDER
                             << abnBooking->eindDatum->datumNaarString() << SCHEIDER
                             << abnBooking->bookingStatus << L"\n";
        }
    }
    bestandSchrijven.close();
}

inline void FileIO::outputParkLijstNaarBestand() {
    std::wofstream bestandSchrijven{PARCS_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << PARCS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }

    for (auto abn: abonnees) {
        if (abn->parkBeheerder == nullptr) {
            continue;
        }
        if (!abn->parkBeheerder->isToegevoegd) {
            continue;
        }

        bestandSchrijven << abn->parkBeheerder->parkID << SCHEIDER
                         << abn->abonneeId << SCHEIDER
                         << abn->parkBeheerder->beginDatum->datumNaarString() << SCHEIDER
                         << abn->parkBeheerder->eindDatum->datumNaarString() << SCHEIDER
                         << abn->parkBeheerder->consumingPointsPerDag << SCHEIDER
                         << abn->parkBeheerder->minLuxuryLevel << SCHEIDER
                         << abn->parkBeheerder->parkStatus << L"\n";
    }
    bestandSchrijven.close();
}

inline void FileIO::outputAbonneeNaarBestand() {
    std::wofstream bestandSchrijven{CUSTOMERS_BESTAND, std::ios::app}; // Append mode
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << CUSTOMERS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }

    for (auto &abn: abonnees) {
        bestandSchrijven << abn->abonneeId << SCHEIDER
                         << abn->mail << SCHEIDER
                         << abn->gebruikersnaam << SCHEIDER
                         << abn->wachtwoord << SCHEIDER
                         << abn->locatie << SCHEIDER
                         << abn->krediet << SCHEIDER
                         << abn->getLuxuryLevel() << L"\n";
    }

    bestandSchrijven.close();
}
//FUN OVER
inline void FileIO::outputAbonneeNaarBestand(std::vector<Abonnee *> newabonnee) {
    std::wofstream bestandSchrijven{CUSTOMERS_BESTAND, std::ios::app}; // Append mode
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << CUSTOMERS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }

    bestandSchrijven << L"\n" << newabonnee[0]->abonneeId << SCHEIDER
                     << newabonnee[0]->mail << SCHEIDER
                     << newabonnee[0]->gebruikersnaam << SCHEIDER
                     << newabonnee[0]->wachtwoord << SCHEIDER
                     << newabonnee[0]->locatie << SCHEIDER
                     << newabonnee[0]->krediet << SCHEIDER
                     << newabonnee[0]->getLuxuryLevel();

    bestandSchrijven.close();
}

inline void FileIO::outputParkNaarBestand() {
    std::wofstream bestandSchrijven{VACATIONPARKS_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << VACATIONPARKS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }
    for (Park *park: parkVector) {
        bestandSchrijven << park->parkID << SCHEIDER
                         << park->beheerder->abonneeId << SCHEIDER
                         << park->locatie << SCHEIDER
                         << park->parkDescription << SCHEIDER
                         << park->getLuxuryLevel() << L"\n";
    }
    bestandSchrijven.close();


}


inline bool FileIO::abonneeInloggen(std::wstring gebruikersnaam, std::wstring wachtwoord) {
    int count = 0;
    for (Abonnee *abn: abonnees) {
//        std::cout << (abn->gebruikersnaam == gebruikersnaam) << (abn->wachtwoord == wachtwoord);
        if (abn->gebruikersnaam == gebruikersnaam && abn->wachtwoord == wachtwoord) {
            huidigUser = abn;
            for (std::wstring loc: PLEKKEN) {
                if (loc == huidigUser->locatie) {
                    count++;
                    break;
                }
            }
            if (count == 0) {
                std::wcout  << L"The app do not support you in your region! \n" ;
                hoofdScherm();
                return false;
            }
            std::wcout  << L"U bent in het systeem...laden...\n\n" ;
            return true;
        }
    }
    std::wcout  << L"\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
    return false;
}

inline void FileIO::abonneeRegistreren() {
    int keuze;
    int subKeuze;
    std::wstring gebruikersnaam, wachtwoord, umail, locatie;
    std::vector<Abonnee*> newlyRegisteredAbnVector{};
    std::wcout  << L"\t---ABONNEE REGISTRATIE---\n" ;
    std::wcin.ignore();
    do {
        std::wcout  << LR"(Uw gebruikersnaam invoeren:   )" ;
        getline(std::wcin, gebruikersnaam);
    } while (!isGebrGeldig(gebruikersnaam));

    do {
        std::wcout  << LR"(Uw wachtwoord invoeren:   )" ;
        getline(std::wcin, wachtwoord);
    } while (!isWachtGeldig(wachtwoord));
// TODO implement email ipv umail
    do {
        std::wcout  << LR"(Uw e-mail invoeren:   )" ;
        getline(std::wcin, umail);
    } while (!geldigeMail(umail));


    std::wcout  << L"1. Kies the locaties the app support \n" ;
    std::wcout  << L"2. Enter the locatie yourself \n" ;
    keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::wcout  << L"Kies een van de volgende locaties: \n" ;
            std::wcout  << L"1.BOOM\t2.WILLEBROEK\t3.RUMST\n" ;
            subKeuze = menuKeuze(1, 3);
            switch (subKeuze) {
                case 1:
                    locatie = PLEKKEN[0];
                    break;
                case 2:
                    locatie = PLEKKEN[1];
                    break;
                case 3:
                    locatie = PLEKKEN[2];
                    break;
            }
            break;
        case 2:
            std::wcin.ignore();
            std::wcout  << LR"(Uw locatie invoeren:   )" ;
            getline(std::wcin, locatie);
            break;
    }
    Abonnee *newAbn = new Abonnee(gebruikersnaam, wachtwoord, L"ABN" + std::to_wstring(abonnees.size() + 1), umail,
                                  OORSPRONKELIJKE_KREDIETEN, OORSPRONKELIJKE_SCORES, locatie);
    newlyRegisteredAbnVector.push_back(newAbn);
//    flush ASAP w fun overloading
    outputAbonneeNaarBestand(newlyRegisteredAbnVector);
    std::wcout  << L"Registratie ging oke.\n" ;
    hoofdScherm();
}

inline Datum *FileIO::stringToDatum(std::wstring &datum) {
    std::vector<std::wstring> gegLijst = mijnStrTok(datum, '/');
    Datum *geconverteerdeDatum = new Datum(std::stoi(gegLijst[0]), std::stoi(gegLijst[1]), std::stoi(gegLijst[2]));
    return geconverteerdeDatum;

}

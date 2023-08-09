//
// Created by r0834721 on 31/7/2023
//

#include "FileIO.h"

FileIO::FileIO() {
    inputBeheerderToSys();
    inputAbonneeToSys();
    inputParkToSys();
//    inputAbnParkToSys();
//    inputParkLijstToSys();
//    inputBookingToSys();
    hoofdScherm();
}

inline std::string FileIO::strSnijden(std::string &str) {

    std::string goeieStr;
    for (char c: str) {
        if (c == L' ') {
            continue;
        } else {
            goeieStr += c;
        }
    }
    return goeieStr;

}

inline bool FileIO::stringToBool(const std::string& s) {
    std::string lowerStr = s;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
//    DEBUG
//    std::cout << lowerStr;
    if (lowerStr == "true" || lowerStr == "1" || lowerStr == "yes") return true;
    if (lowerStr == "false" || lowerStr == "0" || lowerStr == "no") return false;

    // Handle other cases as desired (e.g., throw an exception)
    throw std::invalid_argument("\tstringToBool-> CAN'T PARSE FILE PROPERLY... TRYING TO PARSE " + s + " WITH INCORRECT VALUES\n");

}

inline std::vector<std::string> FileIO::mijnStrTok(const std::string& str, char sep) {
    std::vector<std::string> gegLijst;
    std::stringstream stroom;
    stroom << str;
    std::string cell;
    while (std::getline(stroom, cell, sep)) {
        gegLijst.push_back(cell);
    }
    return gegLijst;
}

//
inline bool FileIO::isNumGeldig(std::string &iStr) {
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

inline bool FileIO::isDouble(std::string &iStr) {
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
            std::cout  << "Is geen nummer!!! :( Nogeens: " ;
            return false;
        }
        if (aantaalPuntjes > 1) {
            std::cout  << "Is geen nummer :( Nogeens" ;
            return false;
        }
    }
    return true;
}

inline bool FileIO::isWachtGeldig(std::string &wachtwoord) {
    //nw: min8-10 tekens, één hletter + kleine letter, cijfer + symbol:
    // w: doorgaan
    std::regex regu("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,10}$");
    wachtwoord = strSnijden(wachtwoord);
    if (std::regex_match(wachtwoord, regu)) {
        return true;
    } else {
        std::cout

                << "min8-10 tekens, één hletter + kleine letter, cijfer + symbol, doe nog eens: \n";
        return false;
    }
}

inline bool FileIO::isGebrGeldig(std::string &gebruikersnaam) {
    std::regex regu("\\s");
    if (std::regex_match(gebruikersnaam, regu)) {
        std::cout  << "Geen spaties toegelaten... Opnieuw \n" ;
        return false;
    } else {
        if (8 > gebruikersnaam.length() || gebruikersnaam.length() > 16) {
            std::cout  << "Tussen 8/16 tekens. Opnieuw? \n" ;
            return false;
        } else {
            for (auto abonnee: abonnees) {
                if (abonnee->getName() == gebruikersnaam ) {
                    std::cout  << "Duplicaat. Probeer het opnieuw met een andere gebruiker: \n" ;
                    return false;
                }
            }
            return true;
        }
    }
}

inline bool FileIO::geldigeMail(std::string &umail) {
    std::regex regul("^[a-zA-Z0-9._%+-]{1,10}@[a-zA-Z0-9.-]{1,10}\\.[a-zA-Z]{2,}$");
    umail = strSnijden(umail);
    if (std::regex_match(umail, regul)) {
        return true;
    } else {
        std::cout  << "Tot 10 chars voor en na @\n" ;
        return false;
    }
}

inline bool FileIO::isDatumGeldig(std::string datum) {
    std::cout << "isDatumGeldig-> Checking...\n";
    std::string dag = datum.substr(0, 2);
    std::string maand = datum.substr(3, 2);
    std::string jaar = datum.substr(6, 4);

    for (int i = 0; i < datum.length(); i++) {
        if (i == 2 || i == 5) {
            if (datum[i] != L'/') {
                std::cout  << "xx/xx/xxxx Datum format aub. Opnieuw proberen \n" ;
                return false;
            }
        } else if (!std::isdigit(datum[i])) {
            std::cout  << "Niet geldig. Opnieuw \n" ;
            return false;
        } else if (std::stoi(maand) > 13 || std::stoi(maand) < 1) {
            std::cout  << "Niet geldig. Opnieuw \n" ;
            return false;
        } else if (std::stoi(dag) > DAG_VSCH_MAAND[std::stoi(maand) - 1]) {
            std::cout  << "Niet geldig. Opnieuw \n" ;
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


inline void FileIO::inputBeheerderToSys() {

    std::ifstream bestandLezen{OWNER_BESTAND};
    std::vector<std::string> gegLijst{};
    std::string gegLijn,name,address,mail,password,location;
    std::cout << R"---(\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ )---" << std::endl;
    if (!bestandLezen.is_open()) {
        std::cerr << "Kan bestand " << OWNER_BESTAND << " niet openen. Probeer het eens opnnieuw.\n";
        return;  //  Als 't bestand iets problematisch heeft
    } else std::cout << "Beheerder aan het laden...\n";

    if (std::getline(bestandLezen, gegLijn)) {
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
    } else {
        std::cerr << "Kon uw beheerdergegevens niet lezen.\n";
        return; // Als je een foutieve lijn krijgt
    }

    if (static_cast<int>(gegLijst.size()) < 2) {
        std::cerr << "Data is in an incorrect format\n";
        return; // Return immediately if the necessary data is not present
    }
    name = gegLijst[0];
    address = gegLijst[1];
    mail = gegLijst[2];
    password = gegLijst[3];
    location = gegLijst[4];

//    CANNOT DO Owner* bc declared at top Classe
    std::cout << "Assigning owner...\n";
    owner = new Owner(name, address,mail,password,location);
}
//
inline int FileIO::menuKeuze(int begin, int eind) {
    int finalKeuze;
    std::string tmpKeuze;
    bool flag;

    do {
        std::cout  << R"(Uw keuze invoeren:   )" ;
        std::cin >> tmpKeuze;
        if (!isNumGeldig(tmpKeuze)) {
            std::cout  << "\nKeuze is only number! Try again: " ;
            flag = false;
            continue;
        }
        finalKeuze = std::stoi(tmpKeuze);
        if (finalKeuze < begin || finalKeuze > eind) {
            std::cout  << "Tussen " << begin << " en " << eind << " Opnieuw: " ;
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
    std::cout << R"---(\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ )---" << std::endl;
    std::cout << R"---(
                            Discover Vacation Parks: Your Gateway to an unforgettable Escapes and Luxury Stays
      ::::.
        _____A_             Explore Our Parks, Choose Your Ideal Accommodation
       /      /\            Book with Ease, Modify and Create Memories
    __/__/\__/  \___        Empowering Owners, Assisting Employees, :) Customers
---/__|" '' "| /___/\----   Your Dream: Getaway | Our Mission: Manage
   |''|"'||'"| |' '||
   `""`""))""`"`""""        created by r0834721 for a summer retake. All rights reserved)---";
    std::cout  << std::endl << std::endl << std::endl << std::endl ;
    std::cout  << " Use the app as:    1. Customer   2. Owner  3. Staff 4.I've had enough (quit) \n" ;
    std::cout  << "----------------------------------------------------------\n\n" ;

    keuze = menuKeuze(1, 4);
    switch (keuze) {
        case 1:
            loginAbnMenu();
            break;
        case 2:
            beheerderLoginMenu();
            break;
//        case 3:
//            TODO
        case 4:
            outputAbonneeNaarBestand();
            outputParkNaarBestand();
            outputBeheerderNaarBestand();
//            outputBookingNaarBestand();
//            break;
    }
}
//owner menu - basic feature
inline void FileIO::beheerderMenu() {
    int keuze;
    std::cout << R"(
*****************************************
              BEHEERDER MENU
            1.(C)reate (R)ead (U)pdate or (D)elete Parcs
            2.(C)reate (R)ead (U)pdate or (D)elete Accommodations
            3.Back to main menu
*****************************************
)" << std::endl;

    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            beheerderZieParkMenu();
            break;
//        case 1:
//            beheerderZieAbonneeMenu();
//            break;
//        case 3:
//            parkHuurvrijMenu();
//            break;
        case 3:
            hoofdScherm();
            break;
    }


}
//
//inline void FileIO::beheerderZieAbonneeMenu() {
//    int index = 1;
//    std::cout  << "All the abonnee of the systeem: " << "\n" ;
//    std::cout
//            << std::left
//            << std::setw(5)
//            << "Index"
//            << std::left
//            << std::setw(10)
//            << "AbonneeID"
//            << std::left
//            << std::setw(15)
//            << "Full Name"
//            << "\n" ;
//    for (auto abn: abonnees) {
//        std::cout
//                << std::left
//                << std::setw(5)
//                << index
//                << std::left
//                << std::setw(10)
//                << abn->abonneeId
//                << std::left
//                << std::setw(15)
//                << abn->mail
//                << "\n" ;
//        index++;
//    }
//    std::cout << "\n";
//    std::cout  << "\t---1.Zie Customer Detail---\n" << "\t---2.Back to owner menu---\n" ;
//    int keuze = menuKeuze(1, 2);
//    switch (keuze) {
//        case 1:
//            std::cout
//                    << std::left
//                    << std::setw(10)
//                    << "Index"
//                    << std::left
//                    << std::setw(15)
//                    << "AbonneeID"
//                    << std::left
//                    << std::setw(15)
//                    << "Full Name"
//                    << std::left
//                    << std::setw(15)
//                    << "Usersnaam"
//                    << std::left
//                    << std::setw(8)
//                    << "Krediet"
//                    << std::left
//                    << std::setw(15)
//                    << "Locatie"
//                    << std::left
//                    << std::setw(10)
//                    << "Luxury level Score"
//                    << "\n" ;
//            for (int i = 0; i < abonnees.size(); i++) {
//                std::cout
//                        << std::left
//                        << std::setw(10)
//                        << i + 1
//                        << std::left
//                        << std::setw(15)
//                        << abonnees[i]->abonneeId
//                        << std::left
//                        << std::setw(15)
//                        << abonnees[i]->mail
//                        << std::left
//                        << std::setw(15)
//                        << abonnees[i]->gebruikersnaam
//                        << std::left
//                        << std::setw(8)
//                        << abonnees[i]->krediet
//                        << std::left
//                        << std::setw(15)
//                        << abonnees[i]->locatie
//                        << std::left
//                        << std::setw(10)
//                        << abonnees[i]->getLuxuryLevel()
//                        << "\n" ;
//            }
//            std::cout << "\n";
//            std::cout  << abonnees.size() + 1 << ".Back to owner menu\n" ;
//            menuKeuze(abonnees.size() + 1, abonnees.size() + 1);
//            beheerderMenu();
//
//        case 2:
//            beheerderMenu();
//            break;
//    }
//}
//
inline void FileIO::beheerderZieParkMenu() {
    std::cout << R"(
*****************************************
            ALL PARCS OF THE SYSTEM ARE READILY AVAILABLE :)" << std::endl;
//    TODO refactor
    for (auto i: parkVector) {
        std::cout<< std::endl<< std::left<< std::setw(12)
//                Derefence otherwise 0x mem pointer to screeen!
                << *i
                << "\n" ;
    }
    std::cout << R"(
*****************************************
            1. Back to owner menu)" << std::endl;
    int keuze = menuKeuze(1, 1);
    switch (keuze) {
        case 1:
            beheerderMenu();
            break;
    }
}

inline void FileIO::loginAbnMenu() {
    std::string gebruikersnaam, wachtwoord;
    std::cout << R"(
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
            std::cin.ignore();
            std::cout  << R"(Uw gebruikersnaam invoeren:   )" ;
            std::getline(std::cin, gebruikersnaam);
            std::cout  << R"(Uw wachtwoord invoeren:   )" ;
            std::getline(std::cin, wachtwoord);
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
    std::string gebruikersnaam, wachtwoord;

    std::cout << R"(
=======================================
              BEHEERDER MENU
     1.Login As Owner
     2.Back to main menu
=======================================
)" << std::endl;
    switch (menuKeuze(1, 2)) {
        case 1:
            std::cin.ignore();
            std::cout  << R"(Uw gebruikersnaam invoeren:   )" ;
            std::getline(std::cin, gebruikersnaam);
            std::cout  << R"(Uw wachtwoord invoeren:   )" ;
            std::getline(std::cin, wachtwoord);
            if (owner->getName() == gebruikersnaam && owner->getPassword() == wachtwoord) {
                std::cout  << "Succesvol ingelogd... aan het laden... \n\n\n\n" ;
                beheerderMenu();
                break;
            } else {
                std::cout  << "\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
            }
        case 2:
            hoofdScherm();
            break;


    }
}


inline void FileIO::abonneeMenu() {
//    TODO Customers can edit their gegevens
    int keuze;
    std::cout << R"(
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
            std::cout << *huidigUser << std::endl;
            std::cout  << "1. Back to menu...\n" ;
            menuKeuze(1, 1);
            abonneeMenu();
            break;
        case 2:
            searchValidParkMenu();
            break;
//        case 3:
//            zieBookingMenu();
//            break;
//        case 4:
//            gehuurdeParkTonen();
//            break;
//        case 5:
//            toonBookingSent();
//            break;
        case 6:
            huidigUser = nullptr;
            hoofdScherm();
            break;
    }


}

//inline void FileIO::parkHuurvrijMenu() {
//    std::cout  << "\t---UP park FOR RENT MENU ---\n" ;
//    if (huidigUser->parkBeheerder != nullptr) {
//        if (huidigUser->parkBeheerder->isToegevoegd) {
//            std::cout  << "You are having a park for rent: \n" ;
//            huidigUser->parkBeheerder->zieParkInfo();
//            if (huidigUser->parkBeheerder->lijstParkBooking.empty()) {
//                std::cout  << "\n\n---\t1. Omit the park of renting site ---\n"
//                            << "\t---2. Back to abonnee menu ---\n" ;
//                switch (menuKeuze(1, 2)) {
//                    case 1:
//                        deleteInRentPark();
//                        std::cout  << "\tCome back to UP park FOR RENT MENU \n" ;
//                        parkHuurvrijMenu();
//                        break;
//                    case 2:
//                        abonneeMenu();
//                        break;
//                }
//            } else {
//                std::cout  << "\tCome back to abonnee menu \n" ;
//                abonneeMenu();
//            }
//        } else {
//            std::cout  << "You are having a park but not allowing rental yet: \n"
//                        << "1. Add the park for rent\n"
//                        << "2. Back to abonnee menu\n" ;
//            switch (menuKeuze(1, 2)) {
//                case 1:
//                    getInfoLijstParkMenu();
//                    std::cout  << "\nParcs toegevoegd\n\n" ;
//                    parkHuurvrijMenu();
//                    break;
//                case 2:
//                    abonneeMenu();
//                    break;
//            }
//        }
//    } else {
//        std::cout  << "Je hebt geen park. Eenje toevoegen: \n" ;
//        enterParkInfo();
//        parkHuurvrijMenu();
//    }
//}
//
//inline bool FileIO::getInfoLijstParkMenu() {
//    std::string beginDatum, eindDatum, minScores, minKrediets;
//    std::cin.ignore();
//
//    std::cout  << "\tPlease enter of your rental info\n" ;
//    do {
//        do {
//            std::cout  << "Enter the first renting datum " ;
//            std::getline(std::cin, beginDatum);
//        } while (!isDatumGeldig(beginDatum));
//        do {
//            std::cout  << "Enter the eind renting datum " ;
//            std::getline(std::cin, eindDatum);
//        } while (!isDatumGeldig(eindDatum));
//    } while (!isJuisteDatumOrder(stringToDatum(beginDatum), stringToDatum(eindDatum)));
//
//    do {
//        std::cout  << "Enter the required krediets per dag " ;
//        std::getline(std::cin, minKrediets);
//    } while (!isDouble(minKrediets));
//
//    do {
//        std::cout  << "Enter the required minimum scores of renant " ;
//        std::getline(std::cin, minScores);
//    } while (!isDouble(minScores));
//
//    Datum *begin = stringToDatum(beginDatum);
//    Datum *eind = stringToDatum(eindDatum);
//    huidigUser->parkToevoegen(begin, eind, std::stod(minKrediets), std::stod(minScores), STATUS[0]);
//    return true;
//}
//
//inline bool FileIO::enterParkInfo() {
//    std::string parkId, locatie, description;
//    int keuze;
//    std::cout  << "\tPlease enter your park's information\n" ;
//    std::cout  << "\tKies the supported app locatie: " ;
//    std::cout  << "\t1. BOOM \t2.WILLEBROEK \t3.RUMST\n" ;
//    keuze = menuKeuze(1, 3);
//    switch (keuze) {
//        case 1:
//            locatie = PLEKKEN[0];
//            break;
//        case 2:
//            locatie = PLEKKEN[1];
//            break;
//        case 3:
//            locatie = PLEKKEN[2];
//            break;
//    }
//    std::cin.ignore();
//    std::cout  << "\tEnter the description for your park: \n" ;
//    std::getline(std::cin, description);
//    auto *createdPark = new Parcs("PRK" + std::to_string(parkVector.size() + 1), locatie, description);
//    parkVector.push_back(createdPark);
//    huidigUser->createPark(createdPark);
//    return true;
//}
////TODO convert naar BookingTonen
//inline void FileIO::gehuurdeParkTonen() {
//    //Check if huidig abonnee ocupying any park
//    if (huidigUser->tenantLijst.empty()) {
//        std::cout  << "\n\t\tThere are no park you are renting\n\n\t\tBack To Customer Menu\n" ;
//        abonneeMenu();
//    }
//    std::cout  << "\nThe lijst of park you occupied:\n" ;
//    huidigUser->zieTenant();
//    std::cout << "\n---" << huidigUser->tenantLijst.size() + 1 << ".Back to menu\n";
//    int keuze = menuKeuze(1, huidigUser->tenantLijst.size() + 1);
//    if (keuze == huidigUser->tenantLijst.size() + 1) {
//        abonneeMenu();
//    }
//    auto tenantPark = huidigUser->tenantLijst[keuze - 1]->occupyPark;
//    tenantPark->zieParkInfo();
//    std::cout  << "\n"
//                << "\t\t1.Checkout\n"
//                << "\t\t2.Back to menu\n" ;
//    int newKeuze = menuKeuze(1, 2);
//    switch (newKeuze) {
//        case 1:
//            huidigUser->checkout(keuze - 1);
//            std::cout  << "\n\t\tLeft Parcs\n" ;
//            rateTenantMenu(keuze - 1);
//            break;
//        case 2:
//            abonneeMenu();
//            break;
//    }
//
//}
//
//inline void FileIO::rateTenantMenu(int leaveID) {
//    std::cout  << "\n\t\t1.Press 1 to rate the park: " ;
//
//    int keuze = menuKeuze(1, 1);
//    if (keuze == 1) {
//        auto leaveAbonnee = huidigUser->tenantLijst[leaveID];
//        std::string luxury_level;
//
//        while (true) {
//            std::cout  << "\n\t\tPlease leave a luxury_level: " ;
//            std::cin >> luxury_level;
//            if (!isNumGeldig(luxury_level)) {
//                continue;
//            }
//            if (std::stoi(luxury_level) < -10 || std::stoi(luxury_level) > 10) {
//                std::cout  << "The luxury level scores can only be van -10 to 10: " ;
//                continue;
//            }else{
//                break;
//            }
//        }
//        std::cout  << "\nPress 2 to back to the abonnee Menu: " ;
//        if (menuKeuze(2, 2) == 2) {
//            abonneeMenu();
//        }
//
//    }
//}
//
//inline void FileIO::toonBookingSent() {
//    std::cout  << "\nEnter the index of booking that you want to cancel:\n" ;
//    std::cout  << "Lijst of the booking you have sent: \n" ;
//    huidigUser->toonBookingSent();
//    std::cout  << huidigUser->bookingLijst.size() + 1 << ".Back to Customer Menu\n" ;
//    int keuze = menuKeuze(1, huidigUser->bookingLijst.size() + 1);
//    if (keuze == huidigUser->bookingLijst.size() + 1) {
//        abonneeMenu();
//    } else {
//        cancelBookingMenu(keuze);
//    }
//
//}
//
//inline void FileIO::cancelBookingMenu(int ID) {
//    std::cout  << "\nPress 1 to cancel the booking\n" ;
//    std::cout  << "\nPress 2 to back to toon booking sent menu\n" ;
//    int keuze = menuKeuze(1, 2);
//    switch (keuze) {
//        case 1:
//            for (auto i: parkVector) {
//                for (int j = 0; j < i->lijstParkBooking.size(); j++) {
//                    if (i->lijstParkBooking[j]->parkID == huidigUser->bookingLijst[ID - 1]->parkID) {
//                        i->lijstParkBooking.erase(i->lijstParkBooking.begin() + j);
//                    }
//                }
//            }
//            huidigUser->cancelBooking(ID);
//            std::cout  << "\nBooking canceled\nBack to menu:\n" ;
//            toonBookingSent();
//            break;
//
//        case 2:
//            toonBookingSent();
//            break;
//    }
//}
//
inline void FileIO::searchValidParkMenu() {
    std::string locatie;
    int keuze;
    std::cout  << "\tSearch for suitable parks: \n" ;
    std::cout  << "\tKies the city you want to stay: \n\n" ;
    std::cout  << "\t1. BOOM \t2.WILLEBROEK \t3.RUMST\n" ;
    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            locatie = PLEKKEN[0];
            std::cout << "Assigned " << locatie << " to you...";
            break;
        case 2:
            locatie = PLEKKEN[1];
            std::cout << "Assigned " << locatie << " to you...";
            break;
        case 3:
            locatie = PLEKKEN[2];
            std::cout << "Assigned " << locatie << " to you...";
            break;
    }

    validParkMenu(locatie);

}

inline void FileIO::validParkMenu(std::string locatie) {
    std::cout << "validParkMenu-> looking...\n";
    abonneeSuitableParkLijst.clear();
    Booking *booking;
    int keuze;
    getGeldigeParks(locatie);
    std::cout  << abonneeSuitableParkLijst.size() + 1 << ". Back to abonnee menu\n" ;
//    stop the printing
    keuze = menuKeuze(1, abonneeSuitableParkLijst.size() + 1);
    if (keuze == abonneeSuitableParkLijst.size() + 1) {

        abonneeMenu();
    } else {
         std::cout << *abonneeSuitableParkLijst[keuze - 1];
        std::cout  << "\n\n--> 1.\tBooking to rent this park\n\n"
                    << "--> 3.\tBack to park lijst\n" ;
        switch (menuKeuze(1, 3)) {
//            case 1: {
//                if (eind == nullptr) {
//                    booking = new Booking(begin, abonneeSuitableParkLijst[keuze - 1]->eindDatum, huidigUser,
//                                          abonneeSuitableParkLijst[keuze - 1]->parkID,
//                                          AV_STATUS[0]);
//                } else {
//                    booking = new Booking(abonneeSuitableParkLijst[keuze - 1]->beginDatum, eind, huidigUser,
//                                          abonneeSuitableParkLijst[keuze - 1]->parkID,
//                                          AV_STATUS[0]);
//                }
//                abonneeSuitableParkLijst[keuze - 1]->bookingToevoegenToParkBookingLijst(booking);
//                abonneeMenu();
//                break; //function send bookings
//            }
            case 3:
                validParkMenu(locatie);
                break;
        }
    }
}

//inline void FileIO::actionBookingMenu(int bookingID) {
//    std::cout  << "\n\n1.Accept Booking\n2.Decline Booking\n" ;
//    switch (menuKeuze(1, 3)) {
//        case 1:
//            if (!huidigUser->acceptBooking(bookingID)) {
//                std::cout  << "\n" << huidigUser->parkBeheerder->lijstParkBooking.size() + 1
//                            << ".Back to booking menu\n" ;
//                menuKeuze(huidigUser->parkBeheerder->lijstParkBooking.size() + 1,
//                          huidigUser->parkBeheerder->lijstParkBooking.size() + 1);
//                zieBookingMenu();
//            } else {
//                std::cout  << "\nBooking accepted\n" ;
//                abonneeMenu();
//                break;
//            }
//        case 2:
//            //Return owner to booking menu once there is no valid accept yet
//            if (!huidigUser->declineBooking(bookingID)) {
//                std::cout  << "You can not decline a booking that has been accpeted and declinded" ;
//                std::cout  << "\n" << huidigUser->parkBeheerder->lijstParkBooking.size() + 1
//                            << ".Back to booking menu\n" ;
//                menuKeuze(huidigUser->parkBeheerder->lijstParkBooking.size() + 1,
//                          huidigUser->parkBeheerder->lijstParkBooking.size() + 1);
//                zieBookingMenu();
//            } else {
//                std::cout  << "\nBooking Declined\n" ;
//                abonneeMenu();
//                break;
//            }
//
//    }
//}
//
//inline void FileIO::zieBookingMenu() {
//    int keuze;
//    std::cout  << "\n\n\tYour booking vandaag:\n\n" ;
//    if (huidigUser->parkBeheerder == nullptr) {
//        std::cout  << "You do not have a park. So you do not have any booking! \n" ;
//        abonneeMenu();
//    } else {
//        int numberBooking = huidigUser->toonAanvragen();
//        std::cout  << "\n\tKies your option:\n\n" ;
//        std::cout  << "\n\n--> 1.\tPoint the Booking:\n\n"
//                    << "--> 2.\tBack to Menu\n" ;
//        keuze = menuKeuze(1, 3);
//        switch (keuze) {
//            case 1: {
//                std::cout  << "Enter the booking you want to proceed: \n" ;
//                int newKeuze = menuKeuze(1, numberBooking);
//                actionBookingMenu(newKeuze - 1);
//                break;
//            }
//            case 2:
//                abonneeMenu();
//                break;
//        }
//    }
//
//}
//
//inline bool FileIO::abnBookingPark(Datum *beginDatum, Datum *eindDatum, int parkId) {
//    if (parkId > abonneeSuitableParkLijst.size()) {
//        return false;
//    }
//
//}

inline bool FileIO::isValidCityParks(std::string locatie) {
//    TODO look for it INSIDE parcs.dat
    std::cout << "isValidCityParks-> looking for compatible city...\n";
    int count = 0;
    std::string pattern = R"(\b(BOOM|Boom|boom|WILLEBROEK|Willebroek|willebroek|RUMST|Rumst|rumst)\b)";
    std::regex cityRegex(pattern);

    std::smatch match;
    if (std::regex_search(locatie, match, cityRegex)) {
        std::cout << "isValidCityParks-> City found: " << match[0] << std::endl;
        return true;
    } else {
        std::cout << "isValidCityParks-> No city found in the address." << std::endl;
        return false;
    }
}

//inline bool FileIO::isValidEndParks(Datum *eind, Customer *abn, Parcs *park, std::string locatie) {
//    if (!park->isToegevoegd) {
//        return false;
//    }
//
//    if (park == abn->parkBeheerder) {
//        return false;
//    }
//
//    if (locatie != park->locatie) {
//        return false;
//    }
//
//
//    if (park->eindDatum == eind) {
//        return true;
//    }
//
//    return false;
//}

inline bool FileIO::getGeldigeParks(std::string locatie) {
    std::cout << "getGeldigeParks-> Looking... for valid parcs\n";
    abonneeSuitableParkLijst.clear();
    if (!isValidCityParks(locatie)) {
        std::cout  << "\nAsjemenou! Wij konden geen park vinden die voldoet aan uw criteria :(\n" ;
        return false;
    }
    std::cout  << "\nThe suitable park lijst:\n\n" ;
    for (int i = 0; i < parkVector.size(); i++) {
        std::cout  << "--> " << i + 1 << ". " ;
        std::cout  << "Parcs Id: " << parkVector[i]->getID() << "\tAdress: "
                    << parkVector[i]->getAddress() << "\tAccommodation(s): ";
        for (auto* e:parkVector[i]->getAccommodations()) {
           std::cout << *e << "\n" ;
        }
    }
    std::cout << "\n\n";

    return true;
}

//inline bool FileIO::deleteInRentPark() {
//    if (huidigUser->deletePark()) {
//        std::cout  << "\nSuccessfully omit the park\n" ;
//        return true;
//    } else {
//        std::cout  << "The park have bookings hanging. Resolved all before omitting! \n" ;
//        return false;
//    }
//}
inline void FileIO::inputParkToSys() {
    //cab = 9 args
    //hr = 12 args
    parkVector.clear();
    std::string gegLijn;
    std::ifstream bestandLezen{PARCS_BESTAND};
    const int emptyParkLen = 8, oneCabinArgs = 9, oneHRArgs = 12;

    if (!bestandLezen.is_open()) {
        std::cerr << "Kan bestand " << PARCS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";

    } else std::cout << "Loading data...\n";
    while (std::getline(bestandLezen, gegLijn)) {
        std::string name,address;
        Parcs::ParcServices* services;
        std::vector<Accommodations*> accommodations;
        std::cout << "Loading park...\n";
        std::vector<std::string> gegLijst;
        std::vector<bool> ServicesBoolLijst;
        std::vector<bool> LuxBoolLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        //DEBUG
//        for (int i = 0; i < gegLijst.size(); ++i) {
//            std::cout << i << ":" << gegLijst[i] << "\n";
//        }
        name = gegLijst[0];
        address = gegLijst[1];
        //      i starts at 2 bc name and address come first and are not booleans and ends 2+6 bc Accommodations should only be
// init with 6 boolean values.
        for (size_t i = 2; i < emptyParkLen; ++i) {
            ServicesBoolLijst.push_back(stringToBool(gegLijst[i]));
        }
        std::cout << "Loading Parc Services into parc...\n";
        services = new Parcs::ParcServices(ServicesBoolLijst[0],ServicesBoolLijst[1],ServicesBoolLijst[2],ServicesBoolLijst[3],ServicesBoolLijst[4],ServicesBoolLijst[5]);
        if(gegLijst.size()<=emptyParkLen){
//            PARC HAS NO MORE INFO THAN ITS CONSTRUCTOR -> std::string name, std::string address, ParcServices services
// and empty accommodations
            std::cout << "Seems your park has no accommodations...\n";
            auto *park = new Parcs(name, address, *services,accommodations);
            parkVector.push_back(park);
            break;
        }
        else if (gegLijst.size()<=emptyParkLen+oneCabinArgs || gegLijst.size()<=emptyParkLen+oneHRArgs){
//            GETS HERE WHENEVER THERE IS 1 CABIN|HR
            if (gegLijst.size()<=emptyParkLen+oneCabinArgs){
//                1 CAB
                std::cout << "Exactly one Cabin found in parc...\n";
                //        +2 = Start at the end of emptyParkLen:
                //        skip n start @ bool bathroomWithBath
                //        plus grab LuxuryLevel* luxuryLevel (4 bools + 1 str... skip str part)
                for (size_t i = emptyParkLen+2; i < 15; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                std::cout << "Loading 1Cab into parc...\n";
                Cabin* c1 = new Cabin(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                                      LuxBoolLijst[0],
                                      new LuxuryLevel(
                                              LuxBoolLijst[1],LuxBoolLijst[2],
                                              LuxBoolLijst[3],LuxBoolLijst[4],
                                              gegLijst[15]),std::stoi(gegLijst[16]));
                accommodations.push_back(c1);
                c1->setAccommodationId(++idGenerator);
            }
            else if (gegLijst.size()<=emptyParkLen+oneHRArgs){
                //                1 HR
                std::cout << "Exactly one HotelRooom found in parc...\n";
                //        +2 = Start at the end of emptyParkLen:
                //        skip n start @ bool bathroomWithBath
                //        plus grab LuxuryLevel* luxuryLevel (4 bools + 1 str... skip str part)
                for (size_t i = emptyParkLen+2; i < 15; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                std::cout << "Loading 1HR into parc...\n";
                HotelRoom* h1 = new HotelRoom(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                                              LuxBoolLijst[0],
                                              new LuxuryLevel(
                                                      LuxBoolLijst[1],LuxBoolLijst[2],
                                                      LuxBoolLijst[3],LuxBoolLijst[4],
                                                      gegLijst[15]), stringToBool(gegLijst[16]),std::stoi(gegLijst[17]),gegLijst[18],
                                              std::stoi(gegLijst[19]));
                h1->setAccommodationId(++idGenerator);
                accommodations.push_back(h1);

            }
        }
        else if (gegLijst.size()<=emptyParkLen+oneCabinArgs*2||gegLijst.size()<=emptyParkLen+oneHRArgs*2){
            //            GETS HERE WHENEVER THERE ARE 2 CABINS | 2 HRS | 1 CAB+1HR
            if (gegLijst.size()<=emptyParkLen+oneCabinArgs*2){
//                2CABS
                std::cout << "Exactly two Cabins found in parc...\n";
                //        +2 = Start at the end of emptyParkLen:
                //        skip n start @ bool bathroomWithBath
                //        plus grab LuxuryLevel* luxuryLevel (4 bools + 1 str... skip str part)
                for (size_t i = emptyParkLen+2; i < 15; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                for (size_t i = emptyParkLen+oneCabinArgs+2; i < 24; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                std::cout << "Loading 2Cabs into parc...\n";
                Cabin* c1 = new Cabin(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                                      LuxBoolLijst[0],
                                      new LuxuryLevel(
                                              LuxBoolLijst[1],LuxBoolLijst[2],
                                              LuxBoolLijst[3],LuxBoolLijst[4],
                                              gegLijst[15]),std::stoi(gegLijst[16]));
                Cabin* c2 = new Cabin(std::stoi(gegLijst[17]),std::stoi(gegLijst[18]),
                                         LuxBoolLijst[5],
                                         new LuxuryLevel(
                                                 LuxBoolLijst[6],LuxBoolLijst[7],
                                                 LuxBoolLijst[8],LuxBoolLijst[9],
                                                 gegLijst[24]),std::stoi(gegLijst[25]));
                c1->setAccommodationId(++idGenerator);
                c2->setAccommodationId(++idGenerator);
                accommodations.push_back(c1);
                accommodations.push_back(c2);
            }
            else if (gegLijst.size()<=emptyParkLen+oneHRArgs*2){
//                2HRs
                std::cout << "Exactly two HotelRooms found in parc...\n";
                //        +2 = Start at the end of emptyParkLen:
                //        skip n start @ bool bathroomWithBath
                //        plus grab LuxuryLevel* luxuryLevel (4 bools + 1 str... skip str part)
                for (size_t i = emptyParkLen+2; i < 15; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                for (size_t i = emptyParkLen+oneHRArgs+2; i < 24; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                std::cout << "Loading 2HRs into parc...\n";
                HotelRoom* h1 = new HotelRoom(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                                              LuxBoolLijst[0],
                                              new LuxuryLevel(
                                                      LuxBoolLijst[1],LuxBoolLijst[2],
                                                      LuxBoolLijst[3],LuxBoolLijst[4],
                                                      gegLijst[15]), stringToBool(gegLijst[16]),std::stoi(gegLijst[17]),gegLijst[18],
                                              std::stoi(gegLijst[19]));
                h1->setAccommodationId(++idGenerator);
                accommodations.push_back(h1);
                HotelRoom* h2 = new HotelRoom(std::stoi(gegLijst[20]),std::stoi(gegLijst[21]),
                                              LuxBoolLijst[5],
                                              new LuxuryLevel(
                                                      LuxBoolLijst[6],LuxBoolLijst[7],
                                                      LuxBoolLijst[8],LuxBoolLijst[9],
                                                      gegLijst[27]), stringToBool(gegLijst[28]),std::stoi(gegLijst[29]),gegLijst[30],
                                              std::stoi(gegLijst[31]));
                h2->setAccommodationId(++idGenerator);
                accommodations.push_back(h2);
            }
        }
        else if (gegLijst.size()<=emptyParkLen+oneCabinArgs*3||gegLijst.size()<=emptyParkLen+oneHRArgs*3){
            if (gegLijst.size()<=emptyParkLen+oneCabinArgs*3){
//                3CABS
                std::cout << "Exactly 3 Cabins found in parc...\n";
                //        +2 = Start at the end of emptyParkLen:
                //        skip n start @ bool bathroomWithBath
                //        plus grab LuxuryLevel* luxuryLevel (4 bools + 1 str... skip str part)
                for (size_t i = emptyParkLen+2; i < 15; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                for (size_t i = emptyParkLen+oneCabinArgs+2; i < 24; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                for (size_t i = emptyParkLen+oneCabinArgs*2+2; i < 33; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                std::cout << "Loading 3Cabs into parc...\n";
                Cabin* c1 = new Cabin(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                                      LuxBoolLijst[0],
                                      new LuxuryLevel(
                                              LuxBoolLijst[1],LuxBoolLijst[2],
                                              LuxBoolLijst[3],LuxBoolLijst[4],
                                              gegLijst[15]),std::stoi(gegLijst[16]));

                Cabin* c2 = new Cabin(std::stoi(gegLijst[17]),std::stoi(gegLijst[18]),
                                      LuxBoolLijst[5],
                                      new LuxuryLevel(
                                              LuxBoolLijst[6],LuxBoolLijst[7],
                                              LuxBoolLijst[8],LuxBoolLijst[9],
                                              gegLijst[24]),std::stoi(gegLijst[25]));

                Cabin* c3 = new Cabin(std::stoi(gegLijst[26]),std::stoi(gegLijst[27]),
                                      LuxBoolLijst[10],
                                      new LuxuryLevel(
                                              LuxBoolLijst[11],LuxBoolLijst[12],
                                              LuxBoolLijst[13],LuxBoolLijst[14],
                                              gegLijst[33]),std::stoi(gegLijst[34]));
                c1->setAccommodationId(++idGenerator);
                c2->setAccommodationId(++idGenerator);
                c3->setAccommodationId(++idGenerator);
                accommodations.push_back(c1);
                accommodations.push_back(c2);
                accommodations.push_back(c3);
            }
            else if (gegLijst.size()<=emptyParkLen+oneHRArgs*3){
                //                3HRs
                std::cout << "Exactly 3 HotelRooms found in parc...\n";
                //        +2 = Start at the end of emptyParkLen:
                //        skip n start @ bool bathroomWithBath
                //        plus grab LuxuryLevel* luxuryLevel (4 bools + 1 str... skip str part)
                for (size_t i = emptyParkLen+2; i < 15; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                for (size_t i = emptyParkLen+oneHRArgs+2; i < 24; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                for (size_t i = emptyParkLen+oneHRArgs*2+2; i < 33; ++i) {
                    LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
                }
                std::cout << "Loading 3HRs into parc...\n";
                HotelRoom* h1 = new HotelRoom(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                                              LuxBoolLijst[0],
                                              new LuxuryLevel(
                                                      LuxBoolLijst[1],LuxBoolLijst[2],
                                                      LuxBoolLijst[3],LuxBoolLijst[4],
                                                      gegLijst[15]), stringToBool(gegLijst[16]),std::stoi(gegLijst[17]),gegLijst[18],
                                              std::stoi(gegLijst[19]));

                HotelRoom* h2 = new HotelRoom(std::stoi(gegLijst[20]),std::stoi(gegLijst[21]),
                                              LuxBoolLijst[5],
                                              new LuxuryLevel(
                                                      LuxBoolLijst[6],LuxBoolLijst[7],
                                                      LuxBoolLijst[8],LuxBoolLijst[9],
                                                      gegLijst[27]), stringToBool(gegLijst[28]),std::stoi(gegLijst[29]),gegLijst[30],
                                              std::stoi(gegLijst[31]));

                HotelRoom* h3 = new HotelRoom(std::stoi(gegLijst[32]),std::stoi(gegLijst[33]),
                                      LuxBoolLijst[10],
                                      new LuxuryLevel(
                                              LuxBoolLijst[11],LuxBoolLijst[12],
                                              LuxBoolLijst[13],LuxBoolLijst[14],
                                              gegLijst[39]), stringToBool(gegLijst[40]),std::stoi(gegLijst[41]),gegLijst[42],
                                               std::stoi(gegLijst[43]));
                h1->setAccommodationId(++idGenerator);
                h2->setAccommodationId(++idGenerator);
                h3->setAccommodationId(++idGenerator);
                accommodations.push_back(h1);
                accommodations.push_back(h2);
                accommodations.push_back(h3);
            }
        }
        else if (gegLijst.size()>44){
            throw std::invalid_argument("You can't have more than 3 Accommodations per Parc! Getting " + std::to_string(gegLijst.size()) + " as len\n");
        }
//        DEBUG
//        std::cout << gegLijst.size() << " AND "<< emptyParkLen+oneHRArgs*3 << std::endl;
        std::cout << "Putting services + accommodations into parc...\n";
//        Happens regardless of n nr acco's
        auto *park = new Parcs(name, address, *services,accommodations);
        parkVector.push_back(park);
    }
    bestandLezen.close();
}


//inline void FileIO::inputParkLijstToSys() {
//    std::string gegLijn;
//    std::ifstream bestandLezen{PARCS_BESTAND};
//    if (!bestandLezen.is_open()) {
//        std::cerr << "Kan bestand " << PARCS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//    }
//    Customer *owner;
//    while (std::getline(bestandLezen, gegLijn)) {
//        std::vector<std::string> gegLijst;
//        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
//        Datum *beginDatum = stringToDatum(gegLijst[2]);
//        Datum *eindDatum = stringToDatum(gegLijst[3]);
//        double krediets = std::stod(gegLijst[4]);
//        double scores = std::stod(gegLijst[5]);
//        std::string status = gegLijst[6];
//        std::string beheerderId = gegLijst[1];
//        for (Customer *abn: abonnees) {
//            if (beheerderId == abn->abonneeId) {
//                owner = abn;
//            }
//        }
//        owner->parkToevoegen(beginDatum, eindDatum, krediets, scores, status);
//    }
//    bestandLezen.close();
//}
//
//inline void FileIO::inputAbnParkToSys() {
//    std::string gegLijn;
//    std::ifstream bestandLezen{VACATIONPARKS_BESTAND};
//    Customer *targetAbn;
//    Parcs *abnPark;
//
//    if (!bestandLezen.is_open()) {
//        std::cerr << "Kan bestand " << VACATIONPARKS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//    }
//
//    while (std::getline(bestandLezen, gegLijn)) {
//        std::vector<std::string> gegLijst;
//        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
//        for (Parcs *park: parkVector) {
//            if (gegLijst[0] == park->parkID) {
//                abnPark = park;
//            }
//        }
//        for (Customer *abn: abonnees) {
//            if (gegLijst[1] == abn->abonneeId) {
//                targetAbn = abn;
//            }
//        }
//        targetAbn->createPark(abnPark);
//    }
//    bestandLezen.close();
//
//}

inline void FileIO::inputAbonneeToSys() {
    abonnees.clear();
    std::string gegLijn;
    std::ifstream bestandLezen{CUSTOMERS_BESTAND};

    if (!bestandLezen.is_open()) {
        std::cerr << "Kan bestand " << CUSTOMERS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
    } else std::cout << "Loading customers...\n";

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::string> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
//        calvinjharris_BOOMSESTEENWEG 77H 2800 MECHELEN_charris@london.com_Cosmic@123_BOOM_Bancontact
        auto *abonnee = new Customer(
                gegLijst[0], gegLijst[1], gegLijst[2], gegLijst[3], gegLijst[4], gegLijst[5]);
        abonnees.push_back(abonnee);
    }
    bestandLezen.close();
}

//inline void FileIO::inputBookingToSys() {
//    std::string gegLijn;
//    std::ifstream bestandLezen{BOOKINGS_BESTAND};
//    Customer *targetAbn;
//    Parcs *targetPark;
//
//    if (!bestandLezen.is_open()) {
//        std::cerr << "Kan bestand " << BOOKINGS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//    }
//
//    while (std::getline(bestandLezen, gegLijn)) {
//        std::vector<std::string> gegLijst;
//        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
//        for (Parcs *park: parkVector) {
//            if (gegLijst[1] == park->parkID) {
//                targetPark = park;
//            }
//        }
//        for (Customer *abn: abonnees) {
//            if (gegLijst[0] == abn->abonneeId) {
//                targetAbn = abn;
//            }
//        }
//        Datum *beginDatum = stringToDatum(gegLijst[2]);
//        Datum *eindDatum = stringToDatum(gegLijst[3]);
//        std::string status = gegLijst[4];
//        Booking *av = new Booking(beginDatum, eindDatum, targetAbn, targetPark->parkID, status);
//        targetPark->bookingToevoegenToParkBookingLijst(av);
//        targetAbn->bookingLijst.push_back(av);
//    }
//    bestandLezen.close();
//}
inline void FileIO::outputBeheerderNaarBestand() {
    std::ofstream bestandSchrijven{OWNER_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::cerr << "Kan bestand " << OWNER_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
    }

    bestandSchrijven << owner->getName() << SCHEIDER
                     << owner->getAddress() << SCHEIDER
                     << owner->getMail() << SCHEIDER
                    << owner->getPassword() << SCHEIDER
                     << owner->getLocation() << "\n";
}

//inline void FileIO::outputBookingNaarBestand() {
//    std::ofstream bestandSchrijven{BOOKINGS_BESTAND};
//
//    if (!bestandSchrijven.is_open()) {
//        std::cerr << "Kan bestand " << BOOKINGS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//    }
//
//    for (auto &park: parkVector) {
//        for (auto &abnBooking: park->lijstParkBooking) {
//            bestandSchrijven << abnBooking->aangevraagdByAbonnee->abonneeId << SCHEIDER
//                             << park->parkID << SCHEIDER
//                             << abnBooking->beginDatum->datumNaarString() << SCHEIDER
//                             << abnBooking->eindDatum->datumNaarString() << SCHEIDER
//                             << abnBooking->bookingStatus << "\n";
//        }
//    }
//    bestandSchrijven.close();
//}
//
inline void FileIO::outputAbonneeNaarBestand() {
    std::ofstream bestandSchrijven{CUSTOMERS_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::cerr << "Kan bestand " << CUSTOMERS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
        return;
    } std::cout << "Saving customer changes to file...\n";

    for (auto* abn: abonnees) {
        bestandSchrijven << abn->getName() << SCHEIDER
                         << abn->getAddress() << SCHEIDER
                         << abn->getMail() << SCHEIDER
                         << abn->getPassword() << SCHEIDER
                         << abn->getLocation() << SCHEIDER
                         << abn->getPaymentMethod() << SCHEIDER
                          << "\n";
    }

    bestandSchrijven.close();
}
inline void FileIO::outputParkNaarBestand() {
    std::ofstream bestandSchrijven{PARCS_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::cerr << "Kan bestand " << PARCS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
        return;
    }
    for (Parcs *park: parkVector) {
        auto p = park->getServices();
        bestandSchrijven << park->getName() << SCHEIDER
                         << p.isSubtropicSwimmingPool() << SCHEIDER
                << p.isSportsInfrastructure() << SCHEIDER
                << p.isSubtropicSwimmingPool() << SCHEIDER
                << p.isBowlingAlley() << SCHEIDER
                << p.isBicycleRent() << SCHEIDER
                << p.isChildrensParadise() << SCHEIDER
                << p.isWaterBikes() << SCHEIDER;
        for (auto* e:park->getAccommodations()) {
            bestandSchrijven << e->getNrPeople() << SCHEIDER;
            bestandSchrijven << e->getSize() << SCHEIDER;
            bestandSchrijven << e->isBathroomWithBath() << SCHEIDER;
            bestandSchrijven << e->getLuxuryLevel()->isBBQ() << SCHEIDER;
            bestandSchrijven << e->getLuxuryLevel()->isSurroundSystem() << SCHEIDER;
            bestandSchrijven << e->getLuxuryLevel()->isBreakfastService() << SCHEIDER;
            bestandSchrijven << e->getLuxuryLevel()->isCleaningService() << SCHEIDER;
            bestandSchrijven << e->getLuxuryLevel()->getAccommodationKind() << SCHEIDER;
            if(e->getLuxuryLevel()->getAccommodationKind()=="Cabin")
            {
                // From base to derived? !static but dynamic cast !
                Cabin* c = dynamic_cast<Cabin*>(e);
                bestandSchrijven << c->getBedrooms() << SCHEIDER;
            }
            else if(e->getLuxuryLevel()->getAccommodationKind()=="HotelRoom")
            {
                // From base to derived? !static but dynamic cast !
                HotelRoom* h = dynamic_cast<HotelRoom*>(e);
                bestandSchrijven << h->isChildrenBed() << SCHEIDER;
                bestandSchrijven << h->getFloor() << SCHEIDER;
                bestandSchrijven << h->getLocation() << SCHEIDER;
                bestandSchrijven << h->getNrBeds() << SCHEIDER;
            }
        }
        bestandSchrijven << "\n";
    }
    bestandSchrijven.close();
}


inline bool FileIO::abonneeInloggen(std::string gebruikersnaam, std::string wachtwoord) {
    int count = 0;
    for (Customer *abn: abonnees) {
//        DEBUG
//        std::cout << (abn->gebruikersnaam == gebruikersnaam) << (abn->wachtwoord == wachtwoord);
        if (abn->getName() == gebruikersnaam && abn->getPassword() == wachtwoord) {
            huidigUser = abn;
            for (std::string loc: PLEKKEN) {
                if (loc == huidigUser->getLocation()) {
                    count++;
                    break;
                }
            }
            if (count == 0) {
                std::cout  << "The app do not support you in your region! \n" ;
                hoofdScherm();
                return false;
            }
            std::cout  << "U bent in het systeem...laden...\n\n" ;
            return true;
        }
    }
    std::cout  << "\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
    return false;
}

inline void FileIO::abonneeRegistreren() {
    int keuze;
    int subKeuze;
    std::string gebruikersnaam, adress, umail,wachtwoord, locatie,paymentMethod;
    std::cout  << "\t---ABONNEE REGISTRATIE---\n" ;
    std::cin.ignore();
    do {
        std::cout  << R"(Uw gebruikersnaam invoeren:   )" ;
        getline(std::cin, gebruikersnaam);
    } while (!isGebrGeldig(gebruikersnaam));
    std::cout  << R"(Uw adress invoeren:   )" ;
    getline(std::cin, adress);
    do {
        std::cout  << R"(Uw wachtwoord invoeren:   )" ;
        getline(std::cin, wachtwoord);
    } while (!isWachtGeldig(wachtwoord));
// TODO implement email ipv umail
    do {
        std::cout  << R"(Uw e-mail invoeren:   )" ;
        getline(std::cin, umail);
    } while (!geldigeMail(umail));
    std::cout  << R"(Uw payment method invoeren:   )" ;
    getline(std::cin, paymentMethod);

    std::cout  << "1. Kies the locaties the app support \n" ;
    std::cout  << "2. Enter the locatie yourself \n" ;
    keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::cout  << "Kies een van de volgende locaties: \n" ;
            std::cout  << "1.BOOM\t2.WILLEBROEK\t3.RUMST\n" ;
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
            std::cin.ignore();
            std::cout  << R"(Uw locatie invoeren:   )" ;
            getline(std::cin, locatie);
            break;
    }
//    std::string name,std::string address, std::string mail,std::string password,std::string location, std::string paymentMethod
    Customer *newAbn = new Customer(gebruikersnaam, adress, umail,
                                  wachtwoord, locatie, paymentMethod);
    abonnees.push_back(newAbn);
    std::cout  << "Registratie ging oke.\n" ;
    hoofdScherm();
}

inline Datum *FileIO::stringToDatum(std::string &datum) {
    std::vector<std::string> gegLijst = mijnStrTok(datum, '/');
    Datum *geconverteerdeDatum = new Datum(std::stoi(gegLijst[0]), std::stoi(gegLijst[1]), std::stoi(gegLijst[2]));
    return geconverteerdeDatum;

}

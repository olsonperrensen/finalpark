//
// Created by r0834721 on 31/7/2023
//

#include "FileIO.h"

FileIO::FileIO() {
    inputBeheerderToSys();
//    inputAbonneeToSys();
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

    if (lowerStr == "true" || lowerStr == "1" || lowerStr == "yes") return true;
    if (lowerStr == "false" || lowerStr == "0" || lowerStr == "no") return false;

    // Handle other cases as desired (e.g., throw an exception)
    throw std::invalid_argument("CAN'T PARSE FILE PROPERLY\n");
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
//
//inline bool FileIO::isDouble(std::string &iStr) {
//    int aantaalPuntjes = 0;
//    for (int i = 0; i < iStr.length(); i++) {
//        if (i == 0) {
//            if (iStr[i] == L'.') {
//                aantaalPuntjes++;
//                continue;
//            }
//        }
//        if (iStr[i] == L'.') {
//            aantaalPuntjes++;
//            continue;
//        }
//
//        if (!std::isdigit(iStr[i])) {
//            std::cout  << "Is geen nummer!!! :( Nogeens: " ;
//            return false;
//        }
//        if (aantaalPuntjes > 1) {
//            std::cout  << "Is geen nummer :( Nogeens" ;
//            return false;
//        }
//    }
//    return true;
//}
//
//inline bool FileIO::isWachtGeldig(std::string &wachtwoord) {
//    //nw: min8-10 tekens, één hletter + kleine letter, cijfer + symbol:
//    // w: doorgaan
//    std::regex regu("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,10}$");
//    wachtwoord = strSnijden(wachtwoord);
//    if (std::regex_match(wachtwoord, regu)) {
//        return true;
//    } else {
//        std::cout
//
//                << "min8-10 tekens, één hletter + kleine letter, cijfer + symbol, doe nog eens: \n";
//        return false;
//    }
//}
//
//inline bool FileIO::isGebrGeldig(std::string &gebruikersnaam) {
//    std::regex regu("\\s");
//    if (std::regex_match(gebruikersnaam, regu)) {
//        std::cout  << "Geen spaties toegelaten... Opnieuw \n" ;
//        return false;
//    } else {
//        if (8 > gebruikersnaam.length() || gebruikersnaam.length() > 16) {
//            std::cout  << "Tussen 8/16 tekens. Opnieuw? \n" ;
//            return false;
//        } else {
//            for (auto abonnee: abonnees) {
//                if (abonnee->gebruikersnaam == gebruikersnaam ) {
//                    std::cout  << "Duplicaat. Probeer het opnieuw met een andere gebruiker: \n" ;
//                    return false;
//                }
//            }
//            return true;
//        }
//    }
//}
//
//inline bool FileIO::geldigeMail(std::string &umail) {
//    std::regex regul("^[a-zA-Z0-9._%+-]{1,10}@[a-zA-Z0-9.-]{1,10}\\.[a-zA-Z]{2,}$");
//    umail = strSnijden(umail);
//    if (std::regex_match(umail, regul)) {
//        return true;
//    } else {
//        std::cout  << "Tot 10 chars voor en na @\n" ;
//        return false;
//    }
//}
////TODO remove
//inline bool FileIO::isValidKrediet(Abonnee *abn, Parcs *park) {
//    if (abn->krediet <
//        (park->consumingPointsPerDag * (park->eindDatum->countDatum() - park->beginDatum->countDatum()))) {
//        return false;
//    }
//    return true;
//}
//
//inline bool FileIO::isValidLuxuryLevel(Abonnee *abn, Parcs *park) {
//    if (abn->user_requested_luxury_level < park->minLuxuryLevel) {
//        return false;
//    }
//    return true;
//}
//
//inline bool FileIO::isDatumGeldig(std::string datum) {
//    std::string dag = datum.substr(0, 2);
//    std::string maand = datum.substr(3, 2);
//    std::string jaar = datum.substr(6, 4);
//
//    for (int i = 0; i < datum.length(); i++) {
//        if (i == 2 || i == 5) {
//            if (datum[i] != L'/') {
//                std::cout  << "xx/xx/xxxx Datum format aub. Opnieuw proberen \n" ;
//                return false;
//            }
//        } else if (!std::isdigit(datum[i])) {
//            std::cout  << "Niet geldig. Opnieuw \n" ;
//            return false;
//        } else if (std::stoi(maand) > 13 || std::stoi(maand) < 1) {
//            std::cout  << "Niet geldig. Opnieuw \n" ;
//            return false;
//        } else if (std::stoi(dag) > DAG_VSCH_MAAND[std::stoi(maand) - 1]) {
//            std::cout  << "Niet geldig. Opnieuw \n" ;
//            return false;
//        }
//    }
//    return true;
//}
//
//inline bool FileIO::isJuisteDatumOrder(Datum *begin, Datum *eind) {
//    if (eind->countDatum() - begin->countDatum() > 0) {
//        return true;
//    } else {
//        return false;
//    }
//}
//

inline void FileIO::inputBeheerderToSys() {

    std::ifstream bestandLezen{OWNER_BESTAND};
    std::vector<std::string> gegLijst{};
    std::string gegLijn,name,address,mail,password;

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

//    CANNOT DO Owner* bc declared at top Classe
    std::cout << "Assigning owner...\n";
    owner = new Owner(name, address,mail,password);
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
    std::cout  << " Use the app as:    1. Abonnee   2. Owner  3. Staff 4.I've had enough (quit) \n" ;
    std::cout  << "----------------------------------------------------------\n\n" ;

    keuze = menuKeuze(1, 4);
    switch (keuze) {
//        case 1:
//            loginAbnMenu();
//            break;
        case 2:
            beheerderLoginMenu();
            break;
//        case 3:
//            TODO
        case 4:
//            outputAbonneeNaarBestand();
            outputParkNaarBestand();
//            outputBeheerderNaarBestand();
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
//    std::cout  << "\t---1.Zie Abonnee Detail---\n" << "\t---2.Back to owner menu---\n" ;
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
            1. Back to owner menu)";
    int keuze = menuKeuze(1, 1);
    switch (keuze) {
        case 1:
            beheerderMenu();
            break;
    }
}
//
//inline void FileIO::loginAbnMenu() {
//    std::string gebruikersnaam, wachtwoord;
//    std::cout << R"(
//|||||||||||||||||||||||||||||||||||||||||
//            | ABONNEE PORTAL |
//        1. Register as a new abonnee
//        2. Login as abonnee
//        3. Back to main menu
//|||||||||||||||||||||||||||||||||||||||||
//)" << std::endl;
//
//    switch (menuKeuze(1, 2)) {
//        case 1:
//            abonneeRegistreren();
//            break;
//        case 2:
//            std::cin.ignore();
//            std::cout  << R"(Uw gebruikersnaam invoeren:   )" ;
//            std::getline(std::cin, gebruikersnaam);
//            std::cout  << R"(Uw wachtwoord invoeren:   )" ;
//            std::getline(std::cin, wachtwoord);
//            if (abonneeInloggen(gebruikersnaam, wachtwoord)) {
//                abonneeMenu();
//                break;
//            }
//        case 3:
//            hoofdScherm();
//            break;
//    }
//
//
//}
//
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
//
//
//inline void FileIO::abonneeMenu() {
////    TODO Customers can edit their gegevens
//    int keuze;
//    std::cout << R"(
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//          @@@ABONNEE MENU@@@
//  1.Zie Account's Information
//  2.Zie Available Parks
//  3.Handle Bookings
//  4.Toon gehuurde menu
//  5.Toon Booking Sent
//  6.Logout
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//)" << std::endl;
//    keuze = menuKeuze(1, 8);
//    switch (keuze) {
//        case 1:
//            huidigUser->toonAccountInfo();
//            std::cout  << "1. Back to menu...\n" ;
//            menuKeuze(1, 1);
//            abonneeMenu();
//            break;
//        case 2:
//            searchValidParkMenu();
//            break;
//        case 3:
//            zieBookingMenu();
//            break;
//        case 4:
//            gehuurdeParkTonen();
//            break;
//        case 5:
//            toonBookingSent();
//            break;
//        case 6:
//            huidigUser = nullptr;
//            hoofdScherm();
//            break;
//    }
//
//
//}
//
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
//        std::cout  << "\n\t\tThere are no park you are renting\n\n\t\tBack To Abonnee Menu\n" ;
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
//    std::cout  << huidigUser->bookingLijst.size() + 1 << ".Back to Abonnee Menu\n" ;
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
//inline void FileIO::searchValidParkMenu() {
//    std::string beginDatum;
//    std::string eindDatum;
//    std::string locatie;
//    Datum *eind, *begin;
//    int keuze;
//    std::cout  << "\tSearch for suitable parks: \n" ;
//    std::cout  << "\t---1. Search by your begin dag ---\n" << "\t---2. Search by your eind dag ---\n" ;
//    switch (menuKeuze(1, 2)) {
//        case 1:
//            std::cin.ignore();
//            do {
//                std::cout  << "Enter when you want to rent (dd/mm/yyyy): " ;
//                std::getline(std::cin, beginDatum);
//            } while (!isDatumGeldig(beginDatum));
//            std::cout << beginDatum << "\n";
//            break;
//
//        case 2:
//            std::cin.ignore();
//            do {
//                std::cout  << "Enter when you want to eind renting (dd/mm/yyyy): " ;
//                std::getline(std::cin, eindDatum);
//            } while (!isDatumGeldig(eindDatum));
//            break;
//    }
//
//    std::cout  << "\tKies the city you want to stay: \n\n" ;
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
//
//    if (eindDatum.length() == 0) {
//        eind = nullptr;
//    } else {
//        eind = stringToDatum(eindDatum);
//    }
//
//    if (beginDatum.length() == 0) {
//        begin = nullptr;
//    } else {
//        begin = stringToDatum(beginDatum);
//    }
//
//    validParkMenu(begin, eind, locatie);
//
//}
//
//inline void FileIO::validParkMenu(Datum *begin, Datum *eind, std::string locatie) {
//    abonneeSuitableParkLijst.clear();
//    Booking *booking;
//    int keuze;
//    if (eind == nullptr) {
//        getGeldigeBeginParks(begin, locatie);
//    } else {
//        getGeldigeEndParks(eind, locatie);
//    }
//    std::cout  << abonneeSuitableParkLijst.size() + 1 << ". Back to abonnee menu\n" ;
//    keuze = menuKeuze(1, abonneeSuitableParkLijst.size() + 1);
//    if (keuze == abonneeSuitableParkLijst.size() + 1) {
//
//        abonneeMenu();
//    } else {
//        abonneeSuitableParkLijst[keuze - 1]->zieParkInfo();
//        std::cout  << "\n\n--> 1.\tBooking to rent this park\n\n"
//                    << "--> 3.\tBack to park lijst\n" ;
//        switch (menuKeuze(1, 3)) {
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
//            case 3:
//                validParkMenu(begin, eind, locatie);
//                break;
//        }
//    }
//}
//
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
//
//inline bool FileIO::isValidBeginParks(Datum *begin, Abonnee *abn, Parcs *park, std::string locatie) {
//
//    int count = 0;
//    if (!park->isToegevoegd) {
//        return false;
//    }
//
//    if (park->parkStatus == STATUS[1]) {
//        return false;
//    }
//
//    if (park == abn->parkBeheerder) {
//        return false;
//    }
//
//    if (!isValidLuxuryLevel(abn, park)) {
//        return false;
//    }
//    if (!isValidKrediet(abn, park)) {
//        return false;
//    }
//
//    if (locatie != park->locatie) {
//        return false;
//    }
//
//    if (park->beginDatum->datumNaarString() == begin->datumNaarString()) {
//        return true;
//    }
//    return false;
//
//}
//
//inline bool FileIO::isValidEndParks(Datum *eind, Abonnee *abn, Parcs *park, std::string locatie) {
//    if (!park->isToegevoegd) {
//        return false;
//    }
//
//    if (park->parkStatus == STATUS[1]) {
//        return false;
//    }
//
//    if (park == abn->parkBeheerder) {
//        return false;
//    }
//
//    if (!isValidLuxuryLevel(abn, park)) {
//        return false;
//    }
//    if (!isValidKrediet(abn, park)) {
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
//
//inline bool FileIO::getGeldigeBeginParks(Datum *begin, std::string locatie) {
//    abonneeSuitableParkLijst.clear();
//    for (auto &park: parkVector) {
//        if (isValidBeginParks(begin, huidigUser, park, locatie)) {
//            abonneeSuitableParkLijst.push_back(park);
//        }
//    }
//
//    if (abonneeSuitableParkLijst.empty()) {
//        std::cout  << "\nAsjemenou! Wij konden geen park vinden die voldoet aan uw criteria :(\n" ;
//        return false;
//    }
//
//    std::cout  << "\nThe suitable park lijst:\n\n" ;
//    for (int i = 0; i < abonneeSuitableParkLijst.size(); i++) {
//        std::cout  << "--> " << i + 1 << ". " ;
//        std::cout  << "Parcs Id: " << abonneeSuitableParkLijst[i]->parkID << "\tLocatie: "
//                    << abonneeSuitableParkLijst[i]->locatie << "\tLuxury level: "
//                    << abonneeSuitableParkLijst[i]->getLuxuryLevel() << "\n" ;
//    }
//    std::cout << "\n\n";
//
//    return true;
//}
//
//inline bool FileIO::getGeldigeEndParks(Datum *eind, std::string locatie) {
//    abonneeSuitableParkLijst.clear();
//    for (auto &park: parkVector) {
//        if (isValidEndParks(eind, huidigUser, park, locatie)) {
//
//            abonneeSuitableParkLijst.push_back(park);
//        }
//    }
//
//    if (abonneeSuitableParkLijst.empty()) {
//        std::cout  << "\nAsjemenou! Wij konden geen park vinden die voldoet aan uw criteria :(\n" ;
//        return false;
//    }
//
//    std::cout  << "\nThe suitable park lijst:\n\n" ;
//    for (int i = 0; i < abonneeSuitableParkLijst.size(); i++) {
//        std::cout << "--> " << i + 1 << ". ";
//        std::cout  << "Parcs Id: " << abonneeSuitableParkLijst[i]->parkID << "\tLocatie: "
//                    << abonneeSuitableParkLijst[i]->locatie << "\tLuxury level: "
//                    << abonneeSuitableParkLijst[i]->getLuxuryLevel() << "\n" ;
//    }
//    std::cout << "\n\n";
//
//    return true;
//}
//
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
    parkVector.clear();
    std::string gegLijn,name,address;
    Parcs::ParcServices* services;
    std::vector<Accommodations*> accommodations;
    std::ifstream bestandLezen{PARCS_BESTAND};

    if (!bestandLezen.is_open()) {
        std::cerr << "Kan bestand " << PARCS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";

    } else std::cout << "Loading park...\n";
    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::string> gegLijst;
        std::vector<bool> ServicesBoolLijst;
        std::vector<bool> LuxBoolLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        name = gegLijst[0];
        address = gegLijst[1];
//      i starts at 2 bc name and address come first and are not booleans and ends 2+6 bc Accommodations should only be
// init with 6 boolean values.
        for (size_t i = 2; i < 8; ++i) {
            ServicesBoolLijst.push_back(stringToBool(gegLijst[i]));
        }
        for (size_t i = 11; i < 16; ++i) {
            LuxBoolLijst.push_back(stringToBool(gegLijst[i]));
        }
        std::cout << "Loading Parc Services into parc...\n";
        services = new Parcs::ParcServices(ServicesBoolLijst[0],ServicesBoolLijst[1],ServicesBoolLijst[2],ServicesBoolLijst[3],ServicesBoolLijst[4],ServicesBoolLijst[5]);
//        TEMP SOLUTION : ADD INVENTED DATA
        std::cout << "Loading accommodations into parc...\n";
        accommodations.push_back(
                new Cabin(std::stoi(gegLijst[8]),std::stoi(gegLijst[9]),
                          std::stoi(gegLijst[10]),LuxBoolLijst[0],
                          new LuxuryLevel(
                                  LuxBoolLijst[0],LuxBoolLijst[1],
                                  LuxBoolLijst[2],LuxBoolLijst[3],
                                          gegLijst[16])));
//        accommodations.push_back(new Cabin(2,2,100,0,new LuxuryLevel(1,1,1,1,"Cabin")));
//        accommodations.push_back(new HotelRoom(22, "Manhattan", 5, 1,
//                                               6,900,1,new LuxuryLevel(1,1,1,1,"HotelRoom")));
        std::cout << "Putting services + accommodations into parc...\n";
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
//    Abonnee *owner;
//    while (std::getline(bestandLezen, gegLijn)) {
//        std::vector<std::string> gegLijst;
//        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
//        Datum *beginDatum = stringToDatum(gegLijst[2]);
//        Datum *eindDatum = stringToDatum(gegLijst[3]);
//        double krediets = std::stod(gegLijst[4]);
//        double scores = std::stod(gegLijst[5]);
//        std::string status = gegLijst[6];
//        std::string beheerderId = gegLijst[1];
//        for (Abonnee *abn: abonnees) {
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
//    Abonnee *targetAbn;
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
//        for (Abonnee *abn: abonnees) {
//            if (gegLijst[1] == abn->abonneeId) {
//                targetAbn = abn;
//            }
//        }
//        targetAbn->createPark(abnPark);
//    }
//    bestandLezen.close();
//
//}
//
//inline void FileIO::inputAbonneeToSys() {
//    abonnees.clear();
//    std::string gegLijn;
//    std::ifstream bestandLezen{CUSTOMERS_BESTAND};
//
//    if (!bestandLezen.is_open()) {
//        std::cerr << "Kan bestand " << CUSTOMERS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//    }
//
//    while (std::getline(bestandLezen, gegLijn)) {
//        std::vector<std::string> gegLijst;
//        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
//        auto *abonnee = new Abonnee(gegLijst[2], gegLijst[3], gegLijst[0], gegLijst[1],
//                                    std::stod(gegLijst[5]), std::stod(gegLijst[6]), gegLijst[4]);
//        abonnees.push_back(abonnee);
//    }
//    bestandLezen.close();
//}
//
//inline void FileIO::inputBookingToSys() {
//    std::string gegLijn;
//    std::ifstream bestandLezen{BOOKINGS_BESTAND};
//    Abonnee *targetAbn;
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
//        for (Abonnee *abn: abonnees) {
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
//inline void FileIO::outputBeheerderNaarBestand() {
//    std::ofstream bestandSchrijven{OWNER_BESTAND};
//
//    if (!bestandSchrijven.is_open()) {
//        std::cerr << "Kan bestand " << OWNER_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//    }
//
//    bestandSchrijven << owner->gebruikersnaam << SCHEIDER
//                     << owner->wachtwoord << "\n";
//}
//
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
//inline void FileIO::outputAbonneeNaarBestand() {
//    std::ofstream bestandSchrijven{CUSTOMERS_BESTAND, std::ios::app}; // Append mode
//    if (!bestandSchrijven.is_open()) {
//        std::cerr << "Kan bestand " << CUSTOMERS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//        return;
//    }
//
//    for (auto &abn: abonnees) {
//        bestandSchrijven << abn->abonneeId << SCHEIDER
//                         << abn->mail << SCHEIDER
//                         << abn->gebruikersnaam << SCHEIDER
//                         << abn->wachtwoord << SCHEIDER
//                         << abn->locatie << SCHEIDER
//                         << abn->krediet << SCHEIDER
//                         << abn->getLuxuryLevel() << "\n";
//    }
//
//    bestandSchrijven.close();
//}
////FUN OVER
//inline void FileIO::outputAbonneeNaarBestand(std::vector<Abonnee *> newabonnee) {
//    std::ofstream bestandSchrijven{CUSTOMERS_BESTAND, std::ios::app}; // Append mode
//    if (!bestandSchrijven.is_open()) {
//        std::cerr << "Kan bestand " << CUSTOMERS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
//        return;
//    }
//
//    bestandSchrijven << "\n" << newabonnee[0]->abonneeId << SCHEIDER
//                     << newabonnee[0]->mail << SCHEIDER
//                     << newabonnee[0]->gebruikersnaam << SCHEIDER
//                     << newabonnee[0]->wachtwoord << SCHEIDER
//                     << newabonnee[0]->locatie << SCHEIDER
//                     << newabonnee[0]->krediet << SCHEIDER
//                     << newabonnee[0]->getLuxuryLevel();
//
//    bestandSchrijven.close();
//}
//
inline void FileIO::outputParkNaarBestand() {
    std::ofstream bestandSchrijven{PARCS_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::cerr << "Kan bestand " << PARCS_BESTAND << " niet openen. Doe eens opnieuw\n" "\n";
        return;
    }
    for (Parcs *park: parkVector) {
        bestandSchrijven << park->getName() << SCHEIDER
                         << park->getServices() << SCHEIDER;
        for (auto e:park->getAccommodations()) {
            bestandSchrijven << e << SCHEIDER;
        }
        bestandSchrijven << "\n";
    }
    bestandSchrijven.close();
}


//inline bool FileIO::abonneeInloggen(std::string gebruikersnaam, std::string wachtwoord) {
//    int count = 0;
//    for (Abonnee *abn: abonnees) {
////        std::cout << (abn->gebruikersnaam == gebruikersnaam) << (abn->wachtwoord == wachtwoord);
//        if (abn->gebruikersnaam == gebruikersnaam && abn->wachtwoord == wachtwoord) {
//            huidigUser = abn;
//            for (std::string loc: PLEKKEN) {
//                if (loc == huidigUser->locatie) {
//                    count++;
//                    break;
//                }
//            }
//            if (count == 0) {
//                std::cout  << "The app do not support you in your region! \n" ;
//                hoofdScherm();
//                return false;
//            }
//            std::cout  << "U bent in het systeem...laden...\n\n" ;
//            return true;
//        }
//    }
//    std::cout  << "\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
//    return false;
//}
//
//inline void FileIO::abonneeRegistreren() {
//    int keuze;
//    int subKeuze;
//    std::string gebruikersnaam, wachtwoord, umail, locatie;
//    std::vector<Abonnee*> newlyRegisteredAbnVector{};
//    std::cout  << "\t---ABONNEE REGISTRATIE---\n" ;
//    std::cin.ignore();
//    do {
//        std::cout  << R"(Uw gebruikersnaam invoeren:   )" ;
//        getline(std::cin, gebruikersnaam);
//    } while (!isGebrGeldig(gebruikersnaam));
//
//    do {
//        std::cout  << R"(Uw wachtwoord invoeren:   )" ;
//        getline(std::cin, wachtwoord);
//    } while (!isWachtGeldig(wachtwoord));
//// TODO implement email ipv umail
//    do {
//        std::cout  << R"(Uw e-mail invoeren:   )" ;
//        getline(std::cin, umail);
//    } while (!geldigeMail(umail));
//
//
//    std::cout  << "1. Kies the locaties the app support \n" ;
//    std::cout  << "2. Enter the locatie yourself \n" ;
//    keuze = menuKeuze(1, 2);
//    switch (keuze) {
//        case 1:
//            std::cout  << "Kies een van de volgende locaties: \n" ;
//            std::cout  << "1.BOOM\t2.WILLEBROEK\t3.RUMST\n" ;
//            subKeuze = menuKeuze(1, 3);
//            switch (subKeuze) {
//                case 1:
//                    locatie = PLEKKEN[0];
//                    break;
//                case 2:
//                    locatie = PLEKKEN[1];
//                    break;
//                case 3:
//                    locatie = PLEKKEN[2];
//                    break;
//            }
//            break;
//        case 2:
//            std::cin.ignore();
//            std::cout  << R"(Uw locatie invoeren:   )" ;
//            getline(std::cin, locatie);
//            break;
//    }
//    Abonnee *newAbn = new Abonnee(gebruikersnaam, wachtwoord, "ABN" + std::to_string(abonnees.size() + 1), umail,
//                                  OORSPRONKELIJKE_KREDIETEN, OORSPRONKELIJKE_SCORES, locatie);
//    newlyRegisteredAbnVector.push_back(newAbn);
////    flush ASAP w fun overloading
//    outputAbonneeNaarBestand(newlyRegisteredAbnVector);
//    std::cout  << "Registratie ging oke.\n" ;
//    hoofdScherm();
//}
//
//inline Datum *FileIO::stringToDatum(std::string &datum) {
//    std::vector<std::string> gegLijst = mijnStrTok(datum, '/');
//    Datum *geconverteerdeDatum = new Datum(std::stoi(gegLijst[0]), std::stoi(gegLijst[1]), std::stoi(gegLijst[2]));
//    return geconverteerdeDatum;
//
//}

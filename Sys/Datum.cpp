//
// Created by Admin on 8/4/2023.
//
#include "Datum.h"
#include "../Shared.h"

Datum::Datum(int dag, int maand, int jaar)
        : dag(dag),
          maand(maand),
          jaar(jaar)
{
}




int Datum:: countSchrikkeljaar() {
    int huidigJaar = this->jaar;
    if(this->maand <= 2) {
        huidigJaar--;
    }

    int Schrikkeljaar = huidigJaar / 4 - huidigJaar / 100 + huidigJaar / 400;
    return Schrikkeljaar;
}

int Datum::countDatum() {
    int aantalDagen = this->jaar * 365 + this->dag;

    for(int i = 0; i < this->maand - 1; i++) {
        aantalDagen = aantalDagen + DAG_VSCH_MAAND[i];
    }

    aantalDagen = aantalDagen + this->countSchrikkeljaar();
    return aantalDagen;
}

bool Datum::operator < (Datum &datum2) {

    return  countDatum() - datum2.countDatum() >= 0;
}

int Datum::operator - (Datum &datum2) {
    // Get the difference between two datums
    std::cout << this->countDatum() << "\n";
    std::cout << datum2.countDatum() << "\n";

    return this->countDatum() - datum2.countDatum();
}

std::string Datum ::datumNaarString() {
    std::stringstream ss;
    ss << dag << "/" << maand << "/" << jaar;
    return ss.str();
}


//
// Created by r0834721 - vak YT6254 on 8/4/2023.
//

#ifndef FINALPARK_DATUM_H
#define FINALPARK_DATUM_H
#include <iostream>
#include <sstream>
#define SIZE 50


class Datum {
    private:
        int dag;
        int maand;
        int jaar;
    public:
        Datum();
        Datum(int dag, int maand, int jaar);
        int getDag();
        int countSchrikkeljaar();
        int countDatum();
        bool operator < (Datum &datum2);
        int operator - (Datum &datum2);
//        dunder
    bool operator==(const Datum& other) const {
        return (this->dag==other.dag)&&(this->maand==other.maand)&&
               (this->jaar==other.jaar);
    }
    friend std::ostream& operator<<(std::ostream& os, const Datum& obj)
    {
        os << obj.dag << "/" << obj.maand << "/" << obj.jaar;
        return os;
    }
        std::string datumNaarString();
};
#endif


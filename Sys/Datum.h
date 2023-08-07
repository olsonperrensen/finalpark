//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_ACCOMMODATIONS_H
#define FINALPARK_ACCOMMODATIONS_H
#include <iostream>
#include <sstream>
#define SIZE 50


class Datum {
    private:
        int datum;
        int maand;
        int jaar;
    public:
        Datum();
        Datum(int datum, int maand, int jaar);
        int getDay();
        int countSchrikkeljaar();
        int countDatum();
        bool operator < (Datum &datum2);
        int operator - (Datum &datum2);
        std::wstring datumNaarString();
};
#endif


#ifndef EDA2TRABALHOPRATICO_STREET_H
#define EDA2TRABALHOPRATICO_STREET_H

#include <string>
#include <iostream>
#include "CityList.h"

using namespace std;

class StreetList {
public:
    struct Street{
        int id;
        double distance;
        int holesNr;
        int thievesNr;
        int policeNr;
        Street* next;
        CityList::City* destination;
        Street(int id, double distance, int holesNr, int thievesNr, int policeNr);
    };

    StreetList();

    bool isEmpty();

    void add(Street* newStreet);

    void printList();

private:
    Street* head;
    Street* tail;
    void printStreet(Street* street);
};


#endif //EDA2TRABALHOPRATICO_STREET_H

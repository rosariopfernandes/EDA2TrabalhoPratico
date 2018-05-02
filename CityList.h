#ifndef EDA2TRABALHOPRATICO_CITY_H
#define EDA2TRABALHOPRATICO_CITY_H

#include <string>
#include <iostream>

using namespace std;

class StreetList/*{
public:
    void add();
    void printList();
}*/;
class HouseList;

class CityList {
public:
    struct City{
        int id;
        string name;
        City* next;
        StreetList* streetList;
        HouseList* houseList;
        City(int id, string name);
    };

    CityList();

    bool isEmpty();

    void add(City* newCity);

    City* getById(int id);

    void remove(int id);

    void printCity(int idCity);

    void printList();

private:
    City* head;
    City* tail;
    void printCity(City *city);
};


#endif //EDA2TRABALHOPRATICO_CITY_H

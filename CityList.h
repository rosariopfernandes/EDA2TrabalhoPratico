#ifndef EDA2TRABALHOPRATICO_CITY_H
#define EDA2TRABALHOPRATICO_CITY_H

#include <string>
#include <iostream>
#include <vector>
#include "HouseList.h"

using namespace std;

class StreetList;

class CityList {
public:
    struct City{
        int id;
        string name;
        StreetList* streetList;
        HouseList* houseList;
        City* next;
        City(int id, string name);
    };

    CityList();

    bool isEmpty();

    void add(City* newCity);

    City* getById(int id);

    City* get(int index);

    int size();

    City* pop();

    void printCity(int idCity);

    void printList();

    void addHouses(int idCity, int nrHouses);

    void executeDijkstra(int source);

private:
    City* head;
    City* tail;
    void printCity(City *city);
    struct DijkstraPath
    {
        int city1, city2;
        double distance;
        bool visited;
    };
    vector<DijkstraPath>dijkstraPathTree;

    int graphSize;
    void initTree(int source);
    int getNextVisit();
    void dijkstraShortestPaths();
    void viewShortestPaths();
};


#endif //EDA2TRABALHOPRATICO_CITY_H

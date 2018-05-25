#ifndef EDA2TRABALHOPRATICO_CITY_H
#define EDA2TRABALHOPRATICO_CITY_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
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

    void executeDijkstra(int source, int destination);

    City* head;

    int getRandomCity(int documentCity);

    int solveCrime(City *city, bool explored[], int goal);

private:
    City* tail;
    void printCity(City *city);
    struct DijkstraPath
    {
        int city1, city2;
        double distance;
        bool visited;
    };
    vector<DijkstraPath>dijkstraPathTree;

    vector<int> shortestPath;

    int graphSize;
    void initTree(int source);
    int getNextVisit();
    void dijkstraShortestPaths();
    void findPath(int source, int destination);

    struct StackSuccessores {
        City *city;
        StackSuccessores *next;
    };
    StackSuccessores *headPilha=NULL;

    void pushPilha(City* city);

    City* popPilha();

    int nrCitiesReachable(int rootVertice, vector<bool>exploredCities);
};


#endif //EDA2TRABALHOPRATICO_CITY_H

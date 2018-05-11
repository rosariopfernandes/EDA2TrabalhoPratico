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

private:
    City* head;
    City* tail;
    void printCity(City *city);
    struct Dijkstra_Single_Source_Shortest_Paths
    {
        int city1, city2;
        double distance;
        bool visited;
    };
    vector<Dijkstra_Single_Source_Shortest_Paths>dijkstra_shortest_path_tree;
    void initialize_dijkstra_single_source_shortest_paths(int source_vertex);
    void dijkstra_single_source_shortest_paths(int source_id,int destination_id);
    int next_visit();
    void view_dijkstra_single_source_shortest_paths();
};


#endif //EDA2TRABALHOPRATICO_CITY_H

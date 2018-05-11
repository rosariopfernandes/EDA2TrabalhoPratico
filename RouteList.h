#ifndef EDA2TRABALHOPRATICO_ROUTELIST_H
#define EDA2TRABALHOPRATICO_ROUTELIST_H

#include <iostream>

using namespace std;

class StopoverQueue;

class RouteList {
public:
    struct Route{
        int idRoute;
        int firstCity;
        int lastCity;
        Route* next;
        StopoverQueue* stopoverQueue;
        Route(int idRoute, int firstCity, int lastCity);
    };

    RouteList();

    bool isEmpty();

    void add(Route* route);

    Route* getById(int idRoute);

    void remove(int idRoute);

    void printRoute(int idRoute);

    void printList();

    void printList(int firstCity, int lastCity);

private:
    Route* head;
    Route* tail;
    void printRoute(Route* route);
};


#endif //EDA2TRABALHOPRATICO_ROUTELIST_H

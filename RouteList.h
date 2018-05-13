#ifndef EDA2TRABALHOPRATICO_ROUTELIST_H
#define EDA2TRABALHOPRATICO_ROUTELIST_H

#include <iostream>
#include "StopoverQueue.h"

using namespace std;

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

    Route* getRoute(int firstCity, int lastCity);

    Route* getRoute(Route* otherRoute);

    void remove(int idRoute);

    void printRoute(int idRoute);

    void printList();

    int printListMostExp(int firstCity, int lastCity);

private:
    Route* head;
    Route* tail;
    void printRoute(Route* route);
};


#endif //EDA2TRABALHOPRATICO_ROUTELIST_H

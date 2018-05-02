#ifndef EDA2TRABALHOPRATICO_BRIDGELIST_H
#define EDA2TRABALHOPRATICO_BRIDGELIST_H

#include <string>
#include <iostream>
#include "HouseList.h"

using namespace std;

class BridgeList {
public:
    struct Bridge{
        double distance;
        HouseList::House* destination;
        Bridge* next;
        Bridge(double distance);
    };

    BridgeList();

    bool isEmpty();

    void add(Bridge* bridge);

    void printList();

private:
    Bridge* head;
    Bridge* tail;
    void printBridge(Bridge* bridge);
};


#endif //EDA2TRABALHOPRATICO_BRIDGELIST_H

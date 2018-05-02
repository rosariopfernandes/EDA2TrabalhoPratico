#ifndef EDA2TRABALHOPRATICO_HOUSELIST_H
#define EDA2TRABALHOPRATICO_HOUSELIST_H

#include <string>
#include <iostream>

using namespace std;

class BridgeList;

class HouseList {
public:
    struct House{
        int id;
        House* next;
        BridgeList* bridgeList;
        House(int id);
    };

    HouseList();

    bool isEmpty();

    void add(House* house);

    House* getById(int id);

    void printHouse(int id);

    void printList();

private:
    House* head;
    House* tail;
    void printHouse(House* house);
};


#endif //EDA2TRABALHOPRATICO_HOUSELIST_H

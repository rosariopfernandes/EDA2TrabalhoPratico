#include "HouseList.h"

HouseList::House::House(int id) {
    this->id = id;
    this->next = NULL;
    this->bridgeList = NULL;
}

HouseList::HouseList() {
    head = NULL;
    tail = NULL;
}

bool HouseList::isEmpty() {
    return head == NULL;
}

void HouseList::add(HouseList::House *newHouse) {
    if(isEmpty())
        head = tail = newHouse;
    else
    {
        tail->next = newHouse;
        tail = newHouse;
    }
}

HouseList::House *HouseList::getById(int id) {
    House* house = head;
    while(house!=NULL)
    {
        if(house->id == id)
            return house;
        house = house->next;
    }
    return NULL;
}

void HouseList::printHouse(House *house) {
    cout << "Casa { id=" <<house->id << "}";
}

void HouseList::printHouse(int id) {
    House* house = getById(id);
    printHouse(house);
}

void HouseList::printList() {
    House* house = head;
    while(house!=NULL)
    {
        printHouse(house);
        house = house->next;
    }
}


#include "BridgeList.h"

BridgeList::Bridge::Bridge(double distance, HouseList::House *destination) {
    this->distance = distance;
    this->destination = destination;
}

BridgeList::BridgeList() {
    head = NULL;
    tail = NULL;
}

bool BridgeList::isEmpty() {
    return head == NULL;
}

void BridgeList::add(Bridge *bridge) {
    if(isEmpty())
        head = tail = bridge;
    else
    {
        tail->next = bridge;
        tail = bridge;
    }
}

void BridgeList::printBridge(Bridge *bridge) {
    cout << "Ponte { distance=" << bridge->distance <<", ";
    cout << "destination="<< bridge->destination->id <<"}";
}

void BridgeList::printList() {
    Bridge* bridge = head;
    while(bridge != NULL){
        printBridge(bridge);
        bridge = bridge->next;
    }
}


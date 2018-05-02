#include "StreetList.h"

/**
 * Constructor for the Street Structure
 * @param id
 * @param distance
 * @param holesNr
 * @param thievesNr
 * @param policeNr
 */
StreetList::Street::Street(int id, double distance, int holesNr, int thievesNr, int policeNr) {
    this->id = id;
    this->distance = distance;
    this->holesNr = holesNr;
    this->thievesNr = thievesNr;
    this->policeNr = policeNr;
}

/**
 * Constructor for the Street List
 */
StreetList::StreetList() {
    head = NULL;
}

bool StreetList::isEmpty() {
    return head == NULL;
}

void StreetList::add(Street *newStreet) {
    if(isEmpty())
        head = tail = newStreet;
    else
    {
        tail->next = newStreet;
        tail = newStreet;
    }
}

void StreetList::printList() {
    Street* street = head;
    while(street != NULL){
        printStreet(street);
        street = street->next;
    }
}

void StreetList::printStreet(Street *street) {
    cout <<"Estrada { distance="<< street->distance << ", ";
    cout <<"buracos="<< street->holesNr << ", ";
    cout <<"policias="<< street->policeNr << ", ";
    cout <<"ladrões="<< street->thievesNr << ", ";
    cout <<"destino="<< street->destination->id << "}";
}

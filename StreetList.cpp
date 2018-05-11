#include "StreetList.h"

/**
 * Constructor for the Street Structure
 * @param id
 * @param distance
 * @param holesNr
 * @param thievesNr
 * @param policeNr
 */
StreetList::Street::Street(CityList::City* destination, double distance, int holesNr,
                           int thievesNr, int policeNr) {
    this->id = 0;
    this->destination = destination;
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
    tail = NULL;
}

bool StreetList::isEmpty() {
    return head == NULL;
}

void StreetList::add(Street *newStreet) {
    int previousId;
    if(tail == NULL)
        previousId = 0;
    else
        previousId = tail->id;
    newStreet->id = previousId+1;
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
        cout << endl;
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

StreetList::Street *StreetList::getStreet(int destination) {
    Street *street = head;
    while(street != NULL)
    {
        if(street->destination->id == destination)
        {
            return street;
        }
        street = street->next;
    }
    return NULL;
}

void StreetList::updateStreet(int streetId, int thieves, int police) {
    Street *street = head;
    while(street != NULL)
    {
        if(street->id == streetId)
        {
            /*int auxThieves = street->thievesNr;
            int auxPolice = street->policeNr;*/
            street->thievesNr = thieves;
            street->policeNr = police;
            cout << "SUCESSO! ESTRADA ACTUALIZADA " /*{ID:"<<street->id<<" DESTINO:" << street->destination->id*/
                 //<<" DISTANCIA:"<<street->distance<<"KM} -> "
                    "{ID:"<<streetId<<" DESTINO:" << street->destination->id<<" DISTANCIA:"
                    <<street->distance<<"KM POLICIAS:"<<street->policeNr <<" LADROES:"<<street->policeNr<<"}!"<<endl;
            break;
        }
        street = street->next;
    }
}

StreetList::Street *StreetList::getById(int id) {
    Street *street = head;
    while(street != NULL)
    {
        if(street->id == id)
            return street;
        street = street->next;
    }
    return NULL;
}

void StreetList::printStreet(int source, int destination) {
    Street *street = head;
    while(street != NULL)
    {
        if(street->destination->id == destination)
            cout <<"ID="<<street->id << " ORIGEM="<<source << " DESTINO=" << destination
                 <<" DISTANCIA="<<street->distance <<endl;
        street = street->next;
    }
}

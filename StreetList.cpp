#include "StreetList.h"

StreetList::Street::Street(CityList::City* destination, double distance, int holesNr,
                           int thievesNr, int policeNr) {
    this->id = 0;
    this->destination = destination;
    this->distance = distance;
    this->holesNr = holesNr;
    this->thievesNr = thievesNr;
    this->policeNr = policeNr;
}

StreetList::StreetList() {
    head = NULL;
    tail = NULL;
}

bool StreetList::isEmpty() {
    return head == NULL;
}

void StreetList::add(Street *newStreet) {
    int previousStreetId;
    if(tail == NULL)
        previousStreetId = 0;
    else
        previousStreetId = tail->id;
    newStreet->id = previousStreetId+1;
    if(isEmpty())
        head = tail = newStreet;
    else
    {
        tail->next = newStreet;
        tail = newStreet;
    }
}

void StreetList::printList() {
    Street* aux = head;
    while(aux != NULL){
        printStreet(aux);
        cout << endl;
        aux = aux->next;
    }
}

void StreetList::printStreet(Street *street) {
    cout <<"Estrada { distance="<< street->distance << ", ";
    cout <<"buracos="<< street->holesNr << ", ";
    cout <<"policias="<< street->policeNr << ", ";
    cout <<"ladrões="<< street->thievesNr << ", ";
    cout <<"destino="<< street->destination->id << "}";
}

void StreetList::updateStreet(int streetId, int thieves, int police) {
    Street *aux = head;
    while(aux != NULL)
    {
        if(aux->id == streetId)
        {
            aux->thievesNr = thieves;
            aux->policeNr = police;
            cout << "SUCESSO! ESTRADA ACTUALIZADA {ID:"<<streetId
                 <<" DESTINO:" << aux->destination->id
                 <<" DISTANCIA:"<<aux->distance
                 <<"KM POLICIAS:"<<aux->policeNr
                 <<" LADROES:"<<aux->policeNr
                 <<"}!"<<endl;
            break;
        }
        aux = aux->next;
    }
}

StreetList::Street *StreetList::getById(int idStreet) {
    Street *aux = head;
    while(aux != NULL)
    {
        if(aux->id == idStreet)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

void StreetList::printStreet(int source, int destination) {
    Street *aux = head;
    while(aux != NULL)
    {
        if(aux->destination->id == destination)
            cout <<"ID="<<aux->id << " ORIGEM="<<source << " DESTINO=" << destination
                 <<" DISTANCIA="<<aux->distance <<endl;
        aux = aux->next;
    }
}

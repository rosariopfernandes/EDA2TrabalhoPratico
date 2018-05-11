#include "CityList.h"

/** Constructor for the City struct **/
CityList::City::City(int id, string name) {
    this->id = id;
    this->name = name;
    this->next = NULL;
    this->streetList = NULL;
    this->houseList = NULL;
}

/**
 * Constructor for the City class
 */
CityList::CityList() {
    head = NULL;
    tail = NULL;
}

/**
 * Checks if the city list has elements
 * @return true if there are no elements in the list, false otherwise
 */
bool CityList::isEmpty() {
    return head == NULL;
}

/**
 * Adds a new city to the list
 * @param newCity the city to be added to the list
 */
void CityList::add(City *newCity) {
    if(isEmpty())
        head = tail = newCity;
    else
    {
        tail->next = newCity;
        tail = newCity;
    }
}

/**
 * Returns the city with the id specified
 * @param id id of the desired city
 * @return the city with that id, or NULL if it does not exist
 */
CityList::City* CityList::getById(int id) {
    City* city = head;
    while(city!=NULL)
    {
        if(city->id == id)
            return city;
        city = city->next;
    }
    return NULL;
}

/**
 * Prints the specified city to stdout
 * @param city - the city to print
 */
void CityList::printCity(City *city) {
    cout << "Cidade:{ id=" << city->id << ", ";
    cout << "nome=" << city->name << ", ";
    cout << "estradas={}";
    //city->streetList->printList();
    cout << "}";
}

/**
 * Finds the city with the specified id
 * and prints it to stdout
 * @param idCity - the id of the city to print
 */
void CityList::printCity(int idCity) {
    City* city = getById(idCity);
    if(city != NULL)
        printCity(city);
}

/**
 * Prints all the cities on the list
 */
void CityList::printList() {
    City* city = head;
    while(city!=NULL)
    {
        printCity(city);
        cout << endl;
        city = city->next;
    }
}

CityList::City *CityList::get(int index) {
    City* city = head;
    int currentIndex = 0;
    while(city!=NULL)
    {
        if(currentIndex == index)
            return city;
        currentIndex++;
        city = city->next;
    }
    return NULL;
}

int CityList::size() {
    City* city = head;
    int size = 0;
    while(city!=NULL)
    {
        size++;
        city = city->next;
    }
    return size;
}

CityList::City *CityList::pop() {
    if(isEmpty())
        return NULL;
    City* city = head;
    head = head->next;
    return city;
}

void CityList::addHouses(int idCity, int nrHouses) {
    City *city = getById(idCity);
    if(city == NULL)
        cout <<"ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << idCity;
    else
    {
        city->houseList = new HouseList;
        for(int i=0; i< nrHouses; i++)
            city->houseList->add(new HouseList::House(i));
        cout << "SUCESSO! FORAM ADICIONADAS " << nrHouses << " NA CIDADE " << city << endl;
    }
}

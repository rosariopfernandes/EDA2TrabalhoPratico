#include "CityList.h"

/** Constructor for the City struct **/
CityList::City::City(int id, string name) {
    this->id = id;
    this->name = name;
    this->next = NULL;
    this->streetList = NULL;
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
    //city->streetList->printList(); TODO: Find a way to fix this
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


#include <iostream>
#include "CityList.h"
#include "StreetList.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    CityList *cityList = new CityList;
    CityList::City* city = new CityList::City(1, "Hello");
    city->streetList = new StreetList;

    StreetList::Street* street = new StreetList::Street(1, 200, 13, 2, 2);
    street->next = NULL;
    street->destination = new CityList::City(2,"World");

    city->streetList->add(street);
    cityList->add(city);
    cityList->printList();
    cityList->getById(1)->streetList->printList();
    return 0;
}

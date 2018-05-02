#include <iostream>
#include "CityList.h"
#include "StreetList.h"
#include "HouseList.h"
#include "BridgeList.h"

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

    //Houses and Bridges
    cout << endl;
    city->houseList = new HouseList;
    HouseList::House* house = new HouseList::House(10);
    house->bridgeList = new BridgeList;

    BridgeList::Bridge* bridge = new BridgeList::Bridge(200);
    bridge->next = NULL;
    bridge->destination = new HouseList::House(20);


    house->bridgeList->add(bridge);
    city->houseList->add(house);
    city->houseList->printList();
    city->houseList->getById(10)->bridgeList->printList();


    return 0;
}

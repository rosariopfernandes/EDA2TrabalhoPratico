#include "CityList.h"
#include "StreetList.h"

/** Constructor for the City struct **/
CityList::City::City(int id, string name) {
    this->id = id;
    this->name = name;
    this->next = NULL;
    this->streetList = new StreetList;
    this->houseList = NULL;
}

/**
 * Constructor for the City class
 */
CityList::CityList() {
    head = NULL;
    tail = NULL;
    graphSize = 0;
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
    graphSize++;
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
    cout << city->id << ". " << city->name;
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
        cout << "SUCESSO! FORAM ADICIONADAS " << nrHouses << " NA CIDADE " << idCity << endl;
    }
}

void CityList::initTree(int source) {
    DijkstraPath dijkstraPath;
    City *city = head;
    dijkstraPathTree = vector<DijkstraPath>();
    while(city!=NULL)
    {
        dijkstraPath.city1 = -1;
        dijkstraPath.city2 = city->id;
        dijkstraPath.distance = city->id == source ? 0 : 99999;
        dijkstraPath.visited = false;

        dijkstraPathTree.push_back(dijkstraPath);
        city = city->next;
    }
}

int CityList::getNextVisit() {
    double minDistance = 99999;
    int nextVisit = -1;
    for(int i =0; i<dijkstraPathTree.size();i++)
    {
        if(minDistance >= dijkstraPathTree[i].distance &&
                !dijkstraPathTree[i].visited)
        {
            minDistance = dijkstraPathTree[i].distance;
            nextVisit = i;
        }
    }
    return nextVisit;
}

void CityList::dijkstraShortestPaths() {
    StreetList *streetList;
    StreetList::Street *street;
    int treeSize = 0;
    int nextVisitPosition, nextVisitDestination;
    double nextVisitDistance;
    while(treeSize != graphSize)
    {
        nextVisitPosition = getNextVisit();
        nextVisitDistance = dijkstraPathTree[nextVisitPosition].distance;
        nextVisitDestination = dijkstraPathTree[nextVisitPosition].city2;

        streetList = getById(nextVisitDestination)->streetList;
        street = streetList->head;
        while(street!=NULL)
        {
            for(int i=0; i< dijkstraPathTree.size();i++)
            {
                if(dijkstraPathTree[i].city2 == street->destination->id)
                {
                    if(dijkstraPathTree[i].distance > street->distance + nextVisitDistance)
                    {
                        dijkstraPathTree[i].distance = street->distance + nextVisitDistance;
                        dijkstraPathTree[i].city1 = nextVisitDestination;
                        //cout << nextVisitDestination << "to" << street->destination->id << endl;
                    }
                }
            }
            street = street->next;
        }
        dijkstraPathTree[nextVisitPosition].visited = true;
        treeSize++;
    }
}

void CityList::executeDijkstra(int source, int destination) {
    initTree(source);
    dijkstraShortestPaths();
    shortestPath = vector<int>();
    findPath(source, destination);
    for(DijkstraPath path : dijkstraPathTree)
        if(path.city1 != -1 && path.city2 == destination)
            cout << "DISTANCIA TOTAL: " << path.distance << endl;
}

void CityList::findPath(int source, int destination) {
    if(destination == source)
    {
        shortestPath.push_back(source);
        reverse(shortestPath.begin(), shortestPath.end());
        for(int i=0;i<shortestPath.size();i++)
        {
            if(i!=0)
                cout << "->";
            cout << shortestPath[i];
        }
        cout << endl;
    }
    else
    {
        for(DijkstraPath path : dijkstraPathTree)
        {
            if(path.city1 != -1 && path.city2 == destination)
            {
                shortestPath.push_back(destination);
                findPath(source, path.city1);
            }
        }
    }
}

int CityList::getRandomCity(int documentCity) {
    vector<bool> explored = vector<bool>();
    for(City *aux = head;aux != NULL; aux = aux->next)
        explored.push_back(false);

    //Verificar quantas cidades são alcançaveis partindo de documentCity
    int citiesReachable = nrCitiesReachable(documentCity, explored);

    random_device rd;
    mt19937 mt(rd());

    uniform_int_distribution<int> distribution(1, citiesReachable);
    int randomCity = distribution(mt);
    return randomCity;
}

int CityList::nrCitiesReachable(int rootVertice, vector<bool>exploredCities) {
    City *city = getById(rootVertice);
    pushPilha(city);
    int citiesReached = 0;
    while(headPilha != NULL)
    {
        city = popPilha();
        if(city != NULL) {
            if (!exploredCities[city->id]) {
                exploredCities[city->id] = true;
                StreetList::Street *street = city->streetList->head;
                while (street != NULL) {
                    pushPilha(street->destination);
                    street = street->next;
                }
                citiesReached++;
            }
        }
    }
    return citiesReached;
}

void CityList::pushPilha(City* city) {
    StackSuccessores *novo_destino = new StackSuccessores;
    novo_destino->city=city;
    novo_destino->next = headPilha;
    headPilha = novo_destino;
}

CityList::City *CityList::popPilha() {
    City *city;
    if(headPilha!=NULL)
    {
        city = headPilha->city;
        headPilha = headPilha->next;
        return city;
    }
    return NULL;
}

int CityList::solveCrime(City *city, bool explored[], int goal){
    pushPilha(city);
    int citiesReached = 0;
    while(headPilha != NULL)
    {
        city = popPilha();
        if(city != NULL) {
            if (!explored[city->id]) {
                explored[city->id] = true;
                StreetList::Street *street = city->streetList->head;
                while (street != NULL) {
                    pushPilha(street->destination);
                    street = street->next;
                }
                citiesReached++;
                if(citiesReached == goal) {
                    return city->id;
                }
            }
        }
    }
    return -1;
}
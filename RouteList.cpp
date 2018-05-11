
#include "RouteList.h"
#include "StopoverQueue.h"

RouteList::Route::Route(int idRoute, int firstCity, int lastCity) {
    this->idRoute = idRoute;
    this->firstCity = firstCity;
    this->lastCity = lastCity;
    next = NULL;
    stopoverQueue = NULL;
}

RouteList::RouteList() {
    head = NULL;
    tail = NULL;
}

bool RouteList::isEmpty() {
    return head == NULL;
}

void RouteList::add(RouteList::Route *route) {
    if(isEmpty())
        head = tail = route;
    else
    {
        tail->next = route;
        tail = route;
    }
}

RouteList::Route *RouteList::getById(int idRoute) {
    Route* route = head;
    while(route!=NULL)
    {
        if(route->idRoute == idRoute)
            return route;
        route = route->next;
    }
    return NULL;
}

void RouteList::printRoute(int idRoute) {
    Route* route = getById(idRoute);
    if(route != NULL)
        printRoute(route);
}

void RouteList::printRoute(RouteList::Route *route) {
    cout << "Route { idRoute = " << route->idRoute;
    cout << ", firstCity = " << route->firstCity;
    cout << ", lastCity = " << route->lastCity << " }" << endl;
}

void RouteList::printList() {
    Route* route = head;
    while(route!=NULL)
    {
        printRoute(route);
        cout << endl;
        route = route->next;
    }
}

void RouteList::printList(int firstCity, int lastCity) {
    if(isEmpty())
        return;
    Route* route = head;
    int mostExpensiveId = route->idRoute;
    double mostExpensivePrice = route->stopoverQueue->getTotalDistance();
    StopoverQueue *queue;
    double routePrice;
    while(route!=NULL)
    {
        if(route->firstCity == firstCity && route->lastCity == lastCity)
        {
            queue = route->stopoverQueue;
            routePrice = queue->getTotalDistance();
            if(routePrice > mostExpensivePrice)
                mostExpensiveId = route->idRoute;
            cout << route->idRoute<<". ORIGEM="<<firstCity<<" DESTINO="<<lastCity
                 << " DISTANCE="<<routePrice << endl;
        }

        route = route->next;
    }
    cout << "A ROTA MAIS CARA É " << mostExpensiveId << endl;
}

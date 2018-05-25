
#include "RouteList.h"

RouteList::Route::Route(int firstCity, int lastCity) {
    this->idRoute = 0;
    this->firstCity = firstCity;
    this->lastCity = lastCity;
    next = NULL;
    stopoverQueue = new StopoverQueue;
}

RouteList::RouteList() {
    head = NULL;
    tail = NULL;
}

bool RouteList::isEmpty() {
    return head == NULL;
}

void RouteList::add(RouteList::Route *route) {
    int previousRouteId;
    if(tail == NULL)
        previousRouteId = 1;
    else
        previousRouteId = tail->idRoute;
    route->idRoute = previousRouteId+1;
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

int RouteList::printListMostExp(int firstCity, int lastCity) {
    Route* route = head;
    int mostExpensiveId = -1;
    double mostExpensivePrice = route->stopoverQueue->getTotalDistance();
    StopoverQueue *queue;
    double routePrice;
    while(route!=NULL)
    {
        if(route->firstCity == firstCity && route->lastCity == lastCity)
        {
            queue = route->stopoverQueue;
            routePrice = queue->getTotalDistance();
            if(routePrice >= mostExpensivePrice)
                mostExpensiveId = route->idRoute;
            cout << route->idRoute<<". ORIGEM="<<firstCity<<" DESTINO="<<lastCity
                 << " DISTANCE="<<routePrice << endl;
        }
        route = route->next;
    }
    return mostExpensiveId;
}

RouteList::Route *RouteList::getRoute(int firstCity, int lastCity) {
    Route* route = head;
    while(route!=NULL)
    {
        if(route->firstCity == firstCity && route->lastCity == lastCity)
            return route;
        route = route->next;
    }
    return NULL;
}

RouteList::Route *RouteList::getRoute(RouteList::Route *otherRoute) {
    Route* route = head;
    if(isEmpty())
        return NULL;
    else
        cout << "List was not empty" << endl;
    StopoverQueue *queue;
    StopoverQueue *otherQueue;
    StopoverQueue::Stopover *stopover1, *stopover2;
    while(route != NULL)
    {
        if(route->firstCity != otherRoute->firstCity &&
            route->lastCity != otherRoute->lastCity)
        {
            route = route->next;
            continue;
        }
        queue = route->stopoverQueue;
        otherQueue = otherRoute->stopoverQueue;
        while(!queue->isEmpty() || !otherQueue->isEmpty())
        {
            stopover1 = queue->dequeue();
            stopover2 = otherQueue->dequeue();
            if(stopover1 != NULL && stopover2 != NULL)
            {
                if(stopover1->idCity != stopover2->idCity)
                    return NULL;
                else
                    cout << "Same stops" << endl;
            }
        }
        route = route->next;
    }
    return otherRoute;
}

bool RouteList::contains(RouteList::Route *route) {
    Route* aux = head;
    StopoverQueue *queue;
    StopoverQueue *otherQueue;
    StopoverQueue::Stopover *stopover;
    while(aux != NULL)
    {
        queue = head->stopoverQueue;
        otherQueue = route->stopoverQueue;
        while(!queue->isEmpty() || !otherQueue->isEmpty())
        {
            stopover = queue->dequeue();
            if(stopover != otherQueue->dequeue())
                return false;
        }
        aux = aux->next;
    }
    return true;
}

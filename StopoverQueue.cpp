#include "StopoverQueue.h"

StopoverQueue::Stopover::Stopover(int idCity, double distance) {
    this->idCity = idCity;
    this->distance = distance;
    this->next = NULL;
}

StopoverQueue::StopoverQueue() {
    head = NULL;
    tail = NULL;
}

bool StopoverQueue::isEmpty() {
    return head == NULL;
}

void StopoverQueue::enqueue(Stopover* stopover) {
    if(isEmpty())
        head = tail = stopover;
    else
    {
        tail->next = stopover;
        tail = stopover;
    }
}

StopoverQueue::Stopover *StopoverQueue::dequeue() {
    if(isEmpty())
        return NULL;
    Stopover* aux = head;
    head = head->next;
    return aux;
}

double StopoverQueue::getTotalDistance() {
    double distance = 0;
    Stopover* aux = head;
    while (aux != NULL)
    {
        distance+= aux->distance;
        aux = aux->next;
    }
    return distance;
}

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
    Stopover* stopover = head;
    head = head->next;
    return stopover;
}

double StopoverQueue::getTotalDistance() {
    double distance = 0;
    Stopover* stopover = head;
    while (stopover != NULL)
    {
        distance+= stopover->distance;
        stopover = stopover->next;
    }
    return distance;
}

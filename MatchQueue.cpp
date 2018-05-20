#include <iomanip>
#include "MatchQueue.h"

MatchQueue::Match::Match(int teamHome, int teamAway, tm date) {
    this->teamHome = teamHome;
    this->teamAway = teamAway;
    this->date = date;
    this->next = NULL;
}

MatchQueue::MatchQueue() {
    this->head = NULL;
    this->tail = NULL;
}

bool MatchQueue::isEmpty() {
    return head == NULL;
}

void MatchQueue::enqueue(MatchQueue::Match *match) {
    match->next = NULL;
    if(isEmpty())
        head = tail = match;
    else
    {
        tail->next = match;
        tail = match;
    }
}

MatchQueue::Match *MatchQueue::dequeue() {
    if(isEmpty())
        return NULL;
    Match* Match = head;
    head = head->next;
    return Match;
}

#include <iomanip>
#include "MatchQueue.h"

MatchQueue::Match::Match(int teamHome, int teamAway, string score, tm date) {
    this->teamHome = teamHome;
    this->teamAway = teamAway;
    this->score = score;
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

void MatchQueue::enqueue(MatchQueue::Match *Match) {
    if(isEmpty())
        head = tail = Match;
    else
    {
        tail->next = Match;
        tail = Match;
    }
}

MatchQueue::Match *MatchQueue::dequeue() {
    if(isEmpty())
        return NULL;
    Match* Match = head;
    head = head->next;
    return Match;
}

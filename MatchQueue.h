#ifndef EDA2TRABALHOPRATICO_GAMEQUEUE_H
#define EDA2TRABALHOPRATICO_GAMEQUEUE_H

#include <iostream>

using namespace std;

class MatchQueue {
public:
    struct Match{
        int teamHome;
        int teamAway;
        tm date;
        Match* next;
        Match(int teamHome, int teamAway, tm date);
    };

    MatchQueue();

    bool isEmpty();

    void enqueue(Match* match);

    Match* dequeue();

    Match* head;
private:
    Match* tail;

};


#endif //EDA2TRABALHOPRATICO_GAMEQUEUE_H

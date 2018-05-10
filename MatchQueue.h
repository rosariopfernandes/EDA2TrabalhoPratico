#ifndef EDA2TRABALHOPRATICO_GAMEQUEUE_H
#define EDA2TRABALHOPRATICO_GAMEQUEUE_H

#include <iostream>

using namespace std;

class MatchQueue {
public:
    struct Match{
        int teamHome;
        int teamAway;
        string score;
        tm* date;
        Match* next;
        Match(int teamHome, int teamAway, string score, tm* date);
    };

    MatchQueue();

    bool isEmpty();

    void enqueue(Match* match);

    Match* dequeue();

private:
    Match* head;
    Match* tail;

};


#endif //EDA2TRABALHOPRATICO_GAMEQUEUE_H

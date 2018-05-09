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
        string date;
        Match* next;
        Match(int teamHome, int teamAway, string score, string date);
    };

    MatchQueue();

    bool isEmpty();

    void enqueue(Match* match);

    Match* dequeue();

    void printQueue();

private:
    Match* head;
    Match* tail;
    void printMatch(Match* match);

};


#endif //EDA2TRABALHOPRATICO_GAMEQUEUE_H

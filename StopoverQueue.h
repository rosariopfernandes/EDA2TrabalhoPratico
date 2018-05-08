#ifndef EDA2TRABALHOPRATICO_STOPOVERLIST_H
#define EDA2TRABALHOPRATICO_STOPOVERLIST_H

#include <iostream>

using namespace std;

class StopoverQueue {
public:
    struct Stopover{
        int idCity;
        double distance;
        Stopover* next;
        Stopover(int idCity, double distance);
    };

    StopoverQueue();

    bool isEmpty();

    void enqueue(Stopover* stopover);

    Stopover* dequeue();

private:
    Stopover* head;
    Stopover* tail;
};


#endif //EDA2TRABALHOPRATICO_STOPOVERLIST_H

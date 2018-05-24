#ifndef EDA2TRABALHOPRATICO_ROUNDLIST_H
#define EDA2TRABALHOPRATICO_ROUNDLIST_H

#include <string>
#include <iostream>
#include "MatchQueue.h"

using namespace std;

class RoundList {
public:
    struct Round{
        int id;
        MatchQueue* matchQueue;
        Round* next;
        Round(int id);
    };

    RoundList(int size);

    bool isEmpty();

    void add(int roundId);

    void printCalendar();

    Round* head;
private:
    Round* tail;
};


#endif //EDA2TRABALHOPRATICO_ROUNDLIST_H

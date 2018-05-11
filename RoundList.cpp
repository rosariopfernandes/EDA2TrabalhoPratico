#include "RoundList.h"

bool RoundList::isEmpty() {
    return head == NULL;
}

RoundList::Round::Round(int id) {
    this->id = id;
    this->matchQueue = new MatchQueue;
    this->next = NULL;
}

void RoundList::add(int id) {
    Round* round = new Round(id);
    if(isEmpty())
        head = tail = round;
    else
    {
        tail->next = round;
        tail = round;
    }
}

void RoundList::addMatch(int idRound, MatchQueue::Match *match) {
    Round* round = head;
    while(round != NULL)
    {
        if(round->id == idRound)
        {
            round->matchQueue->enqueue(match);
            break;
        }
        round = round->next;
    }
}

void RoundList::printCalendar() {
    Round* round = head;
    MatchQueue* queue;
    MatchQueue::Match *match;
    while(round != NULL)
    {
        cout << "JORNADA " << round->id << endl;
        queue = round->matchQueue;
        while(!queue->isEmpty())
        {
            match = queue->dequeue();
            cout << match->teamHome << " VS " << match->teamAway << " ";
            string weekDay[] = {"DOMINGO","Segunda","Terça","Quarta","Quinta","Sexta","SABADO"};
            tm date = match->date;
            cout << weekDay[date.tm_wday] <<" ";
            cout << date.tm_mday << "/" << date.tm_mon << endl;
        }
        cout << endl;
        round = round->next;
    }
}

RoundList::RoundList(int size) {
    this->head = NULL;
    this->tail = NULL;
    for(int i=1; i< (size*2-1);i++)
        add(i);
}


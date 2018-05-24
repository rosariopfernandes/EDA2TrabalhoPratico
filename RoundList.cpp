#include "RoundList.h"

bool RoundList::isEmpty() {
    return head == NULL;
}

RoundList::Round::Round(int id) {
    this->id = id;
    this->matchQueue = new MatchQueue;
    this->next = NULL;
}

void RoundList::add(int roundId) {
    Round* round = new Round(roundId);
    if(isEmpty())
        head = tail = round;
    else
    {
        tail->next = round;
        tail = round;
    }
}

void RoundList::printCalendar() {
    string weekDays[] = {"DOMINGO","Segunda","Terça","Quarta","Quinta","Sexta","SABADO"};
    Round* auxRound = head;
    MatchQueue* auxMatchQueue;
    MatchQueue::Match *auxMatch;
    while(auxRound != NULL)
    {
        cout << "JORNADA " << auxRound->id << endl;
        auxMatchQueue = auxRound->matchQueue;
        while(!auxMatchQueue->isEmpty())
        {
            auxMatch = auxMatchQueue->dequeue();
            cout << auxMatch->teamHome << " VS " << auxMatch->teamAway << " ";
            tm date = auxMatch->date;
            cout << weekDays[date.tm_wday] << " ";
            cout << date.tm_mday << "/" << (date.tm_mon+1) << endl;
        }
        cout << endl;
        auxRound = auxRound->next;
    }
}

RoundList::RoundList(int size) {
    this->head = NULL;
    this->tail = NULL;
    for(int i=1; i< size*2-1;i++)
        add(i);
}
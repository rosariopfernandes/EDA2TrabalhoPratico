#include <iostream>
#include "CityList.h"
#include "StreetList.h"
#include "MatchQueue.h"
#include "RoundList.h"
#include "RouteList.h"
#include "BridgeList.h"
#include <ctime>
#include <fstream>

using namespace std;

/*
 *    Se o documento do policia tiver o número 5. E no meio dessas 5 cidades do percurso ele volta para
 *    a cidade do assassinato, essa cidade conta? Sim, conta.
 *    E se o percurso terminar na cidade do assassinato? Não tem problema.
 */

tm* addDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60;
    time_t date_seconds = mktime( date ) + (days * ONE_DAY);
    *date = *localtime( &date_seconds );
    return date;
}

tm* getNextSaturday(tm *gmnow)
{
    while(gmnow->tm_wday != 6)
        addDays(gmnow, 1);
    //cout << gmnow->tm_mday <<"/" << gmnow->tm_mon << endl;
    return gmnow;
}

void generateMatchCalendar(CityList *cityList)
{
    RoundList* roundList = new RoundList(cityList->size());
    MatchQueue::Match* match;
    int currentRound =0;

    int size = cityList->size();
    bool foundExtra;

    time_t now = time(0);
    tm* gmnow = gmtime(&now);
    tm* lastSaturday = getNextSaturday(gmnow);

    for(int i=0; i<size;i++)
    {
        for(int j=i+1; j < size; j++)
        {
            currentRound++;
            if(currentRound <= size-1)
                match = new MatchQueue::Match(cityList->get(i)->id,
                                              cityList->get(j)->id,
                                              "0-0",*lastSaturday);
            else
                match = new MatchQueue::Match(cityList->get(j)->id,
                                              cityList->get(i)->id,
                                              "0-0",*lastSaturday);

            lastSaturday = addDays(lastSaturday, 1);

            roundList->addMatch(currentRound, match);
            foundExtra = false;

            for(int k=0; k < size && !foundExtra; k++)
            {
                if(k == j || k== i)
                    continue;
                for(int l = 0; l < size; l++)
                {
                    if (l == k || l == j || l == i)
                        continue;
                    if(currentRound <= size-1)
                        match = new MatchQueue::Match(cityList->get(k)->id,
                                                      cityList->get(l)->id, "0-0",*lastSaturday);
                    else
                        match = new MatchQueue::Match(cityList->get(l)->id,
                                                      cityList->get(k)->id, "0-0",*lastSaturday);
                    roundList->addMatch(currentRound, match);
                    foundExtra = true;
                    break;
                }
                lastSaturday = addDays(lastSaturday, 6);
            }
        }
    }
    roundList->printCalendar();
}

void listenForInput(CityList *cityList, RouteList *routeList)
{
    cout << "Introduza um comando:";
    string command;
    cin >> command;
    if(command == "SAIR")
    {
        cout << "GAME OVER :(" << endl;
        return;
    } else if( command == "CRIAR_MAPA_DO_JOGO_CIDADE")
    {
        cout << "ID_CIDADE:";
        int idCity;
        cin >> idCity;
        cout << "NOME_CIDADE:";
        string nameCity;
        cin >> nameCity;
        CityList::City *city = new CityList::City(idCity, nameCity);
        cityList->add(city);
        cout << "SUCESSO! CIDADE ADICIONADA {ID: "<<idCity <<
                "; NOME: "<<nameCity<<"}!" << endl;
    }else if(command == "CRIAR_MAPA_DO_JOGO_ESTRADA")
    {
        cout << "ID_CIDADE_ORIGEM:";
        int city1;
        cin >> city1;
        cout << "ID_CIDADE_DESTINO:";
        int city2;
        cin >> city2;

        cout << "DISTANCIA:";
        double distance;
        cin >> distance;

        CityList::City* city = cityList->getById(city1);
        CityList::City* destination = cityList->getById(city2);
        StreetList::Street *street = new StreetList::Street(destination, distance, 0,0,0);
        if(city1 == city2)
            cout << "ERRO! O MAPA_DO_JOGO NÃO PODE CONTER ESTRADAS INTERNAS NUMA"
                    " CIDADE! REVEJA O CONCEITO DE PONTES E CASAS NUMA CIDADE SE"
                    " QUER EXPANDIR UMA CIDADE!" << endl;
        else if(city == NULL)
            cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << city1 << endl;
        else if(destination == NULL)
            cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << city2 << endl;
        else if(cityList->size() %2 != 0)
            cout << "ERRO! O MAPA_DO_JOGO CONTEM UM NUMERO IMPAR DE CIDADES!" << endl;
        else
        {
            if(city->streetList == NULL)
                city->streetList = new StreetList;
            city->streetList->add(street);
            //TODO: Test this
            /*StreetList::Street *street2 = new StreetList::Street(city, distance, 0,0,0);
            destination->streetList->add(street2);*/
            cout << "SUCESSO! ESTRADA ADICIONADA {ORIGEM:"<<city1 <<
                 "; DESTINO:"<<city2 << "; DISTANCIA=" <<distance<<"KM}!" << endl;
        }
    }else if(command == "ACTUALIZAR_MAPA_DO_JOGO_INFO_CRIMINOSA")
    {
        cout << "ID_CIDADE_ORIGEM:";
        int city1;
        cin >> city1;
        cout << "ID_CIDADE_DESTINO:";
        int city2;
        cin >> city2;

        cout << "NUMERO_DE_LADROES_NESTA_ESTRADA:";
        int thieves;
        cin >> thieves;
        cout << "NUMERO_DE_POLICIAS_NESTA_ESTRADA:";
        int police;
        cin >> police;

        CityList::City *origin = cityList->getById(city1);
        if(city1 == city2)
        {
            cout << "ERRO! NÃO EXISTE ESTRADA DE " << city1 << " PARA " << city1 << endl;
        }
        else if(thieves < 0)
        {
            cout << "ERRO! NÃO PODE EXISTIR UM NÚMERO NEGATIVO DE LADRÕES" << endl;
        }
        else if(police < 0)
        {
            cout << "ERRO! NÃO PODE EXISTIR UM NÚMERO NEGATIVO DE POLÍCIAS" << endl;
        }
        else if(origin == NULL)
        {
            cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << city1 << endl;
        }
        else
        {
            origin->streetList->printStreet(city1, city2);
            cout << "ID_ESTRADA:" << endl;
            int streetId;
            cin >> streetId;
            if(origin->streetList->getById(streetId) == NULL)
                cout << "ERRO! NÃO EXISTE NENHUMA ESTRADA COM ID="<<streetId<<"!" << endl;
            else
                origin->streetList->updateStreet(streetId, thieves, police);
        }
    }else if(command == "ACTUALIZAR_MAPA_DO_JOGO_INFO_CASAS")
    {
        cout << "ID_CIDADE:";
        int city;
        cin >> city;
        cout << "NUMERO_DE_CASAS:";
        int housesNr;
        cin >> housesNr;
        if(housesNr < 0)
            cout << "ERRO! UMA CIDADE NÃO PODE CONTER UM NÚMERO NEGATIVO DE CASAS" << endl;
        else if(cityList->isEmpty())
        {
            cout << "ERRO! ADICIONE CIDADES ANTES DE ADICIONAR CASAS!" << endl;
        }else
            cityList->addHouses(city, housesNr);
    }else if(command == "CRIAR_CIDADE_PONTE")
    {
        cout << "ID_CASA_ORIGEM:";
        int house1;
        cin >> house1;
        cout << "ID_CASA_DESTINO:";
        int house2;
        cin >> house2;

        cout << "DISTANCIA:";
        double distance;
        cin >> distance;

        if(house1 == house2){
            cout << "ERRO! NÃO É POSSÍVEL ADICIONAR UMA PONTE ENTRE UMA CASA E ELA MESMA!"<<endl;
        }
        else if(cityList->isEmpty()){
            cout << "ERRO! ADICIONE CIDADES ANTES DE ADICIONAR PONTES!" << endl;
        }else {
            cityList->printList();
            int cityId;
            cout << "ID_CIDADE:";
            cin >> cityId;
            CityList::City *city = cityList->getById(cityId);
            if(city==NULL)
            {
                cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID="<<cityId << endl;
            }
            else
            {
                HouseList::House *firstHouse = city->houseList->getById(house1);
                if(firstHouse == NULL)
                    cout << "ERRO! NÃO EXISTE NENHUMA CASA COM ID="<<house1 << endl;
                else{
                    HouseList::House *secondHouse = city->houseList->getById(house2);
                    if(secondHouse == NULL)
                    {
                        cout << "ERRO! NÃO EXISTE NENHUMA CASA COM ID="<<house1 << endl;
                    } else{
                        BridgeList::Bridge *bridge =
                                new BridgeList::Bridge(distance, secondHouse);
                        if(firstHouse->bridgeList == NULL)
                            firstHouse->bridgeList = new BridgeList;
                        firstHouse->bridgeList->add(bridge);
                        cout << "SUCESSO! PONTE ADICIONADA {ORIGEM:"<<house1 <<
                             "; DESTINO:"<<house2 << "; DISTANCIA=" <<distance<<"}!" << endl;
                    }
                }

            }
        }
    }else if(command == "ADICIONAR_ROTA")
    {
        cout << "ID_CIDADE_ORIGEM:";
        int city1;
        cin >> city1;
        cout << "ID_CIDADE_DESTINO:";
        int city2;
        cin >> city2;

        CityList::City *origin = cityList->getById(city1);
        if(city1 == city2)
        {
            cout << "ERRO! NÃO É POSSÍVEL CRIAR ROTA DE UMA CIDADE PARA ELA MESMA." << endl;
        } else if(origin == NULL)
        {
            cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << city1 << endl;
        } else{
            CityList::City *destination = cityList->getById(city2);
            if(destination == NULL)
            {
                cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << city2 << endl;
            } else{
                //TODO: Mostrar todas cidades que estão entre city1 e city2
                // E pedir para escolher em que cidades quer fazer paragem.
                // Quando ele termina de escolher, verificar se a rota já existe
                // Se não existe, adicionar.
                int stopoverId;
                CityList::City *stopCity;
                do{
                    cout <<"(Introduza -1 quando terminar) PARAGEM_ID:";
                    cin >> stopoverId;
                    if(stopoverId == city1 || stopoverId == city2)
                    {
                        cout << "PARAGEM INVÁLIDA" << endl;
                    }
                }while (stopoverId != -1);
            }
        }

    }else if(command == "GERAR_CALENDARIO_DE_FUTEBOL")
    {
        //generateMatchCalendar(cityList);
        int size = cityList->size();
        if(size %2 != 0)
            cout << "ERRO! O MAPA_DO_JOGO CONTEM UM NUMERO IMPAR DE CIDADES!" << endl;
        else{
            int half = size/2;
            vector<int> cityIds;
            CityList::City *city = cityList->head;
            while(city!=NULL)
            {
                cityIds.push_back(city->id);
                city = city->next;
            }
            /*vector<int> blue, red;
            CityList::City *city = cityList->head;
            int currentIndex = 0;
            while(city!=NULL) //Colorir metade do grafo
            CityList::City *city = cityList->head;
            {
                //if(currentIndex<half)
                if(currentIndex%2==0)
                    blue.push_back(city->id);
                else
                    red.push_back(city->id);
                currentIndex++;
                city = city->next;
            }*/

            time_t now = time(0);
            tm* gmnow = gmtime(&now);
            tm* lastSaturday = getNextSaturday(gmnow);

            int roundSize =cityList->size()-1;
            RoundList* roundList = new RoundList(cityList->size());
            MatchQueue::Match* match;
            int unmutablePosition=0;
            RoundList::Round *currentRound = roundList->head;
            int mutablePos=1, total;
            /*
             * int previousIndex; done
        int aux; done
        for(int i=0;i<array.length-1;i++) done
        {
            for(int l=1;l<array.length;l+=2)//This is where I push matches
                System.out.println(array[l-1]+ ","+array[l]); done
            //Swap left
            for(int index=1;index<array.length-1;index++)
            {
                previousIndex = index-1;
                if(previousIndex==0)
                    previousIndex = array.length-1;
                aux = array[previousIndex];
                array[previousIndex] = array[index];
                array[index] = aux;
            }

        }
             */
            int previousIndex;
            int aux;
            for(int i= 0;i<roundSize;i++)
            {
                for(int j=0; j<roundSize;j+=2)
                {
                    match = new MatchQueue::Match(cityIds[j],
                                                  cityIds[j+1], "0-0",*lastSaturday);
                    currentRound->matchQueue->enqueue(match);
                }
                //Swap left
                for(int index=1;index<roundSize;index++)
                {
                    previousIndex = index-1;
                    if(previousIndex == 0)
                        previousIndex = roundSize;
                    aux = cityIds[previousIndex];
                    cityIds[previousIndex] = cityIds[index];
                    cityIds[index] = aux;
                }
                currentRound = currentRound->next;
            }
            /*while(mutablePos<roundSize && currentRound != NULL)
            {
                for(int i=0;i<half;i++)
                {
                    total=mutablePos+i;
                    if(total>=half)
                        total -= (half);
                    unmutablePosition+=i;
                    match = new MatchQueue::Match(cityIds[unmutablePosition],
                                                  cityIds[total], "0-0",*lastSaturday);
                    currentRound->matchQueue->enqueue(match);
                }
                mutablePos++;
                currentRound = currentRound->next;
            }*/
            roundList->printCalendar();
            //int j =0;
            //First round
            //int currentRound = 0;
            //int j;

            //Blue vs. Red
            /*int lastRound = 1;
            for(int currentRound = 0; currentRound < half; currentRound++)
            {
                for(int i=0;i<half;i++)
                {
                    j = i+(currentRound);
                    if(j >= half)
                        j -= half;
                    match = new MatchQueue::Match(blue[i], red[j], "0-0",*lastSaturday);
                    lastSaturday = addDays(lastSaturday, 1);
                    roundList->addMatch(lastRound, match);

                    //Add the reverse TODO: Check its date
                    reverse = new MatchQueue::Match(red[j], blue[i], "0-0",*lastSaturday);
                    roundList->addMatch(lastRound+size-1, reverse);
                    //cout << "reverseRound = " << lastRound+size-1 <<endl;
                }
                lastRound++;
            }*/

            //Blue vs. Blue
            /*int k = 1;
            int matchesAdded = 0;
            for(int l = half-1;l>0;l--)
            {
                for(int i =0; i<l;i++)
                {
                    matchesAdded++;
                    match = new MatchQueue::Match(blue[i], blue[i+k], "0-0", *lastSaturday);
                    lastSaturday = addDays(lastSaturday, 1);
                    roundList->addMatch(lastRound, match);

                    reverse = new MatchQueue::Match(blue[i+k], blue[i], "0-0",*lastSaturday);
                    roundList->addMatch(lastRound+size-1, reverse);

                    if(matchesAdded%half==0)
                        lastRound++;
                }
                k++;
            }*/

            //Red vs. Red
            /*k = 1;
            for(int l = half-1;l>0;l--)
            {
                for(int i =0; i<l;i++)
                {
                    matchesAdded++;

                    match = new MatchQueue::Match(red[i], red[i+k], "0-0", *lastSaturday);
                    lastSaturday = addDays(lastSaturday, 1);
                    roundList->addMatch(lastRound, match);

                    reverse = new MatchQueue::Match(red[i+k], red[i], "0-0",*lastSaturday);
                    roundList->addMatch(lastRound+size-1, reverse);

                    if(matchesAdded%half == 0)
                        lastRound++;
                }
                k++;
            }*/
            //roundList->printCalendar();

        }
    }else if(command == "VIAJAR")
    {
        cout << "ID_CIDADE_EM_QUE_O_JOGADOR_SE_ENCONTRA_ACTUALMENTE:";
        int city1;
        cin >> city1;
        cout << "ID_CIDADE_QUE_O_JOGADOR_DESEJAR_VISITAR:";
        int city2;
        cin >> city2;

        CityList::City *source = cityList->getById(city1);
        CityList::City *destination = cityList->getById(city2);
        if(source == NULL)
        {
            cout << "ERRO! NÃO EXISTE CIDADE COM ID="<< city1 << endl;
        } else if(destination == NULL)
        {
            cout << "ERRO! NÃO EXISTE CIDADE COM ID="<< city2 << endl;
        } else{
            if(routeList->isEmpty() || city1 == city2)
            {
                cout << "ERRO! NÃO EXISTE ROTA DE "<<city1 <<" PARA " << city2 << endl;
            }
            else
            {
                int mostExp = routeList->printListMostExp(city1, city2);

                if(mostExp != -1) {
                    cout << "A ROTA MAIS CARA É " << mostExp << endl;
                    cout << "ID_ROTA:";
                    int routeId;
                    cin >> routeId;

                    RouteList::Route* route = routeList->getById(routeId);
                    if(route != NULL)
                    {
                        StopoverQueue::Stopover *stopover;
                        int lastCity = city1;
                        int totalRefuelCount = 0;
                        int maintenanceCount = 0;
                        cout << "ORIGEM_ROTA="<<city1 <<" DESTINO_ROTA="<<city2<<endl;
                        while(!route->stopoverQueue->isEmpty())
                        {
                            stopover = route->stopoverQueue->dequeue();

                            cout << "ORIGEM:" << lastCity << " DESTINO:" << stopover->idCity;
                            double distance = stopover->distance;
                            cout << "DISTANCIA:"<< distance;

                            int refuelCount = (int)distance / 150;
                            int refuelCost = refuelCount*50000;
                            cout << " ABASTECIMENTO: " << refuelCost;
                            totalRefuelCount+=refuelCount;

                            maintenanceCount = totalRefuelCount/3;
                            int maintenanceCost = maintenanceCount*30000;
                            cout << " MANUTENCAO: " << maintenanceCost << endl;

                            //TODO: Test the file write
                            ofstream os("UltimaRota.txt");
                            os << "ORIGEM:" << lastCity << " DESTINO:" << stopover->idCity
                                << "DISTANCIA:"<< distance << " ABASTECIMENTO: " << refuelCost
                                << " MANUTENCAO: " << maintenanceCost << "\n";
                            os.close();
                        }
                    } else{
                        cout << "ERRO! NÃO EXISTE ROTA DE ID=" << routeId << endl;
                    }
                }
                else
                    cout << "ERRO! NÃO EXISTE ROTA DE "<<city1 <<" PARA "<< city2 << endl;
            }
        }

    }else if(command == "ASSASSINATO_NO_MAPA_MUNDO")
    {
        //TODO: Exercício 9
        int sourceId, destinationId;
        cout << "CIDADE_ASSASSINATO:" ;
        cin >> sourceId;

        CityList::City *city1 = cityList->get(sourceId);
        if(city1 == NULL)
            cout << "NÃO EXISTE CIDADE COM ID="<<sourceId << endl;
        else{
            cout << "CIDADE_DOCUMENTO:";
            cin >> destinationId;
            CityList::City *city2 = cityList->get(sourceId);
            if(city2 == NULL)
                cout << "NÃO EXISTE CIDADE COM ID=" << destinationId << endl;
            else{
                cityList->executeDijkstra(sourceId);
            }
        }

    }else
    {
        cout << "ERRO! COMANDO INVÁLIDO!" << endl;
    }
    listenForInput(cityList, routeList);
}

int main(){
    CityList* cityList = new CityList;
    RouteList* routeList = new RouteList;

    string name = "Rosário Fernandes";
    cout << "OLÁ " << name <<  "!" << endl;
    cout << "BEM-VINDO AO EDA2JOGO :)" << endl;

    listenForInput(cityList, routeList);

    return 0;
}
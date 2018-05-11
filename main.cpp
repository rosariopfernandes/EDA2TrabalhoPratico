#include <iostream>
#include "CityList.h"
#include "StreetList.h"
#include "MatchQueue.h"
#include "RoundList.h"
#include <ctime>

using namespace std;

/*
 * TODO: Perguntar ao docente
 * 1. Para adicionar pontes entre cidades, o jogador tem de dizer em que cidade quer adicionar a ponte?
 *    Ou devo mostrar uma lista de cidades para ele escolher?
 * 2. Na adição de rota, pede-se ao jogador para introduzir a distancia de cada paragem.
 *    E se a distancia não estiver correcta?
 * 3. Na hora de escrever detalhes dos gastos do avião, é preciso indicar a paragem onde ele abasteceu?
 * 4. Podemos usar o algoritmo de Dijkstra que o docente deu?
 * 5. Se o documento do policia tiver o número 5. E no meio dessas 5 cidades do percurso ele volta para
 *    a cidade do assassinato, essa cidade conta?
 *    E se o percurso terminar na cidade do assassinato?
 */

void welcomePlayer(string name)
{
    cout << "Olá " << name <<  "!" << endl;
    cout << "Bem-vindo ao EDA2JOGO :)" << endl;
}

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
    cout << gmnow->tm_mday <<"/" << gmnow->tm_mon << endl;
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

void listenForInput(CityList *cityList)
{
    string command = "";
    cin >> command;
    if(command == "SAIR")
    {
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
        cout << "ID_CIDADE_ORIGEM:";
        int city;
        cin >> city;
        cout << "NUMERO_DE_CASAS:";
        int housesNr;
        cin >> housesNr;
        if(housesNr < 0)
            cout << "ERRO! UMA CIDADE NÃO PODE CONTER UM NÚMERO NEGATIVO DE CASAS" << endl;
        else
            cityList->addHouses(city, housesNr);
    }else if(command == "CRIAR_CIDADE_PONTE") //CRIAR_CIDADE_PONTE CASA_ORIGEM CASA_DESTINO DISTANCIA
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

        //TODO: mostrar lista de cidades para utilizador escolher em que cidade quer adicionar casa

        /*CityList::City* city = cityList->getById(house1);
        CityList::City* destination = cityList->getById(house2);
        StreetList::Street *street = new StreetList::Street(destination, distance, 0,0,0);
        if(house1 == house2)
            cout << "ERRO! O MAPA_DO_JOGO NÃO PODE CONTER ESTRADAS INTERNAS NUMA"
                    " CIDADE! REVEJA O CONCEITO DE PONTES E CASAS NUMA CIDADE SE"
                    " QUER EXPANDIR UMA CIDADE!" << endl;
        else if(city == NULL)
            cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << house1 << endl;
        else if(destination == NULL)
            cout << "ERRO! NÃO EXISTE NENHUMA CIDADE COM ID=" << house2 << endl;
        else if(cityList->size() %2 != 0)
            cout << "ERRO! O MAPA_DO_JOGO CONTEM UM NUMERO IMPAR DE CIDADES!" << endl;
        else
        {
            city->streetList = new StreetList;
            city->streetList->add(street);
            cout << "SUCESSO! ESTRADA ADICIONADA {ORIGEM:"<<house1 <<
                 "; DESTINO:"<<house2 << "; DISTANCIA=" <<distance<<"KM}!" << endl;
        }*/
    }else if(command == "ADICIONAR_ROTA")
    {

    }else if(command == "GERAR_CALENDARIO_DE_FUTEBOL")
    {
        generateMatchCalendar(cityList);
    }else if(command == "VIAJAR")
    {

    }else if(command == "POLICIA_ENCONTRAR_POLICIAS") //Não necessário
    {

    }else if(command == "LADRAO_EVITAR_POLICIAS") //Não necessário
    {

    }else
    {
        cout << "ERRO! COMANDO INVÁLIDO!" << endl;
    }
    listenForInput(cityList);
}

int main(){
    CityList* cityList = new CityList;

    welcomePlayer("Rosário Fernandes");

    listenForInput(cityList);

    return 0;
}
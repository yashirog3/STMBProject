#ifndef EVENTREPOSITORY_H_
#define EVENTREPOSITORY_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "Event/event.h"


class EventRepository{

typedef std::vector<Event *> Events;
typedef std::pair<int, Events *> Accounts;
typedef std::vector<Accounts *> AccountEvents;
typedef std::pair<int, AccountEvents *> ClientAccounts;
typedef std::vector<ClientAccounts *> Repository;
Repository AllClients;

public:

ClientAccounts * GetClientAccounts(int ClientId)
{
    for(Repository::const_iterator it = AllClients.begin(); it != AllClients.end(); ++it)
    {    
        if(std::get<0>(**it) == ClientId)
        {
            return new ClientAccounts(**it);
        }
    }
    return NULL;
}

Accounts * GetAccountEvents(int ClientId, int AccountId)
{
    ClientAccounts * aux = GetClientAccounts(ClientId);
    if(aux != NULL)
    {
        for(AccountEvents::const_iterator it = std::get<1>(*aux)->begin(); it != std::get<1>(*aux)->end(); ++it)
        {
            if(std::get<0>(**it) == AccountId)
            {
                return new std::pair<int, Events *>(**it);
            }
        }
    }

    return NULL;
}


void AddEvents(Events * ac, Events * ev)
{

    for(Events::const_iterator it = ev->begin(); it != ev->end(); ++it)
    {
        Event * aux = *it;
        ac->push_back(aux);
    }    
}

void Persist(int IdClient, int IdAccount, Events * ev)
{
    ClientAccounts * Caux = GetClientAccounts(IdClient);
    if(Caux != NULL)
    { 
        Accounts * Aaux = GetAccountEvents(IdClient, IdAccount); 
        if(Aaux != NULL) //Account Exists
        { 
            AddEvents(std::get<1>(*Aaux), ev);                    
        }
        else//Account Doesn't Exists, but Client have anothers accounts
        {            
            Events * Eaux = new Events();
            AddEvents(Eaux, ev);
            std::get<1>(*Caux)->push_back(new Accounts(IdAccount, Eaux));            
        }
    }
    else//Account Doesn't Exists and Client have not accounts
    {         
            Events * Eaux = new Events();  
            AddEvents(Eaux, ev);     
            Accounts * Aaux = new Accounts(IdAccount, Eaux); 
            AccountEvents * Aevn = new AccountEvents();
            Aevn->push_back(Aaux);
            Caux = new ClientAccounts(IdClient, Aevn);
            AllClients.push_back(Caux);
        }
    }
};

#endif

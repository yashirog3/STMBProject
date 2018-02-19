#ifndef EVENTREPOSITORY_H_
#define EVENTREPOSITORY_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "../Event/event.h"
#include "idaoaccount.h"
#include "userdefs.h"

static unsigned int seed = 0;

class EventRepository : public IDaoAccount
{

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

    bool CheckVersion(int ClientId, int AccountId, int NewVersion)
    {
        Accounts * Aux = GetAccountEvents(ClientId, AccountId);
        if(Aux != NULL)
        {
            for(Events::const_iterator it = std::get<1>(*Aux)->begin(); it != std::get<1>(*Aux)->end(); ++it)
            {
                if((*it)->Version == NewVersion)
                    return true;
            }

            return false;
        }

        return true;
    }

    int PersistAccount(int ClientId)
    {

        ClientAccounts * Aaux = GetClientAccounts(ClientId);
        if(Aaux != NULL)
        {                
            Events * ev = new Events();
            std::get<1>(*Aaux)->push_back(new Accounts(++seed, ev));
            return seed;

        }else{

            Events * ev = new Events();
            Aaux = new ClientAccounts(ClientId , new AccountEvents()); 
            std::get<1>(*Aaux)->push_back(new Accounts(++seed, ev));
            AllClients.push_back(Aaux);
            return seed;
        }

        return 0;
      
    };

    void Persist(int ClientId, int AccountId, Events * ev, int NewVersion)
    { 
        try
        {
            Accounts * Aaux = GetAccountEvents(ClientId, AccountId); 
            if(Aaux != NULL) //Account Exists
            { 
                if(CheckVersion(ClientId, AccountId, NewVersion)) //If has new events after selected this account
                {        

                    throw collide;                     
                }

                for(Events::const_iterator it = ev->begin(); it != ev->end(); ++it)
                {
                    Event * aux = *it;
                    std::get<1>(*Aaux)->push_back(aux);
                }                      
            }
        }
        catch(CollideDetection &e)
        {
            std::cout << e.what() << std::endl;
            throw collide;
        }
    }

};

#endif

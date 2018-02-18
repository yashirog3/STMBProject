#ifndef QUERY_H_
#define QUERY_H_
#include "Model/account.h"
#include "Dao/idaoaccount.h"
#include <iomanip>
#include <iostream>

class Query{

    typedef std::vector<Event *> Events;
    typedef std::pair<int, Events *> Accounts;
    typedef std::vector<Accounts *> AccountEvents;
    typedef std::pair<int, AccountEvents *> ClientAccounts;    
    IDaoAccount * DaoAc;

public:
    Query(IDaoAccount * DaoAc) : DaoAc(DaoAc) {};

    void Summary(Events * AcEvents)
    {
        double Value = 0;
        for(Events::const_iterator it = AcEvents->begin(); it != AcEvents->end(); ++it)
        {
            switch((*it)->EventType)
            {                
                case DEPOSITE:
                    Value += (*it)->Value;
                    break;
                case WITHDRAW:
                    Value -= (*it)->Value;
                    break;
                default:
                    break;
            }
            
            std::cout << (*it) << std::endl;
        }
            std::locale MyLoc("");
            std::cout.imbue(MyLoc);
            std::cout << std::endl << "Balance: R$ " << Value << std::endl << std::endl;
    }


    void SummaryAccount(int ClientId, int AccountId)
    {
        Accounts * Aux = DaoAc->GetAccountEvents(ClientId, AccountId);
        if(Aux != NULL)
        {            
           std::cout << "Account Id: " << std::get<0>(*Aux) << std::endl << std::endl; 
           Summary(std::get<1>(*Aux));
        }
    }

    void SummaryAllAccounts(int ClientId)
    {
        ClientAccounts * Aux = DaoAc->GetClientAccounts(ClientId);
        if(Aux != NULL)
        {          
            std::cout << "Client Id: " << ClientId << std::endl;
            for(AccountEvents::const_iterator it = std::get<1>(*Aux)->begin(); it != std::get<1>(*Aux)->end(); ++it)
            {
               std::cout << "Account Id: " << std::get<0>(**it) << std::endl << std::endl; 
               Summary(std::get<1>(**it));
            }        
        }          
    }


};

#endif // QUERY_H_

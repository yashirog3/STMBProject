#ifndef QUERY_H_
#define QUERY_H_
#include "Model/account.h"
#include "eventrepository.h"
#include <iomanip>

class Query{

    typedef std::vector<Event *> Events;
    typedef std::pair<int, Events *> Accounts;
    typedef std::vector<Accounts *> AccountEvents;
    typedef std::pair<int, AccountEvents *> ClientAccounts;    

public:



void SummaryAllAccounts(int IdClient, EventRepository * Repository)
{
    ClientAccounts * Caux = Repository->GetClientAccounts(IdClient);
    if(Caux != NULL)
    { 
        std::cout << "Client: " << IdClient << std::endl;
        for(AccountEvents::const_iterator it = std::get<1>(*Caux)->begin(); it != std::get<1>(*Caux)->end(); ++it)
        {
            Accounts * ac = Repository->GetAccountEvents(IdClient, std::get<0>(**it));
            if(ac != NULL)
            {
                double Value = 0;
                for(Events::const_iterator jt = std::get<1>(*ac)->begin(); jt != std::get<1>(*ac)->end(); ++jt)
                {
                    
                    switch((*jt)->EventType)
                    {                    
                        case WITHDRAW:
                            Value -= (*jt)->Value;
                        break;

                        case DEPOSITE:
                            Value += (*jt)->Value;
                        break;

                        default:
                        break;
                    };
                }

                    std::locale mylocale("");
                    std::cout << "Account: " << std::get<0>(**it) << " - ";
                    std::cout.imbue(mylocale);
                    std::cout << "Balance: R$ " << std::fixed << std::showpoint << std::setprecision(2) << std::setfill('0') << Value << std::endl;    
            }            
        }
    }
}

void ShowEvents(int IdClient, int AccountId, EventRepository * Repository)
{
    Accounts * Caux = Repository->GetAccountEvents(IdClient, AccountId);
    if(Caux != NULL)
    { 
        for(Events::const_iterator jt = std::get<1>(*Caux)->begin(); jt != std::get<1>(*Caux)->end(); ++jt)
        {
            std::cout << (*jt) << std::endl;
        }
    };

}


void SummaryAccount(int IdClient, int AccountId, EventRepository * Repository)
{
    Accounts * Caux = Repository->GetAccountEvents(IdClient, AccountId);
    if(Caux != NULL)
    { 
            double Value = 0;
                std::locale mylocale("");
                std::cout << "Client: " << IdClient << std::endl;
                std::cout << "Account: " << std::get<0>(*Caux) << std::endl;
                std::cout.imbue(mylocale);
                std::cout << "Transactions: " << std::endl << std::endl;
            for(Events::const_iterator jt = std::get<1>(*Caux)->begin(); jt != std::get<1>(*Caux)->end(); ++jt)
            {        
                std::cout << *jt << std::endl;                
                switch((*jt)->EventType)
                {                    
                    case WITHDRAW:
                        Value -= (*jt)->Value;
                    break;

                    case DEPOSITE:
                        Value += (*jt)->Value;
                    break;

                    default:
                    break;
                };
            }


                std::cout << std::endl << "Balance: R$ " << std::fixed << std::showpoint << std::setprecision(2) << std::setfill('0') << Value << std::endl << std::endl;

                    
        }            

    }

};


#endif // QUERY_H_

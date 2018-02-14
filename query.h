#ifndef QUERY_H_
#define QUERY_H_
#include "Model/account.h"
#include "eventrepository.h"
#include "Dao/daoaccount.h"
#include <iomanip>

class Query{

    typedef std::vector<Event *> Events;
    typedef std::pair<int, Events *> Accounts;
    typedef std::vector<Accounts *> AccountEvents;
    typedef std::pair<int, AccountEvents *> ClientAccounts;    

public:


void SummaryAllAccounts(int ClientId, DaoAccount * DaoAc)
{
  /*  ClientAccounts * Caux = Repository->GetClientAccounts(ClientId);

    if(Caux != NULL)
    { 
        std::cout << "Client: " << ClientId << std::endl;
        for(AccountEvents::const_iterator it = std::get<1>(*Caux)->begin(); it != std::get<1>(*Caux)->end(); ++it)
        {
            Accounts * ac = Repository->GetAccountEvents(ClientId, std::get<0>(**it));
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
    //                    ShowEvents(Caux);
            }            
        }
    }
*/
}


    void SummaryAccount(int ClientId, int AccountId, DaoAccount * DaoAc)
    {

        pqxx::result res = DaoAc->GetAccountEvents(AccountId);
            
        if(res.size() > 0)
        {
            
           double Value = 0;
           std::vector<Event *> MyEvents;
            for(int i = 0; i < res.size(); i++)
            {
                switch(res[i][1].as<int>())
                {
                    case CREATE:
                        MyEvents.push_back(new CreateAccountEvent(res[i][0].as<int>()));                        
                    break;
                    case DEPOSITE:
                        MyEvents.push_back(new DepositeAccountEvent(res[i][2].as<double>(), res[i][0].as<int>()));
                        Value += res[i][2].as<double>();
                    break;
                    case WITHDRAW:
                        MyEvents.push_back(new WithdrawAccountEvent(res[i][2].as<double>(), res[i][0].as<int>()));  
                        Value -= res[i][2].as<double>();     
                    break;
                }                
            }        


            std::locale mylocale("");
            std::cout << "Client: " << ClientId << std::endl;
            std::cout << "Account: " << AccountId << std::endl;
            std::cout.imbue(mylocale);
            std::cout << "Balance: R$ " << std::fixed << std::showpoint << std::setprecision(2) << std::setfill('0') << Value << std::endl << std::endl;

            std::cout << "Account Events:" << std::endl << std::endl;           
            for(Events::const_iterator jt = (MyEvents).begin(); jt != (MyEvents).end(); ++jt)
            {
                std::cout << (*jt) << std::endl;
            } 
        }
    }
};


#endif // QUERY_H_

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Handler/eventhandler.h"
#include "../eventrepository.h"
#include "../Dao/daoaccount.h"

class Account : public EventHandler<DepositeAccountEvent>::Listener, public EventHandler<WithdrawAccountEvent>::Listener,
public EventHandler<CreateAccountEvent>::Listener, public EventHandler<PersistAccountEvent>::Listener, public EventHandler<RemoveAccountEvent>::Listener
{

    private:

        int AccountId;
        double AccountMoney;
        int OldVersion;
        int NewVersion;        

        EventRepository * Repository;

        std::vector<Event *> AllEvents; 
        
        void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender)
        {                        
            
            AcEvent->Version = NewVersion++;
            if(AcEvent->NewEvent){           
                //Here i Create an Account and set AccountId
                pqxx::connection conn("user = stoneuser password = stonepassword host = localhost dbname = stonedb");
                pqxx::work wk(conn);
                DaoAccount dac(conn, wk);
                AccountId = dac.InsertAccountEvent(AcEvent->IdClient);                   
                AcEvent->NewEvent = false;     
                AllEvents.push_back(AcEvent);
            }
        }

        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {
            AccountMoney += AcEvent->Value;
            AcEvent->Version = NewVersion++;
            if(AcEvent->NewEvent){           
                AcEvent->NewEvent = false;     
                AllEvents.push_back(AcEvent);
            }
        }

        void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender)
        {
            if(AccountMoney - AcEvent->Value < 0)
            {
                std::cout << " Account Balance is lower than Withdraw value " << std::endl;
                return;
            }
            
            AccountMoney -= AcEvent->Value;
            AcEvent->Version = NewVersion++;
            if(AcEvent->NewEvent){           
                AcEvent->NewEvent = false;     
                AllEvents.push_back(AcEvent);
            }

        }

        void Update(RemoveAccountEvent * AcEvent, EventHandler<RemoveAccountEvent> & Sender)
        {

        }
        void Update(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender)
        {
            Repository->Persist(AccountId, &AllEvents);
            Repository->Summary(AccountId);
        }        
        
    public:

        Account(EventRepository * Repository) : Repository(Repository), AccountId(0), AccountMoney(0), OldVersion(0), NewVersion(0) {};
        Account(int AccountId,  EventRepository * Repository) :  Repository(Repository), AccountId(AccountId), AccountMoney(0), OldVersion(0), NewVersion(0) {};
};


#endif              

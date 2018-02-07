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
public EventHandler<CreateAccountEvent>::Listener, public EventHandler<PersistAccountEvent>::Listener
{

    private:

        int AccountId;
        double AccountMoney;
        int OldVersion;
        int NewVersion;        

        std::vector<std::pair<int, Event *> > AllEvents; 
        EventRepository * Repository;
        
        void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender)
        {
            if(AcEvent->NewEvent)
            {

                AcEvent->Version = ++NewVersion;
                Repository->AllEvents.push_back(std::make_pair(AccountId, AcEvent));
            }
        }

        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {
            AccountMoney += AcEvent->Value;
            if(AcEvent->NewEvent)
            {              
                AcEvent->Version = ++NewVersion;
                Repository->AllEvents.push_back(std::make_pair(AccountId, AcEvent));
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
            if(AcEvent->NewEvent)
            {
                    AcEvent->Version = ++NewVersion;
                    Repository->AllEvents.push_back(std::make_pair(AccountId, AcEvent));
            }            

        }

        void Update(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender)
        {
            for(std::vector<std::pair<int, Event *> >::const_iterator it = Repository->AllEvents.begin(); it != Repository->AllEvents.end(); ++it)
            {
                    if(std::get<0>(*it) == AccountId && std::get<1>(*it)->NewEvent)
                    {
                        pqxx::connection conn("user = stoneuser password = stonepassword host = localhost dbname = stonedb");
                        pqxx::work wk(conn);
                        DaoAccount Dao(conn, wk);
                        if(Dao.InsertAccountEvent(new DtoAccountEvent(AccountId, std::get<1>(*it)->Version,std::get<1>(*it)->EventType, std::get<1>(*it)->Value))) std::cout << std::get<0>(*it) << std::endl;
                        
                    }
            }
        }        
        
    public:

        Account(EventRepository * Repository) : Repository(Repository), AccountId(0), AccountMoney(0), OldVersion(0), NewVersion(0) {};
        Account(int AccountId, EventRepository * Repository) : Repository(Repository), AccountId(AccountId), AccountMoney(0), OldVersion(0), NewVersion(0) {};
};


#endif              

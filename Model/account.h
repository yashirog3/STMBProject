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
#include "../Dto/dtoaccountevent.h"
#include "../eventrepository.h"

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
                AcEvent->NewEvent = false;
                Repository->AllEvents.push_back(std::make_pair(AccountId, AcEvent));
            }
        }

        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {
            AccountMoney += AcEvent->Value;
            if(AcEvent->NewEvent)
            {              
                AcEvent->Version = ++NewVersion;
                AcEvent->NewEvent = false;
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
                    if(std::get<1>(*it)->NewEvent)
                    {
                        std::get<1>(*it)->NewEvent = false;
                    }
            }
        }        
        
    public:

        Account(EventRepository * Repository) : Repository(Repository), AccountId(0), AccountMoney(0), OldVersion(0), NewVersion(0) {};
        Account(int AccountId, EventRepository * Repository) : Repository(Repository), AccountId(AccountId), AccountMoney(0), OldVersion(0), NewVersion(0) {};
};


#endif              

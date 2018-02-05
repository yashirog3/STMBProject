#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "../Event/accountevent.h"
#include "../Event/undolastevent.h"
#include "../Event/listevent.h"
#include "../Handler/eventhandler.h"
#include "../Dto/dtoaccountevent.h"


class Account : public EventHandler<AccountEvent>::Listener,
                public EventHandler<ListEvent>::Listener{

    private:
        int AccountId;
        double AccountMoney;
        int OldVersion;
        int NewVersion;

        std::vector<std::pair<int, Event * > > AllEvents;
    
        void Update(AccountEvent * AcEvent, EventHandler<AccountEvent> & Sender)
        {  
            if(AcEvent->EventType==DEPOSITE)
            {    
                AccountMoney += AcEvent->Value;               
            }
            else
            {
                AccountMoney -= AcEvent->Value;               
            }          

            AcEvent->Version = ++NewVersion;
            AllEvents.push_back(std::make_pair(AccountId, AcEvent));
         }

        void Update(ListEvent * SvEvent, EventHandler<ListEvent> & Sender){

            for(std::vector<std::pair<int, Event *> >::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it){

                std::cout << std::get<1>(*it) << std::endl;

            }

        }

    public:
        Account() {};
        Account(int AccountId) : AccountId(AccountId), AccountMoney(0), OldVersion(0), NewVersion(0) {};
};


#endif
              //  AllEvents.push_back(std::make_pair(Ac, new AccountEvent(++seed, WITHDRAW, Value)));

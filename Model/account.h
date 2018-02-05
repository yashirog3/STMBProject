#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Event/undolastevent.h"
#include "../Event/listevent.h"
#include "../Handler/eventhandler.h"
#include "../Dto/dtoaccountevent.h"


class Account : public EventHandler<DepositeAccountEvent>::Listener,
                public EventHandler<WithdrawAccountEvent>::Listener,
                public EventHandler<CreateAccountEvent>::Listener,
                public EventHandler<ListEvent>::Listener{

    private:
        int AccountId;
        double AccountMoney;
        int OldVersion;
        int NewVersion;

        std::vector<std::pair<int, Event * > > AllEvents;
    
        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {  
            AccountMoney += AcEvent->Value;               
        }

        void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender)
        {  
            AccountMoney += AcEvent->Value;               
        }

        void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender)
        {  
//            AccountMoney += AcEvent->Value;               
            std::cout << "Account Created" << std::endl;
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

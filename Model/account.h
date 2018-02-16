#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Handler/persistaccounthandler.h"
#include "../Handler/undoaccounthandler.h"
#include "../Handler/eventhandler.h"
#include "../Dao/daoaccount.h"
#include "iaccount.h"

class Account :  public IAccount
{
    private:

        int AccountId = 0;
        int ClientId = 0;
        double AccountMoney = 0;
        int OldVersion = 0;
        int NewVersion = 0;

        IDaoAccount * DaoAc;
        std::vector<Event *> AllEvents;

        //Create an Account;
        void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender)
        {          
            AccountId = DaoAc->PersistAccount(ClientId);
            AcEvent->Version = ++NewVersion;
            if(AcEvent->NewEvent)
            {              
                AllEvents.push_back(AcEvent);
            }                       
        }

        //Deposite on a account
        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {
            AccountMoney += AcEvent->Value;
            AcEvent->Version = ++NewVersion;

            if(AcEvent->NewEvent)
            {              
                AllEvents.push_back(AcEvent);
            }           
        }

        //Withdraw from account
        void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender)
        {
            if(AccountMoney - AcEvent->Value < 0)
            {
                std::cout << " Account Balance is lower than Withdraw value " << std::endl;
                return;
            }
            
            AccountMoney -= AcEvent->Value;
            AcEvent->Version = ++NewVersion;

            if(AcEvent->NewEvent)
            {              
                AllEvents.push_back(AcEvent);
            }           
        }

        //Undo Last Event
        void Update(UndoAccountEvent * AcEvent, EventHandler<UndoAccountEvent> & Sender)
        {
            AllEvents.pop_back();
            NewVersion--;
        }

        //Persiste account on In Memory Repository and Database
        void Update(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender)
        {                                 
            DaoAc->Persist(ClientId, AccountId, &AllEvents, OldVersion);
            AllEvents.clear();
        }

    public:
        
        Account(IDaoAccount * DaoAc) : AccountId(0), DaoAc(DaoAc) {};
        Account(int ClientId, IDaoAccount * DaoAc) : ClientId(ClientId), DaoAc(DaoAc) {};
        ~Account() {};
};


#endif

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>


#include "../Dao/idaoaccount.h"
#include "iaccount.h"

class Account :  public IAccount
{
    private:

        int AccountId;
        int ClientId;
        double AccountMoney = 0;
        int OldVersion = 0;
        int NewVersion = 0;

        std::vector<Event *> AllEvents;

        //Create an Account;
        void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender)
        {          
            if(AcEvent->NewEvent)
            {       
                AcEvent->Version = ++NewVersion;        
                AllEvents.push_back(AcEvent);
            }
            else
            {            
                OldVersion = ++NewVersion;                   
            }                       
        }

        //Deposite on a account
        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {
            AccountMoney += AcEvent->Value;
            if(AcEvent->NewEvent)
            {       
                AcEvent->Version = ++NewVersion;        
                AllEvents.push_back(AcEvent);
            }
            else
            {            
                OldVersion = ++NewVersion;                   
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
            if(AcEvent->NewEvent)
            {       
                AcEvent->Version = ++NewVersion;        
                AllEvents.push_back(AcEvent);
            }
            else
            {            
                OldVersion = ++NewVersion;           
            }          
        }

    public:
        
        Account() {}
        Account(int ClientId, int AccountId) : ClientId(ClientId), AccountId(AccountId) {}

        //Undo Last Event
        void UndoEvent(Event * AcEvent)
        {
            AllEvents.pop_back();
            NewVersion--;
        }

        void PersistAccount(IDaoAccount * DaoAc = NULL)
        {                                 
            DaoAc->Persist(ClientId, AccountId, &AllEvents, NewVersion);
            AllEvents.clear();
        }
        
};


#endif

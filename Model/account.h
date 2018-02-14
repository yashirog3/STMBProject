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
#include "../eventrepository.h"
#include "../Dao/daoaccount.h"

class Account : 
                public EventHandler<DepositeAccountEvent>::Listener, 
                public EventHandler<WithdrawAccountEvent>::Listener,
                public EventHandler<CreateAccountEvent>::Listener, 
                public EventHandler<PersistAccountEvent>::Listener, 
                public EventHandler<UndoAccountEvent>::Listener 
{

    private:

        int AccountId = 0;
        int ClientId = 0;
        double AccountMoney = 0;
        int OldVersion = 0;
        int NewVersion = 0;

        EventRepository * Repository;
        DaoAccount * DaoAc;

        std::vector<Event *> AllEvents;

        //Create an Account;
        void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender)
        {                   
            AccountId = DaoAc->PersistAccount(ClientId);        
            Dispatch(AcEvent); 
        }

        //Deposite on a account
        void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender)
        {
            Dispatch(AcEvent);
        }

        //Withdraw from account
        void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender)
        {
            if(AccountMoney - AcEvent->Value < 0)
            {
                std::cout << " Account Balance is lower than Withdraw value " << std::endl;
                return;
            }

            Dispatch(AcEvent);
        }

        //Undo Last Event
        void Update(UndoAccountEvent * AcEvent, EventHandler<UndoAccountEvent> & Sender){
            AllEvents.pop_back();
            NewVersion--;
        }

        //Persiste account on In Memory Repository and Database
        void Update(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender)
        {                       
            Repository->Persist(ClientId, AccountId, &AllEvents);            
            DaoAc->Persist(AccountId, &AllEvents, OldVersion, NewVersion);
            AllEvents.clear();
        }

        //Dispatch an Event
        void Dispatch(Event * AcEvent, bool NewEvent = true)
        {
            AcEvent->Version = ++NewVersion;            
            if(AcEvent->EventType == DEPOSITE)
                AccountMoney += AcEvent->Value;
            
            if(AcEvent->EventType == WITHDRAW)
                AccountMoney -= AcEvent->Value;

            if(NewEvent)
            {              
                AllEvents.push_back(AcEvent);
            }     
        }

    public:

        Account() : AccountId(0) {};

        Account(int ClientId, EventRepository * Repository, DaoAccount * DaoAc) : ClientId(ClientId),Repository(Repository), DaoAc(DaoAc) {};


        //Re-create an account based on In Memory Repository or Database
        Account(int ClientId, int AccountId,  EventRepository * Repository, DaoAccount * DaoAc) : ClientId(ClientId),Repository(Repository), DaoAc(DaoAc), AccountId(AccountId)
        {
            std::pair<int, std::vector<Event *> *> * MyAccount = Repository->GetAccountEvents(ClientId, AccountId);
            if(MyAccount != NULL)
            {
                for(std::vector<Event *>::const_iterator it = std::get<1>(*MyAccount)->begin(); it != std::get<1>(*MyAccount)->end(); ++it)
                {
                    Dispatch(*it, false);
                }
            }
            else
            {                
                pqxx::result res = DaoAc->GetAccountEvents(AccountId);
                if(res.size() > 0)
                {    
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
                            break;
                            case WITHDRAW:
                                MyEvents.push_back(new WithdrawAccountEvent(res[i][2].as<double>(), res[i][0].as<int>()));       
                            break;
                        }

                        OldVersion = NewVersion = res[i][0].as<int>();                
                    }  

                    Repository->Persist(ClientId, AccountId, &MyEvents);     
                }                        
             };  
        };
};


#endif

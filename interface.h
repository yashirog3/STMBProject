#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <iostream>
#include "Model/account.h"
#include "command.h"
#include "query.h"

class Interface
{

        typedef std::vector<Event *> Events;
        typedef std::pair<int, Events *> Accounts;
        typedef std::vector<Accounts *> AccountEvents;
        typedef std::pair<int, AccountEvents *> ClientAccounts;

        int ClientId = 0;
        IDaoAccount * DaoAc;
        Account * Ac = NULL;
        Command * Commands = NULL;
        Query Queries = Query(DaoAc);

    public:        

        Interface(int ClientId, IDaoAccount * DaoAc) : ClientId(ClientId),  DaoAc(DaoAc) {}

        //Client can create new clients
        void CreateAccount()
        {
            try
            {                
                int AccountId = DaoAc->PersistAccount(ClientId);
                Ac = new Account(ClientId, AccountId);
                Commands = new Command(*Ac);
                Commands->DoCreate(new CreateAccountEvent());

            //Here we can send a mail
            }
            catch(std::exception &e)
            {
                throw;
            }
        }

        //Client Can retrieve an persisted account
        void GetAccount(int AccountId)
        {            
            try
            {
                Accounts * MyAccount = DaoAc->GetAccountEvents(ClientId, AccountId);
                if(MyAccount != NULL){
                    Ac = new Account(ClientId, AccountId);
                    Commands = new Command(*Ac);

                    for(Events::const_iterator it = std::get<1>(*MyAccount)->begin(); it != std::get<1>(*MyAccount)->end(); ++it)
                    {       
                        switch((*it)->EventType)
                        {
                            case CREATE:
                                Commands->DoCreate(new CreateAccountEvent((*it)->Version, false));
                            break;
                            case DEPOSITE:
                                Commands->DoDeposite(new DepositeAccountEvent((*it)->Value,(*it)->Version, false));
                            break;
                            case WITHDRAW:
                                Commands->DoWithdraw(new WithdrawAccountEvent((*it)->Value,(*it)->Version, false));
                            break;

                            default:
                            break;
                        }                    
                    }
                }
            }
            catch(std::exception &e)
            {
                return;
            }
        }

        //Client Can Deposite in an account
        void Deposite(double Value)
        {
            if(Commands != NULL)
                Commands->DoDeposite(new DepositeAccountEvent(Value));  
            else
                throw;
        }

        //Client can Withdraw from an account
        void Withdraw(double Value)
        {                
            if(Commands != NULL)
                Commands->DoWithdraw(new WithdrawAccountEvent(Value));
            else
                throw;    
        }

        //Client Will Persist All Events of an account
        void Save()
        {
            if(Commands != NULL)
                Commands->DoPersist(DaoAc);
            else
                throw;
        }

        //Client Can Undo Last Event
        void Undo()
        {          
            if(Commands != NULL)  
                Commands->DoUndo();  
            else
                throw;

        }

        //Summary of an especified account
        void SummaryAccount(int AccountId)
        {
            Queries.SummaryAccount(ClientId, AccountId);
        }

        //Summary All Client Accounts
        void SummaryAllAccounts()
        {
            Queries.SummaryAllAccounts(ClientId);
        }
};

#endif // CLIENT_H_

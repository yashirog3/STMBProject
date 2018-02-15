#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <iostream>
#include "Model/account.h"
#include "command.h"
#include "query.h"
#include "Dao/idaoaccount.h"

class Interface
{

        typedef std::vector<Event *> Events;
        typedef std::pair<int, Events *> Accounts;
        typedef std::vector<Accounts *> AccountEvents;
        typedef std::pair<int, AccountEvents *> ClientAccounts;


        int ClientId;
        IDaoAccount * DaoAc;
        Query Queries = Query(DaoAc);
        Account Ac = Account(ClientId, DaoAc);
        Command Commands = Command(Ac);

    public:        

        Interface(int ClientId, IDaoAccount * DaoAc) : ClientId(ClientId), DaoAc(DaoAc) {};

        //Client can create new clients
        void CreateAccount()
        {
            try
            {                
                Commands.DoCreate(new CreateAccountEvent());

            //Here we can send a mail
            }
            catch(std::exception &e)
            {
                throw;
            }
        };

        //Client Can retrieve an persisted account
        void GetAccount(int AccountId)
        {            
            try
            {
                Accounts * MyAccount = DaoAc->GetAccountEvents(ClientId, AccountId);
                for(Events::const_iterator it = std::get<1>(*MyAccount)->begin(); it != std::get<1>(*MyAccount)->end(); ++it)
                {       
                    switch((*it)->EventType)
                    {
                        case CREATE:
                            Commands.DoCreate(new CreateAccountEvent((*it)->Version, (*it)->NewEvent));
                        break;
                        case DEPOSITE:
                            Commands.DoDeposite(new DepositeAccountEvent((*it)->Value,(*it)->Version, (*it)->NewEvent));
                        break;
                        case WITHDRAW:
                            Commands.DoWithdraw(new WithdrawAccountEvent((*it)->Value,(*it)->Version, (*it)->NewEvent));
                        break;

                        default:
                        break;
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
                Commands.DoDeposite(new DepositeAccountEvent(Value));
        };

        //Client can Withdraw from an account
        void Withdraw(double Value)
        {                
                Commands.DoWithdraw(new WithdrawAccountEvent(Value));    
        };

        //Client Will Persist All Events of an account
        void Save()
        {
                Commands.DoPersist();
        };

        //Client Can Undo Last Event
        void Undo()
        {
                Commands.DoUndo();  

        };

        //Summary of an especified account
        void SummaryAccount(int AccountId)
        {
            Queries.SummaryAccount(ClientId, AccountId);
        };

        //Summary All Client Accounts
        void SummaryAllAccounts()
        {
            Queries.SummaryAllAccounts(ClientId);
        };


};

#endif // CLIENT_H_

#ifndef CLIENT_H_
#define CLIENT_H_
#include "account.h"
#include "../command.h"
#include "../query.h"
#include "../Dao/daoaccount.h"
#include <iostream>

class Client
{
        int ClientId;
        std::shared_ptr<Account> Ac;
        Command Commands;
        Query Queries;

    public:

        Client(int ClientId) : ClientId(ClientId) {};

        //Client can create new clients
        void CreateAccount(EventRepository * Repository, DaoAccount * DaoAc)
        {
            try
            {
                Account MyAc(ClientId, Repository, DaoAc);
                Ac = std::make_shared<Account>(MyAc);  
                Commands.DoCreate(Ac);

            //Here we can send a mail
           }
            catch(std::exception &e)
            {
                return;
            }
        };

        //Client Can retrieve an persisted account
        void GetAccount(int AccountId, EventRepository * Repository, DaoAccount * DaoAc)
        {            
            try
            {
                Account MyAc(ClientId, AccountId, Repository, DaoAc);
                Ac = std::make_shared<Account>(MyAc);
            }
            catch(std::exception &e)
            {
                return;
            }
        }

        //Client Can Deposite in an account
        void Deposite(double Value)
        {
            if(Ac != NULL)
                Commands.DoDeposite(Ac, Value);
        };

        //Client can Withdraw from an account
        void WithDraw(double Value)
        {                
            if(Ac != NULL)
                Commands.DoWithdraw(Ac, Value);        
        };

        //Client Will Persist All Events of an account
        void Save()
        {
            if(Ac != NULL)
                Commands.DoPersist(Ac);
        };

        //Client Can Undo Last Event
        void Undo()
        {
            if(Ac != NULL)
                Commands.DoUndo(Ac);  

        };

        //Summary of an especified account
        void SummaryAccount(int AccountId, DaoAccount * DaoAc)
        {
            Queries.SummaryAccount(ClientId, AccountId, DaoAc);
        };

        //Summary All Client Accounts
        void SummaryAllAccounts(DaoAccount * DaoAc )
        {
            Queries.SummaryAllAccounts(ClientId, DaoAc);
        };


};

#endif // CLIENT_H_

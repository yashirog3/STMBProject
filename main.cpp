#include <iostream>
#include "command.h"
#include "query.h"
#include "Dao/daoaccount.h"

using namespace std;

Command Commands;
Query Queries;

EventRepository Repository;

int main()
{

    std::shared_ptr<Account> Ac(new Account(1, 1, &Repository));
    std::shared_ptr<Account> Ad(new Account(0, 1, &Repository));
    std::shared_ptr<Account> Ae(new Account(2, 1, &Repository));
    std::shared_ptr<Account> Af(new Account(3, 0, &Repository));
    std::shared_ptr<Account> Ag(new Account(4, 1, &Repository));
    std::shared_ptr<Account> Ah(new Account(5, 1, &Repository));
    std::shared_ptr<Account> Ai(new Account(6, 1, &Repository));


// A Client can create one or more accounts - Ok
    Commands.DoCreate(Ac, new CreateAccountEvent());
    Commands.DoCreate(Ad, new CreateAccountEvent());
    Commands.DoCreate(Ae, new CreateAccountEvent());
    Commands.DoCreate(Af, new CreateAccountEvent());
    Commands.DoCreate(Ag, new CreateAccountEvent());
    Commands.DoCreate(Ah, new CreateAccountEvent());
    Commands.DoCreate(Ai, new CreateAccountEvent());

//One account can deposite or withdraw - Ok
    Commands.DoDeposite(Ac, new DepositeAccountEvent(1000.0));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(100.0));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(1000.50));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(500.30));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(1500.20));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(2500.20));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(3500));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(4500));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(5500));

    Commands.DoPersist(Ac, new PersistAccountEvent());
    Commands.DoPersist(Ad, new PersistAccountEvent());
    Commands.DoPersist(Ae, new PersistAccountEvent());
    Commands.DoPersist(Af, new PersistAccountEvent());
    Commands.DoPersist(Ag, new PersistAccountEvent());
    Commands.DoPersist(Ah, new PersistAccountEvent());
    Commands.DoPersist(Ai, new PersistAccountEvent());

//A Client can 
    Queries.SummaryAccount(1, 1 , &Repository);
    Queries.SummaryAllAccounts(1, &Repository);


  Queries.ShowEvents(1, 1 , &Repository);

  
    return 0;
}





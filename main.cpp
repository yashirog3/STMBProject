#include <iostream>
#include "command.h"
#include "query.h"
#include "Dao/daoaccount.h"
#include <pqxx/pqxx>

using namespace std;

Command Commands;
Query Queries;
EventRepository Repository;

int main()
{

pqxx::connection conn("user=stoneuser"" password=stonepassword"" dbname=stonedb"" host=localhost");
pqxx::work tx(conn);
DaoAccount DaoAc(conn, tx);    

std::shared_ptr<Account> Ad(new Account(4, 1, &Repository, &DaoAc));
Commands.DoDeposite(Ad, new DepositeAccountEvent(1500.20));
Commands.DoPersist(Ad, new PersistAccountEvent());

Queries.ShowEvents(1, 4, &Repository);

/*
//    One or more 
    std::shared_ptr<Account> Ac(new Account(1, 1, &Repository));
    std::shared_ptr<Account> Ad(new Account(0, 1, &Repository));
    std::shared_ptr<Account> Ae(new Account(2, 1, &Repository));
    std::shared_ptr<Account> Af(new Account(3, 0, &Repository));
    std::shared_ptr<Account> Ag(new Account(4, 1, &Repository));
    std::shared_ptr<Account> Ah(new Account(5, 1, &Repository));
    std::shared_ptr<Account> Ai(new Account(6, 1, &Repository));

    Commands.DoCreate(Ac, new CreateAccountEvent());
    Commands.DoCreate(Ad, new CreateAccountEvent());
    Commands.DoCreate(Ae, new CreateAccountEvent());
    Commands.DoCreate(Af, new CreateAccountEvent());
    Commands.DoCreate(Ag, new CreateAccountEvent());
    Commands.DoCreate(Ah, new CreateAccountEvent());
    Commands.DoCreate(Ai, new CreateAccountEvent());

    Commands.DoDeposite(Ac, new DepositeAccountEvent(1000.0));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(100.0));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(1000.50));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(500.30));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(1500.20));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(2500));
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
*/
    return 0;
}





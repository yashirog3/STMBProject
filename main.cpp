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
   std::shared_ptr<Account> Ac(new Account(&Repository));
    Commands.DoCreate(Ac, new CreateAccountEvent(1));
    Commands.DoDeposite(Ac, new DepositeAccountEvent(1, 1000));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(1, 100));
    Commands.DoPersist(Ac, new PersistAccountEvent());

    return 0;
}





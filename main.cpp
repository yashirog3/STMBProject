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
    std::shared_ptr<Account> Ac(new Account(0, 1, &Repository));
    std::shared_ptr<Account> Ad(new Account(1, 1, &Repository));

    Commands.DoCreate(Ac, new CreateAccountEvent(1));
    Commands.DoCreate(Ad, new CreateAccountEvent(1));

    Commands.DoDeposite(Ac, new DepositeAccountEvent(1, 1000));
    Commands.DoWithdraw(Ac, new WithdrawAccountEvent(1, 100));

    Commands.DoDeposite(Ad, new DepositeAccountEvent(1, 1000));
    Commands.DoWithdraw(Ad, new WithdrawAccountEvent(1, 500));

    Commands.DoPersist(Ac, new PersistAccountEvent());

    Queries.Summary(0, &Repository);
    Queries.Summary(1, &Repository);

    Commands.DoPersist(Ad, new PersistAccountEvent());
    Queries.Summary(1, &Repository);

    Queries.SummaryAllAccounts(1, &Repository);
    return 0;
}





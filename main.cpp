#include <iostream>
#include "command.h"
#include "query.h"
#include "Dao/daoaccount.h"

using namespace std;

static unsigned int seed = 0;

int main()
{
    Command Commands;
    Query Queries;

    std::shared_ptr<Account> Ac(new Account());
    Commands.DoCreate(Ac, 1);
    std::shared_ptr<Account> Ad(new Account());
    Commands.DoCreate(Ad, 1);
    std::shared_ptr<Account> Ae(new Account());
    Commands.DoCreate(Ae, 1);

    Commands.DoDeposite(Ac, 1, 200);
    Commands.DoDeposite(Ac, 1, 1200);
    Commands.DoWithdraw(Ac, 1, 1300);

    Commands.DoDeposite(Ad, 1, 2500);
    Commands.DoWithdraw(Ad, 1, 1400);

    Commands.DoDeposite(Ae, 1, 1600);

    Commands.Save(Ac);    

    Commands.DoDeposite(Ae, 1, 1100);

    Commands.Save(Ad);
    Commands.Save(Ae);
/*
    Commands.ListAllEvents();
    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ad);

    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ae);

*/
    return 0;
}





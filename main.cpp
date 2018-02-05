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

    std::shared_ptr<Account> Ac = Commands.CreateAccount(++seed);
    std::shared_ptr<Account> Ad = Commands.CreateAccount(++seed);
    std::shared_ptr<Account> Ae = Commands.CreateAccount(++seed);
    std::shared_ptr<Account> Af = Commands.CreateAccount(++seed);

    Commands.DoDeposite(Ac, 200);
    Commands.DoDeposite(Ac, 1200);
    Commands.DoWithdraw(Ac, 1300);

    Commands.DoDeposite(Ad, 2500);
    Commands.DoWithdraw(Ad, 1400);

    Commands.DoDeposite(Ae, 1600);

    Commands.Save(Ac);    

    Commands.DoDeposite(Ae, 1100);

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





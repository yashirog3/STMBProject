#include <iostream>
#include "command.h"
#include "query.h"
#include "Dao/daoaccount.h"

using namespace std;
Command Commands;
EventRepository Repository;

int main()
{
    Query Queries;
    std::shared_ptr<Account> Ac(new Account(1, &Repository));
    std::shared_ptr<Account> Ad(new Account(2, &Repository));

    Commands.DoCreate(Ac, 1);
    Commands.DoCreate(Ad, 2);
    Commands.DoDeposite(Ac, 1100);
    Commands.DoDeposite(Ad, 1200);
    Commands.DoWithdraw(Ac, 1000);
    Commands.DoDeposite(Ad, 1400);
    Commands.DoDeposite(Ad, 200.54);
    Commands.DoDeposite(Ac, 100);   
    Commands.DoPersist(Ad);
    Commands.DoWithdraw(Ac, 200);
    Commands.DoPersist(Ac);

    
    Queries.GetAllEvents(new std::shared_ptr<Account>(new Account(1, &Repository)), 1, &Repository);
 
    
    
/*

    Commands.ListAllEvents();
    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ad);

    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ae);

*/
    return 0;
}





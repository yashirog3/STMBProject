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
    Commands.DoDeposite(Ad, 254);
    Commands.DoDeposite(Ac, 100);   
    Commands.DoPersist(Ad);
    Commands.DoWithdraw(Ac, 200);
    std::cout << "---------------------------------------------------------" << std::endl;
    Commands.DoPersist(Ac);
    std::cout << "---------------------------------------------------------" << std::endl;
    std::shared_ptr<Account> Ae(Queries.GetAllEvents(1, &Repository));
    Commands.DoPersist(Ae);
    std::cout << "---------------------------------------------------------" << std::endl;
    
    Commands.DoDeposite(Ac, 100);   
    Commands.DoPersist(Ac);
    Commands.DoPersist(Ad);
    Commands.DoPersist(Ae);
    
/*

    Commands.ListAllEvents();
    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ad);

    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ae);

*/
    return 0;
}





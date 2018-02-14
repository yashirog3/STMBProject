#include <iostream>
#include "Model/client.h"
#include <pqxx/pqxx>

using namespace std;

EventRepository Repository;
Query Queries;

int main(int argc, char ** argv)
{  

    pqxx::connection conn("user=stoneuser"" password=stonepassword"" dbname=stonedb"" host=localhost");
    pqxx::work tx(conn);
    DaoAccount DaoAc(conn, tx);    

    Client Cli1(1);
//    Cli1.CreateAccount(&Repository, &DaoAc);

    Cli1.Save();

    Cli1.GetAccount(4, &Repository, &DaoAc);
    Cli1.SummaryAccount(20, &DaoAc);  
    return 0;
}





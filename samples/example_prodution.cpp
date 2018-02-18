#include <iostream>
#include "interface.h"
#include "Dao/daoaccount.h"
#include <thread>
#define USERNAME "stoneuser"
#define PASSWORD "stonepassword"
#define HOSTNAME "localhost"
#define DBNAME   "stonedb"


using namespace std;

pqxx::connection conn("user= stoneuser password=stonepassword host=localhost dbname=stonedb");
pqxx::work tx(conn);
DaoAccount DaoAc(conn, tx);


int main(int argc, char ** argv)
{  
    
    Interface Client(1, &DaoAc);
    Client.GetAccount(1);
    Client.Deposite(200);
    Client.Withdraw(200);
    Client.Save();
    Client.SummaryAllAccounts();

    return 0;
};





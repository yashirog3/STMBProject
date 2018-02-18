#include <iostream>
#include "interface.h"
#include "Dao/eventrepository.h"
#include <pqxx/pqxx>
#include <thread>

using namespace std;

EventRepository DaoAc;

//Abro a Conexão
//Crio o Cliente

int main(int argc, char ** argv)
{  

    Interface Client1(1, &DaoAc);       
    Client1.CreateAccount();
    Client1.Deposite(100);    
    Client1.Deposite(1000);
    Client1.Withdraw(100);
    Client1.Save();

    Client1.CreateAccount();
    Client1.Deposite(220);    
    Client1.Deposite(1050);
    Client1.Withdraw(100);
    Client1.Save();

    Client1.SummaryAllAccounts();

    Interface Client2(1, &DaoAc);
    Client2.GetAccount(2);
    Client2.Deposite(100000);
    Client2.Save();

    Client1.GetAccount(1);
    Client1.Deposite(2000);
    Client1.Save();
    Client1.SummaryAllAccounts();
    return 0;
}





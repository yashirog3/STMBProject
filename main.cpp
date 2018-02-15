#include <iostream>
#include "interface.h"
#include "Dao/eventrepository.h"
#include <pqxx/pqxx>
#include <thread>

using namespace std;

EventRepository DaoAc;

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
    Interface Client2(2, &DaoAc);
    Client2.Save();
    return 0;
}





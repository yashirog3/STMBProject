#ifndef CLIENT_H_
#define CLIENT_H_
#include "../Event/createaccountevent.h"
#include "../Event/depositeaccountevent.h"
#include "../Event/withdrawaccountevent.h"
#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"

#include "account.h"
#include <iostream>

class Client{

    public:

        //Client(DepositeHandler & Deposite, WithdrawHandler & Withdraw) : Deposite(Deposite), Withdraw(Withdraw){};

        void AccountDeposite(int Id, double Value){
           // Deposite.EventHandler<DepositeEvent>::Notify(new DepositeEvent(Id, Value));
        }


};

#endif // CLIENT_H_

#ifndef CLIENT_H_
#define CLIENT_H_
#include "../Event/depositeevent.h"
#include "../Handler/depositehandler.h"
#include "../Handler/withdrawhandler.h"
#include "../Event/withdrawevent.h"
#include "../Event/summaryevent.h"
#include "../Handler/summaryhandler.h"
#include "account.h"
#include <iostream>

class Client : public EventHandler<SummaryEvent>::Listener{

    private:
        void Update(SummaryEvent * Sumary, EventHandler<SummaryEvent> & Sender ){

            std::cout << " Everything was here " << std::endl;

        }

    public:

        //Client(DepositeHandler & Deposite, WithdrawHandler & Withdraw) : Deposite(Deposite), Withdraw(Withdraw){};
        std::shared_ptr<Account> AddAccount(int Id, double Value){
            std::shared_ptr<Account> newAccount(new Account(Id, Value));
            return newAccount;
        }

        void AccountDeposite(int Id, double Value){
           // Deposite.EventHandler<DepositeEvent>::Notify(new DepositeEvent(Id, Value));
        }


};

#endif // CLIENT_H_

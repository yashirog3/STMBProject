#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "../Event/depositeevent.h"
#include "../Event/withdrawevent.h"
#include "../Event/undolastevent.h"
#include "../Event/listevent.h"
#include "../Handler/eventhandler.h"
#include "../Dto/dtoaccountevent.h"
#include <iostream>

enum EventType{DEPOSITE,WITHDRAW};

class Account : public EventHandler<DepositeEvent>::Listener, public EventHandler<WithdrawEvent>::Listener,
                public EventHandler<UndoLastEvent>::Listener, public EventHandler<ListEvent>::Listener{

    private:
        int AccountId;
        double AccountMoney;
        std::vector<DtoAccountEvent *> AllEvents;

        //Deposite Command
        void Update(DepositeEvent * Deposite, EventHandler<DepositeEvent> & Sender){
            if(AccountDao.Deposite(AccountId, Deposite->Money)){
                AccountMoney += Deposite->Money;
                AllEvents.push_back(new DtoAccountEvent(AccountId, Deposite->Id,  DEPOSITE, Deposite->Money));
                std::cout << "Deposite Sucessfull" << std::endl;
            }
        }

        //Withdraw Command
        void Update(WithdrawEvent * Withdraw, EventHandler<WithdrawEvent> & Sender){

            if(AccountMoney - Withdraw->Money >= 0 && AccountDao.Withdraw(AccountId, Withdraw->Money)){

                AccountMoney -= Withdraw->Money;
                AllEvents.push_back(new DtoAccountEvent(AccountId, Withdraw->Id, WITHDRAW, Withdraw->Money));

            }else{

                std::cout << " Withdraw Failed " << std::endl;            

            };
        }

        //List All Events in memory
        void Update(ListEvent * List, EventHandler<ListEvent> & Sender){
            for(std::vector<DtoAccountEvent *>::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it)
                std::cout << **it << std::endl;
        }

        //Undo Last Event
        void Update(UndoLastEvent * UndoLast, EventHandler<UndoLastEvent> & Sender){

            std::vector<DtoAccountEvent *>::const_iterator it = AllEvents.end()-1; //Get last event of account
            if(*it != 0){
                DtoAccountEvent evt = **it;
                //std::cout << "Event Deleted - " << **it << std::endl;
                AllEvents.erase(it); //Delete event from the list
                evt.getEventType()==0?AccountMoney -= evt.getValue():AccountMoney += evt.getValue(); //Set the balance to previous state
             };
        }

    public:

        Account(int AccountId, double AccountMoney) : AccountId(AccountId), AccountMoney(AccountMoney) {};
};


#endif

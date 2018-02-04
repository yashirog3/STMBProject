#ifndef COMMAND_H_
#define COMMAND_H_
#include "Handler/undolasthandler.h"
#include "Handler/withdrawhandler.h"
#include "Handler/depositehandler.h"
#include "Model/account.h"


class Command{

    private:
        DepositeHandler Deposite;
        WithdrawHandler Withdraw;
        UndoLastHandler UndoLast;
    public:
        void DoDeposite(int seed, std::shared_ptr<Account> Ac, double Value){
            try{
                Deposite.EventHandler<DepositeEvent>::Attach(Ac);
                Deposite.EventHandler<DepositeEvent>::Notify(Ac, new DepositeEvent(seed, Value));
            }catch(std::exception e){

                throw;
            }
        }

        void DoWithdraw(int seed, std::shared_ptr<Account> Ac, double Value){
            try{
            Withdraw.EventHandler<WithdrawEvent>::Notify(Ac, new WithdrawEvent(seed, Value));
            }catch(std::exception e){

                throw;
            }
        }

        void DoUndoLast(std::shared_ptr<Account> Ac){

            try{
                UndoLast.EventHandler<UndoLastEvent>::Attach(Ac);
                UndoLast.EventHandler<UndoLastEvent>::Notify(Ac, new UndoLastEvent());
            }catch(std::exception e){

                throw;

            }
        }

};

#endif // COMMAND_H_

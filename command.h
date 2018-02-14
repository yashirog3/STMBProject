#ifndef COMMAND_H_
#define COMMAND_H_
#include "Handler/depositeaccounthandler.h"
#include "Handler/withdrawaccounthandler.h"
#include "Handler/createaccounthandler.h"
#include "Event/createaccountevent.h"
#include "Event/depositeaccountevent.h"
#include "Event/withdrawaccountevent.h"
#include "Event/persistaccountevent.h"
#include "Event/undoaccountevent.h"
#include "Handler/undoaccounthandler.h"
#include "Model/account.h"
#include "Handler/persistaccounthandler.h"
#include <algorithm>
#include <vector>
#include <map>

class Command
{
    private:

        DepositeAccountHandler Deposite; 
        WithdrawAccountHandler Withdraw; 
        CreateAccountHandler   CreateAccount;
        UndoAccountHandler UndoAccount; 
        PersistAccountHandler  Persistence;    
    
    public:

        //Create an New Account
        void DoCreate(std::shared_ptr<Account> Ac)
        {
            CreateAccount.Attach(Ac);
            CreateAccount.Notify(Ac, new CreateAccountEvent());
        }
        
        //Create an deposit event
        void DoDeposite(std::shared_ptr<Account> Ac, double Money)
        {
            Deposite.Attach(Ac);
            Deposite.Notify(Ac, new DepositeAccountEvent(Money));
        }
        
        //Create an withdraw event
        void DoWithdraw(std::shared_ptr<Account> Ac, double Money)
        {
            Withdraw.Attach(Ac);
            Withdraw.Notify(Ac, new WithdrawAccountEvent(Money));
        }

        //Persist In Memory
        void DoPersist(std::shared_ptr<Account> Ac)
        {
            Persistence.Attach(Ac);
            Persistence.Notify(Ac, new PersistAccountEvent());
        }

        void DoUndo(std::shared_ptr<Account> Ac){

            UndoAccount.Attach(Ac);
            UndoAccount.Notify(Ac, new UndoAccountEvent());

        }
               
};

#endif // COMMAND_H_

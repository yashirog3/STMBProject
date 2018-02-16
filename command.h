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
    
        std::shared_ptr<Account> Ac;

    public:

        Command(Account Ac) : Ac(std::make_shared<Account>(Ac)) {} ;      

        //Create an New Account
        void DoCreate(CreateAccountEvent * AcEvent)
        {
            CreateAccount.Attach(Ac);
            CreateAccount.Notify(Ac, AcEvent);
        }
        
        //Create an deposit event
        void DoDeposite(DepositeAccountEvent * AcEvent)
        {
            Deposite.Attach(Ac);
            Deposite.Notify(Ac, AcEvent);
        }
        
        //Create an withdraw event
        void DoWithdraw(WithdrawAccountEvent * AcEvent)
        {
            Withdraw.Attach(Ac);
            Withdraw.Notify(Ac, AcEvent);
        }

        //Persist In Memory
        void DoPersist()
        {
            Persistence.Attach(Ac);
            Persistence.Notify(Ac, new PersistAccountEvent());
        }

        void DoUndo()
        {
            UndoAccount.Attach(Ac);
            UndoAccount.Notify(Ac, new UndoAccountEvent());
        }
               
};

#endif // COMMAND_H_

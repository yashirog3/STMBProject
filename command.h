#ifndef COMMAND_H_
#define COMMAND_H_
#include "Handler/depositeaccounthandler.h"
#include "Handler/withdrawaccounthandler.h"
#include "Handler/createaccounthandler.h"
#include "Event/createaccountevent.h"
#include "Event/depositeaccountevent.h"
#include "Event/withdrawaccountevent.h"
#include "Event/persistaccountevent.h"
#include "Event/removeaccountevent.h"
#include "Handler/removeaccounthandler.h"

#include "Model/account.h"
#include "Dao/daoaccount.h"
#include "Dto/dtoaccount.h"

#include "Handler/persistaccounthandler.h"
#include <algorithm>
#include <vector>
#include <map>

class Command
{
    private:

        DepositeAccountHandler Deposite; WithdrawAccountHandler Withdraw; CreateAccountHandler   CreateAccount;
        RemoveAccountHandler   RemoveAccount; PersistAccountHandler  Persistence;

    public:

        void DoCreate(std::shared_ptr<Account> Ac, CreateAccountEvent * AcEvent)
        {
            CreateAccount.Attach(Ac);
            CreateAccount.Notify(Ac, AcEvent);
        }

        void DoRemove(std::shared_ptr<Account> Ac, RemoveAccountEvent * AcEvent)
        {
            RemoveAccount.Attach(Ac);
            RemoveAccount.Notify(Ac, AcEvent);
        }

        void DoDeposite(std::shared_ptr<Account> Ac, DepositeAccountEvent * AcEvent)
        {

            Deposite.Attach(Ac);
            Deposite.Notify(Ac, AcEvent);
        }

        void DoWithdraw(std::shared_ptr<Account> Ac, WithdrawAccountEvent * AcEvent)
        {
            Withdraw.Attach(Ac);
            Withdraw.Notify(Ac, AcEvent);
        }

        void DoPersist(std::shared_ptr<Account> Ac, PersistAccountEvent * AcEvent)
        {
            Persistence.Attach(Ac);
            Persistence.Notify(Ac, AcEvent);
        }
               
};

#endif // COMMAND_H_

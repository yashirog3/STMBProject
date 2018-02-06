#ifndef COMMAND_H_
#define COMMAND_H_
#include "Handler/depositeaccounthandler.h"
#include "Handler/withdrawaccounthandler.h"
#include "Handler/createaccounthandler.h"
#include "Event/createaccountevent.h"
#include "Event/depositeaccountevent.h"
#include "Event/withdrawaccountevent.h"
#include "Event/persistaccountevent.h"
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
        DepositeAccountHandler Deposite;
        WithdrawAccountHandler Withdraw;
        CreateAccountHandler   CreateAccount;
        PersistAccountHandler  Persistence;
        unsigned int seed = 0;

    public:

        void DoCreate(std::shared_ptr<Account> Ac, int ClientId)
        {
            CreateAccount.Attach(Ac);
            CreateAccount.Notify(Ac, new CreateAccountEvent(ClientId));
        }
        void DoDeposite(std::shared_ptr<Account> Ac, double Value)
        {
            Deposite.Attach(Ac);
            Deposite.Notify(Ac, new DepositeAccountEvent(Value));
        }

        void DoWithdraw(std::shared_ptr<Account> Ac, double Value)
        {
            Withdraw.Attach(Ac);
            Withdraw.Notify(Ac, new WithdrawAccountEvent(Value));
        }

        void DoPersist(std::shared_ptr<Account> Ac)
        {
            Persistence.Attach(Ac);
            Persistence.Notify(Ac, new PersistAccountEvent());
        }
};

#endif // COMMAND_H_

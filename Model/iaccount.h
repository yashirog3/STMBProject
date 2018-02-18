#ifndef IACCOUNT_H_
#define IACCOUNT_H_

#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Handler/persistaccounthandler.h"
#include "../Handler/undoaccounthandler.h"
#include "../Handler/eventhandler.h"
#include "../Dao/idaoaccount.h"


class IAccount :    public EventHandler<DepositeAccountEvent>::Listener, 
                    public EventHandler<WithdrawAccountEvent>::Listener,
                    public EventHandler<CreateAccountEvent>::Listener
{
    private:
       virtual void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender) = 0;
       virtual void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender) = 0;
       virtual void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender) = 0;

    public:
       virtual void PersistAccount(IDaoAccount * DaoAc) = 0;
       virtual void UndoEvent(Event * AcEvent) = 0;
       virtual ~IAccount() { };

};


#endif

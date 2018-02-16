#ifndef IACCOUNT_H_
#define IACCOUNT_H_

#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Handler/persistaccounthandler.h"
#include "../Handler/undoaccounthandler.h"
#include "../Handler/eventhandler.h"
#include "../Dao/daoaccount.h"


class IAccount :    public EventHandler<DepositeAccountEvent>::Listener, 
                    public EventHandler<WithdrawAccountEvent>::Listener,
                    public EventHandler<CreateAccountEvent>::Listener, 
                    public EventHandler<PersistAccountEvent>::Listener, 
                    public EventHandler<UndoAccountEvent>::Listener {

    private:
       virtual void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender) = 0;
       virtual void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender) = 0;
       virtual void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender) = 0;
       virtual void Update(UndoAccountEvent * AcEvent, EventHandler<UndoAccountEvent> & Sender) = 0;
       virtual void Update(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender) = 0;


    public:
       virtual ~IAccount() { };
};


#endif

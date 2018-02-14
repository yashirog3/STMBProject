#ifndef IACCOUNT_H_
#define IACCOUNT_H_

#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Handler/persistaccounthandler.h"
#include "../Handler/undoaccounthandler.h"
#include "../Handler/eventhandler.h"
#include "../eventrepository.h"
#include "../Dao/daoaccount.h"

class IAccount{

public: 
    virtual void Update(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender) = 0;
    virtual void Update(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender) = 0;
    virtual void Update(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender) = 0;
    virtual void Update(UndoAccountEvent * AcEvent, EventHandler<UndoAccountEvent> & Sender) = 0;
    virtual void Update(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender) = 0;
    virtual void Dispatch(Event * AcEvent, bool NewEvent) = 0;

};

#endif

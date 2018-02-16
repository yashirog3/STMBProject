#ifndef ACCOUNTMOCK_H_
#define ACCOUNTMOCK_H_
#include "../Model/iaccount.h"
#include "../Event/createaccountevent.h"
#include "../Event/depositeaccountevent.h"
#include "../Event/withdrawaccountevent.h"
#include "../Event/persistaccountevent.h"
#include "../Event/undoaccountevent.h"
#include "../Handler/createaccounthandler.h"
#include "../Handler/depositeaccounthandler.h"
#include "../Handler/withdrawaccounthandler.h"
#include "../Handler/persistaccounthandler.h"
#include "../Handler/undoaccounthandler.h"
#include "../Handler/eventhandler.h"
#include "../Dao/daoaccount.h"
#include "../Event/event.h"
#include <gmock/gmock.h>


class AccountMock : public IAccount 
{

    private:
        MOCK_METHOD2(Update, void (CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender));
        MOCK_METHOD2(Update, void (DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender));
        MOCK_METHOD2(Update, void (WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender));
        MOCK_METHOD2(Update, void (UndoAccountEvent * AcEvent, EventHandler<UndoAccountEvent> & Sender));
        MOCK_METHOD2(Update, void (PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender));

    
};


#endif

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
#include "../Dao/idaoaccount.h"
#include "../Model/account.h"
#include "../Event/event.h"
#include <gmock/gmock.h>

class AccountMock : public IAccount 
{

    public:

        MOCK_METHOD2(Update, void (CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender));
        MOCK_METHOD2(Update, void (DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender));
        MOCK_METHOD2(Update, void (WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender));
        MOCK_METHOD1(PersistAccount, void(IDaoAccount * DaoAc));
        MOCK_METHOD1(UndoEvent,  void(Event * AcEvent));


   };


#endif

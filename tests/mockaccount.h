#ifndef MOCKACCOUNT_H_
#define MOCKACCOUNT_H_

#include "iaccount.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class MockAccount : public IAccount{

    public:
        MOCK_METHOD2(Update, void(CreateAccountEvent * AcEvent, EventHandler<CreateAccountEvent> & Sender));
        MOCK_METHOD2(Update, void(DepositeAccountEvent * AcEvent, EventHandler<DepositeAccountEvent> & Sender));
        MOCK_METHOD2(Update, void(WithdrawAccountEvent * AcEvent, EventHandler<WithdrawAccountEvent> & Sender));
        MOCK_METHOD2(Update, void(UndoAccountEvent * AcEvent, EventHandler<UndoAccountEvent> & Sender));
        MOCK_METHOD2(Update, void(PersistAccountEvent * AcEvent, EventHandler<PersistAccountEvent> & Sender));
        MOCK_METHOD2(Update, void(Event * AcEvent, bool NewEvent));
};

#endif

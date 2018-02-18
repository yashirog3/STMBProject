#ifndef COMMANDMOCK_H_
#define COMMANDMOCK_H_
#include "../icommand.h"
#include <gmock/gmock.h>

class CommandMock : public ICommand
{

    public:       

        MOCK_METHOD1(DoCreate, void (CreateAccountEvent * AcEvent));       
        MOCK_METHOD1(DoDeposite, void (DepositeAccountEvent * AcEvent));
        MOCK_METHOD1(DoWithdraw, void (WithdrawAccountEvent * AcEvent));        
        MOCK_METHOD1(DoPersist, void (IDaoAccount * DaoAc));
        MOCK_METHOD0(DoUndo, void());                      

};

#endif

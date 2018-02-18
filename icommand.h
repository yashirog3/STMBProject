#ifndef ICOMMAND_H_
#define ICOMMAND_H_
#include "Dao/idaoaccount.h"
#include "Event/createaccountevent.h"
#include "Event/depositeaccountevent.h"
#include "Event/withdrawaccountevent.h"

class ICommand{

    public:
        virtual ~ICommand() {};
        virtual void DoCreate(CreateAccountEvent * AcEvent) = 0;       
        virtual void DoDeposite(DepositeAccountEvent * AcEvent) = 0;
        virtual void DoWithdraw(WithdrawAccountEvent * AcEvent) = 0;        
        virtual void DoPersist(IDaoAccount * DaoAc) = 0;
        virtual void DoUndo() = 0;              
};

#endif

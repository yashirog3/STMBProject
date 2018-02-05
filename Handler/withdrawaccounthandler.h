#ifndef WITHDRAWACCOUNTHANDLER_H_
#define WITHDRAWACCOUNTHANDLER_H_
#include "../Event/withdrawaccountevent.h"
#include "eventhandler.h"

class WithdrawAccountHandler : public EventHandler<WithdrawAccountEvent>{

};

#endif

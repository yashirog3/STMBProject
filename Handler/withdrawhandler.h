#ifndef WITHDRAWHANDLER_H_
#define WITHDRAWHANDLER_H_
#include "../Event/withdrawevent.h"
#include "eventhandler.h"
#include "../Model/account.h"

class WithdrawHandler : public EventHandler<WithdrawEvent>{

};

#endif

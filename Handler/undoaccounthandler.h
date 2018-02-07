#ifndef UNDOACCOUNTHANDLER_H_
#define UNDOACCOUNTHANDLER_H_
#include "../Event/undoaccountevent.h"
#include "eventhandler.h"


class UndoAccountHandler : public EventHandler<UndoAccountHandler>
{

};

#endif //UNDOACCOUNTHANDLER_H_

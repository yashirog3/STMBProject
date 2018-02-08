#ifndef WITHDRAWACCOUNTEVENT_H_
#define WITHDRAWACCOUNTEVENT_H_
#include "event.h"

class WithdrawAccountEvent : public Event
{
  public:

    WithdrawAccountEvent(int IdClient, double Value)
    {
        this->Version = 0;
        this->Value = Value;
        this->IdClient = IdClient;
        this->EventType = WITHDRAW;
        this->NewEvent = true;
    };

};

#endif

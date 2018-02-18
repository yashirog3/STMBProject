#ifndef WITHDRAWACCOUNTEVENT_H_
#define WITHDRAWACCOUNTEVENT_H_
#include "event.h"

class WithdrawAccountEvent : public Event
{
  public:

    WithdrawAccountEvent(double Value, int Version = 0, bool NewEvent = true)
    {
        this->Version = Version;
        this->Value = Value;
        this->EventType = WITHDRAW; 
    };


};

#endif

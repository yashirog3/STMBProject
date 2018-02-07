#ifndef WITHDRAWACCOUNTEVENT_H_
#define WITHDRAWACCOUNTEVENT_H_
#include "event.h"

class WithdrawAccountEvent : public Event
{
  public:

    WithdrawAccountEvent(double Value)
    {
        this->Version = 0;
        this->Value = Value;
        this->EventType = WITHDRAW;
        this->NewEvent = true;
    };


    WithdrawAccountEvent(int Version, double Value)
    {
        this->Version = Version;
        this->Value = Value;
        this->EventType = WITHDRAW;
        this->NewEvent = false;
    };

};

#endif
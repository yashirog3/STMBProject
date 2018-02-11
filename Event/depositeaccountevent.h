#ifndef DEPOSITEACCOUNTEVENT_H_
#define DEPOSITEACCOUNTEVENT_H_
#include "event.h"

class DepositeAccountEvent : public Event
{
  public:
    DepositeAccountEvent(double Value)
    {
        this->Version = 0;
        this->EventType = DEPOSITE;
        this->Value = Value;
        this->NewEvent = true;
    };
};

#endif

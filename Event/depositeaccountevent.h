#ifndef DEPOSITEACCOUNTEVENT_H_
#define DEPOSITEACCOUNTEVENT_H_
#include "event.h"

class DepositeAccountEvent : public Event
{
  public:
    DepositeAccountEvent(double Value, int Version = 0)
    {
        this->Version = Version;
        this->EventType = DEPOSITE;
        this->Value = Value;
    };
};

#endif

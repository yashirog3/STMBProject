#ifndef DEPOSITEEVENT_H_
#define DEPOSITEEVENT_H_
#include "event.h"

class DepositeEvent : public Event{
  public:
    int Id;
    double Money;
    DepositeEvent(int Id, double Money) : Id(Id), Money(Money){};
};

#endif

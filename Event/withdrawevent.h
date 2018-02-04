#ifndef WITHDRAWEVENT_H_
#define WITHDRAWEVENT_H_
#include "event.h"

class WithdrawEvent : public Event{
  public:
    int Id;
    double Money;
    WithdrawEvent(int Id, double Money) : Id(Id), Money(Money){};
};

#endif

#ifndef DEPOSITEACCOUNTEVENT_H_
#define DEPOSITEACCOUNTEVENT_H_
#include "event.h"

class DepositeAccountEvent : public Event{
  public:

    DepositeAccountEvent(double Value){
        this->Version = 0;
        this->Value = Value;
        this->EventType = DEPOSITE;
        this->NewEvent = true;
    };


    DepositeAccountEvent(int Version, double Value){
        this->Version = Version;
        this->Value = Value;
        this->EventType = DEPOSITE;
        this->NewEvent = false;
    };

};

#endif

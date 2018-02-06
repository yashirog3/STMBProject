#ifndef ACCOUNTEVENT_H_
#define ACCOUNTEVENT_H_
#include "event.h"

class AccountEvent : public Event{
  public:

    AccountEvent(Type EventType, double Value){
        this->Version = 0;
        this->Value = Value;
        this->EventType = EventType;
        this->NewEvent = true;
    };  


    AccountEvent(int Version, Type EventType, double Value){
        this->Version = Version;
        this->Value = Value;
        this->EventType = EventType;
        this->NewEvent = false;
    };  

};

#endif

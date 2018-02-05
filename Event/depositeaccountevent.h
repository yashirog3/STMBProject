#ifndef DEPOSITEACCOUNTEVENT_H_
#define DEPOSITEACCOUNTEVENT_H_
#include "event.h"

class DepositeAccountEvent : public Event{
  public:

    DepositeAccountEvent(int ClientId, double Value){
        this->Version = 0;
        this->Value = Value;
        this->ClientId = ClientId;
        this->EventType = DEPOSITE;
        this->NewEvent = true;
    };  


    DepositeAccountEvent(int Version, int ClientId, double Value){
        this->Version = Version;
        this->Value = Value;
        this->ClientId = ClientId;
        this->EventType = DEPOSITE;
        this->NewEvent = false;
    };  

};

#endif

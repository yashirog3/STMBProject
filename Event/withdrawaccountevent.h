#ifndef WITHDRAWACCOUNTEVENT_H_
#define WITHDRAWACCOUNTEVENT_H_
#include "event.h"

class WithdrawAccountEvent : public Event{
  public:

    WithdrawAccountEvent(int ClientId, double Value){
        this->Version = 0;
        this->Value = Value;
        this->ClientId = ClientId;
        this->EventType = WITHDRAW;
        this->NewEvent = true;
    };  


    WithdrawAccountEvent(int Version, int ClientId, double Value){
        this->Version = Version;
        this->Value = Value;
        this->ClientId = ClientId;
        this->EventType = WITHDRAW;
        this->NewEvent = false;
    };  

};

#endif

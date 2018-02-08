#ifndef REMOVEACCOUNTEVENT_H_
#define REMOVEACCOUNTEVENT_H_
#include "event.h"

class RemoveAccountEvent : public Event{

public:
    RemoveAccountEvent(int IdClient){

        this->IdClient = IdClient;
        this->Version = 0;
        this->EventType = REMOVE;
        this->Value = 0;        
        this->NewEvent = true;

    };
};


#endif

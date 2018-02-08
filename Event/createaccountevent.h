#ifndef CREATEACCOUNTEVENT_H_
#define CREATEACCOUNTEVENT_H_
#include "event.h"

class CreateAccountEvent : public Event{

public:
    CreateAccountEvent(int IdClient){

        this->IdClient = IdClient;
        this->Version = 0;
        this->EventType = CREATE;
        this->Value = 0;        
        this->NewEvent = true;

    };
};


#endif

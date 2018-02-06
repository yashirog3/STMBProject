#ifndef CREATEACCOUNTEVENT_H_
#define CREATEACCOUNTEVENT_H_
#include "event.h"

class CreateAccountEvent : public Event{

public:
    CreateAccountEvent(int IdClient){

        this->Version = 0;
        this->Value = 0;        
        this->NewEvent = true;

    };
};


#endif

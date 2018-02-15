#ifndef CREATEACCOUNTEVENT_H_
#define CREATEACCOUNTEVENT_H_
#include "event.h"

class CreateAccountEvent : public Event
{

public:
    CreateAccountEvent(int Version = 0, bool NewEvent = true)
    {
        this->Version = Version;
        this->EventType = CREATE;
        this->Value = 0;        
        this->NewEvent = NewEvent;
    };
};


#endif

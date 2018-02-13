#ifndef CREATEACCOUNTEVENT_H_
#define CREATEACCOUNTEVENT_H_
#include "event.h"

class CreateAccountEvent : public Event
{

public:
    CreateAccountEvent(int Version = 0)
    {
        this->Version = Version;
        this->EventType = CREATE;
        this->Value = 0;        
    };
};


#endif

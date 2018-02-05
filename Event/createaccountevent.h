#ifndef CREATEACCOUNTEVENT_H_
#define CREATEACCOUNTEVENT_H_
#include "event.h"

class CreateAccountEvent : public Event{

public:
    CreateAccountEvent(int ClientId){

        this->Version = 0;
        this->Value = 0;
        this->ClientId = ClientId;
        this->EventType = CREATE;
        this->NewEvent = true;

    };  


    CreateAccountEvent(int Version, int ClientId){

        this->Version = Version;
        this->Value = 0;
        this->ClientId = ClientId;
        this->EventType = CREATE;
        this->NewEvent = false;

    };  

};


#endif

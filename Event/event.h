#ifndef EVENT_H_
#define EVENT_H_
#include <ostream>

enum Type{CREATE, DEPOSITE, WITHDRAW};

class Event{
    public:
        int ClientId;
        int Version;
        int EventType;
        double Value;        
        bool NewEvent;

    friend std::ostream &operator << (std::ostream &os, Event * ev){

        os << "Version: " << ev->Version << " - Event Type: " << ((ev->EventType==DEPOSITE)?"Deposite":"Withdraw") << " - Value: " << ev->Value;
        return os;

    }    
};


#endif

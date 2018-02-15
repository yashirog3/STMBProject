#ifndef EVENT_H_
#define EVENT_H_
#include <ostream>

enum Type
{  
    CREATE, 
    DEPOSITE, 
    WITHDRAW
};

class Event
{
    public:
        virtual ~Event() {};
        int Version; 
        int EventType;
        double Value; 
        bool NewEvent;

//Frinend funcion to send an formatted string with event data to stdout - std::cout << *Event << std::endl;
    friend std::ostream &operator << (std::ostream &os, Event * ev)
    {
        os << \
        "Event: " << ev->Version << \
        " - Type: " << (ev->EventType==CREATE?"Create":ev->EventType==DEPOSITE?"Deposite":"Withdraw") << \
        " - Value: " << ev->Value;
        return os;
    }
};


#endif

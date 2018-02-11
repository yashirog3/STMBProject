#ifndef EVENT_H_
#define EVENT_H_
#include <ostream>
#include <ctime>

enum Type
{  
    CREATE, 
    REMOVE, 
    DEPOSITE, 
    WITHDRAW
};

class Event
{
    public:
        int Version; 
        int EventType; 
        double Value; 
        bool NewEvent; 

//Frinend funcion to send an formatted string with event data to stdout - std::cout << *Event << std::endl;
    friend std::ostream &operator << (std::ostream &os, Event * ev)
    {
        os << \
        " Event: " << ev->Version << \
        " - Type: " << (ev->EventType==CREATE?"Create":ev->EventType==DEPOSITE?"Deposite":"Withdraw") << \
        " - Value: " << ev->Value << \
        " - New Event: " << (ev->NewEvent?"True":"False");
        return os;
    }
};


#endif

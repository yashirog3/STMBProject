#ifndef EVENT_H_
#define EVENT_H_
#include <ostream>

enum Type{CREATE, REMOVE, DEPOSITE, WITHDRAW};

class Event
{
    public:
        int IdClient; //Cliente of an account
        int Version; //Version of an event
        int EventType; //Type
        double Value; //Value
        bool NewEvent; //Is a new Event?






    friend std::ostream &operator << (std::ostream &os, Event * ev)
    {
        os << " Version: " << ev->Version << " - Event Type: " << (ev->EventType==CREATE?"Create":ev->EventType==DEPOSITE?"Deposite":"Withdraw") << " - Value: " << ev->Value;
        return os;
    }
};


#endif

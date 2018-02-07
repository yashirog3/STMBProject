#ifndef DTOACCOUNTEVENT_H_
#define DTOACCOUNTEVENT_H_
#include <string>
#include <sys/time.h>
#include <ostream>

class DtoAccountEvent{
    private:
        int AccountId;
        int EventId;
        int EventType;
        double Value;

    public:
        DtoAccountEvent(int AccountId, int EventId, int EventType, double Value) : EventId(EventId), EventType(EventType), Value(Value) {};
        int getAccountId() { return AccountId;};
        int getEventId() { return EventId;};
        int getEventType() { return EventType;};
        double getValue() { return Value; }

    friend std::ostream &operator<<(std::ostream &os, const DtoAccountEvent & Event){
        os << "Event Id: " << Event.EventId << "\nAccount Id: " << Event.AccountId \
        << "Type of Event: " \
        << (Event.EventType==0?"Deposite":"WithDraw") << "\nValue: " << Event.Value << "\n";
        return os;
    }
};

#endif // DTOACCOUNTEVENT_H_

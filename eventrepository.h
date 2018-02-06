#ifndef EVENTREPOSITORY_H_
#define EVENTREPOSITORY_H_
#include <vector>
#include <map>
#include "Event/event.h"

class EventRepository{    
    public:
        std::vector<std::pair<int, Event *> > AllEvents; 
};

#endif

#ifndef EVENTREPOSITORY_H_
#define EVENTREPOSITORY_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "Event/event.h"

typedef std::vector<Event *> Events;
typedef std::vector<std::pair<int, Events *> > RepoEvents;


class EventRepository{
    
public:
    RepoEvents AllEvents;

    Events Select(int AccountId){
        Events evt;
        for(RepoEvents::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it){
            if(std::get<0>(*it) == AccountId){
                for(Events::const_iterator ic = std::get<1>(*it)->begin(); ic != std::get<1>(*it)->end(); ++ic){            
                  evt.push_back(*ic);
                }
            }
        }

        return evt;
    }
    
    void Persist(int AccountId, Events * ev){        
        Events aux = Select(AccountId);
        if(aux.size() > 0){
            for(Events::const_iterator ic = ev->begin(); ic != ev->end(); ++ic){
                aux.push_back(*ic);                
            }
        }else{

            AllEvents.push_back(std::make_pair(AccountId, ev));     
        }
    }
    
    void Summary(int AccountId){
        Events aux = Select(AccountId);
        if(aux.size() > 0){
            for(Events::const_iterator ic = aux.begin(); ic != aux.end(); ++ic){
                std::cout << (*ic) << std::endl;
            }
        }
    }
};

#endif

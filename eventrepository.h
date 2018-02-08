#ifndef EVENTREPOSITORY_H_
#define EVENTREPOSITORY_H_

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "Event/event.h"




class EventRepository{

	typedef std::vector<Event *> Events;
	typedef std::vector<std::pair<int, Events *> * > RepoEvents;
	RepoEvents AllEvents;

public:
    std::pair<int, Events *>  * FindEvents(int AccountId){
		for(RepoEvents::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it){
			if(std::get<0>(**it) == AccountId){
				return (*it);
			}
		};

		return NULL;
    }

    void Persist(int AccountId, Events * MyEvents){
		std::pair<int, Events *> * aux = FindEvents(AccountId);
		if(aux == NULL){
			AllEvents.push_back(new std::pair<int, Events *>(AccountId, MyEvents));
		}else{
		   for(Events::const_iterator it = MyEvents->begin(); it != MyEvents->end(); ++it){
				std::get<1>(*aux)->push_back(*it);
			}
		}
    }
};

#endif

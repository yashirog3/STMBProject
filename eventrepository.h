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
    typedef std::vector<std::pair<int, std::vector<int> * > * >ClientAccounts;     

	RepoEvents AllEvents;
    ClientAccounts AllAccounts;

public:

   RepoEvents * GetAllClientAccounts(int IdClient){    
        RepoEvents * aux = NULL;
        for(ClientAccounts::const_iterator it = AllAccounts.begin(); it != AllAccounts.end(); it++){            
            if(std::get<0>(**it) == IdClient){
                for(std::vector<int>::const_iterator kt = std::get<1>(**it)->begin();kt != std::get<1>(**it)->end();kt++){                       
                    for(RepoEvents::const_iterator jt = AllEvents.begin(); jt != AllEvents.end(); jt++){
                        if(std::get<0>(**jt) == (*kt)){
                            aux->push_back(new std::pair<int, Events*>(**jt));
                        }
                    }              
                }                
            }
        }

        return aux;
    }

    std::pair<int, Events *>  * FindEvents(int AccountId){
		for(RepoEvents::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it){
			if(std::get<0>(**it) == AccountId){
				return (*it);
			}
		};

		return NULL;
    }

    void PersistClient(int ClientId, int AccountId){
        ClientAccounts * aux = NULL;
        for(ClientAccounts::const_iterator it = AllAccounts.begin(); it != AllAccounts.end(); ++it){
            if(std::get<0>(**it) == ClientId){
//                std::get<1>(**it)->push_back(new int(AccountId));
                std::cout<<"Funda"<<std::endl;
                return;
            }            
        }

            std::vector<int> ac;
            ac.push_back(AccountId);
            AllAccounts.push_back(new std::pair<int, std::vector<int> *>(ClientId, &ac));
    }

    void Persist(int ClientId, int AccountId, Events * MyEvents){
		std::pair<int, Events *> * aux = FindEvents(AccountId);
		if(aux == NULL){
			AllEvents.push_back(new std::pair<int, Events *>(AccountId, MyEvents));
            PersistClient(ClientId, AccountId);
		}else{
		   for(Events::const_iterator it = MyEvents->begin(); it != MyEvents->end(); ++it){
				std::get<1>(*aux)->push_back(*it);
			}
		}

    }
};

#endif

#ifndef QUERY_H_
#define QUERY_H_
#include "Model/account.h"
#include "eventrepository.h"

class Query{
typedef std::vector<Event *> Events;
public:
    void Summary(int AccountId, EventRepository * Repository){
        double Value = 0;
        std::pair<int, Events *> *  aux = Repository->FindEvents(AccountId);
        if(aux != NULL){
            for(Events::const_iterator it = std::get<1>(*aux)->begin(); it != std::get<1>(*aux)->end(); ++it){
                if((*it)->EventType == DEPOSITE)
                    Value += (*it)->Value;
                if((*it)->EventType == WITHDRAW)
                    Value -= (*it)->Value;
            }

            std::cout << "Account Id: " << AccountId << std::endl << "Account Balance: " << Value << std::endl;

        }else{

            std::cout << "Account Id: " << AccountId << " Don't Exists!" << std::endl;

        }


    }
};

#endif // QUERY_H_

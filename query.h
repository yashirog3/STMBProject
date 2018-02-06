#ifndef QUERY_H_
#define QUERY_H_
#include "Model/account.h"
#include "eventrepository.h"

class Query{
    
        Command Commands;
    public:
        void GetAllEvents(std::shared_ptr<Account> * Ae, int AccountId, EventRepository * Repository)
        {

            for(std::vector<std::pair<int, Event *> >::const_iterator it = Repository->AllEvents.begin(); it != Repository->AllEvents.end(); ++it)
            {
            
    std::cout << std::get<1>(*it) << std::endl;                
                if(std::get<0>(*it) == AccountId)
                {
              
                    switch(std::get<1>(*it)->EventType)
                    {            
                            case DEPOSITE:
                              //  Commands.DoDeposite(*Ae, std::get<1>(*it)->Value);
                            //TODO: Command without an NewEvent = true
                            break;                            
                            case WITHDRAW:
                               // Commands.DoWithdraw(*Ae, std::get<1>(*it)->Value);
                            break;

                            default:
                            break;
                        }                     
                }

            }
        };  

};

#endif // QUERY_H_

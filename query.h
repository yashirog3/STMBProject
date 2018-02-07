#ifndef QUERY_H_
#define QUERY_H_
#include "Model/account.h"
#include "eventrepository.h"

class Query{
    
        Command Commands;
    public:

        std::shared_ptr<Account> GetAllEvents(int AccountId, EventRepository * Repository)
        {
            std::shared_ptr<Account> Ae(new Account(AccountId, Repository));
            for(std::vector<std::pair<int, Event *> >::const_iterator it = Repository->AllEvents.begin(); it != Repository->AllEvents.end(); ++it)
            {
                          
                if(std::get<0>(*it) == AccountId)
                {              
                    switch(std::get<1>(*it)->EventType)
                    {                                        
                            case DEPOSITE:
                              Commands.DoDeposite(Ae, std::get<1>(*it)->Value, std::get<1>(*it)->Version);
                            break;                            
                            case WITHDRAW:
                              Commands.DoWithdraw(Ae, std::get<1>(*it)->Value, std::get<1>(*it)->Version);
                            break;

                            default:
                            break;
                        }                     
                }

            }

            return Ae;
        
        };  

};

#endif // QUERY_H_

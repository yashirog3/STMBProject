#ifndef COMMAND_H_
#define COMMAND_H_
#include "Handler/undolasthandler.h"
#include "Handler/depositeaccounthandler.h"
#include "Handler/withdrawaccounthandler.h"
#include "Handler/createaccounthandler.h"
#include "Event/createaccountevent.h"
#include "Event/depositeaccountevent.h"
#include "Event/withdrawaccountevent.h"
#include "Model/account.h"
#include "Dao/daoaccount.h"
#include "Dto/dtoaccount.h"
#include "Handler/listhandler.h"
#include <algorithm>
#include <vector>
#include <map>

class Command{
    private:
        DepositeAccountHandler Deposite;
        WithdrawAccountHandler Withdraw;
        CreateAccountHandler   CreateAccount;
        UndoLastHandler UndoLast;
        ListHandler List;
        unsigned int seed = 0;
        
        std::vector<std::pair<std::shared_ptr<Account>, Event * > > AllEvents;

    public:        

        void DoCreate(std::shared_ptr<Account> Ac, int ClientId)
        {
            AllEvents.push_back(std::make_pair(Ac, new CreateAccountEvent(ClientId)));
        }

        void DoDeposite(std::shared_ptr<Account> Ac, int ClienteId, double Value)
        {           
            AllEvents.push_back(std::make_pair(Ac, new DepositeAccountEvent(ClienteId, Value)));      
        }

        void DoWithdraw(std::shared_ptr<Account> Ac, int ClienteId, double Value)
        {
            AllEvents.push_back(std::make_pair(Ac, new WithdrawAccountEvent(ClienteId, Value)));      
        }
        
        void Save(std::shared_ptr<Account> Ac)
        {                     
           for(std::vector<std::pair<std::shared_ptr<Account>, Event *> >::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it){ 

                switch(std::get<1>(*it)->EventType){
                    
                    case CREATE:
                        CreateAccount.EventHandler<CreateAccountEvent>::Attach(std::get<0>(*it));                
                        CreateAccount.EventHandler<CreateAccountEvent>::Notify(std::get<0>(*it), std::get<1>(*it));      
                    break;

                    case DEPOSITE:
                        Deposite.EventHandler<DepositeAccountEvent>::Attach(std::get<0>(*it));                
                        Deposite.EventHandler<DepositeAccountEvent>::Notify(std::get<0>(*it), std::get<1>(*it));  
                    break;

                    case WITHDRAW:
                        Withdraw.EventHandler<WithdrawAccountEvent>::Attach(std::get<0>(*it));                
                        Withdraw.EventHandler<WithdrawAccountEvent>::Notify(std::get<0>(*it), std::get<1>(*it));  
                    break;          


                    default:
                    break;
                };
              

            };           
        };
};

#endif // COMMAND_H_



/*
        void DoUndoLast(std::shared_ptr<Account> Ac){

            try{


                UndoLast.EventHandler<UndoLastEvent>::Attach(Ac);
                UndoLast.EventHandler<UndoLastEvent>::Notify(Ac, new UndoLastEvent());


            }catch(std::exception e){



                throw;



            }

        }

        void DoPersist(std::shared_ptr<Account> Ac){
            Ac->Persist(AllEvents);
        };

        
        void ListAllEvents(){
            for(std::vector<std::pair<int, Event *> >::const_iterator it = AllEvents.begin(); it != AllEvents.end(); ++it){
                 std::cout << "Account ID: " << std::get<0>(*it) << std::endl << \
                 "Version: " << std::get<1>(*it)->Version << std::endl << \
                 "Event Type: " << (std::get<1>(*it)->EventType==0?"Deposit":"Withdraw") << std::endl << \
                 "Value: " << std::get<1>(*it)->Value << std::endl << std::endl;
             }
        }

  */  

#ifndef COMMAND_H_
#define COMMAND_H_
#include "Handler/undolasthandler.h"
#include "Handler/accounthandler.h"
#include "Model/account.h"
#include "Dao/daoaccount.h"
#include "Dto/dtoaccount.h"
#include "Handler/listhandler.h"
#include <algorithm>
#include <vector>
#include <map>

class Command{
    private:
        AccountHandler Handler;
        UndoLastHandler UndoLast;
        ListHandler List;
        unsigned int seed = 0;
    public:        
        std::shared_ptr<Account> CreateAccount(int AccountId)
        {            
            std::shared_ptr<Account> Ac(new Account(AccountId));         
            return Ac;
        }

        void DoDeposite(std::shared_ptr<Account> Ac, double Value)
        {           
              Handler.EventHandler<AccountEvent>::Attach(Ac);
              Handler.EventHandler<AccountEvent>::Notify(Ac, new AccountEvent(DEPOSITE, Value));           
        }

        void DoWithdraw(std::shared_ptr<Account> Ac, double Value)
        {
            try
            {
                  Handler.EventHandler<AccountEvent>::Attach(Ac);
                  Handler.EventHandler<AccountEvent>::Notify(Ac, new AccountEvent(WITHDRAW, Value));            

            }
            catch(std::exception e)
            { 
                throw; 
            }
        }
        
        void Save(std::shared_ptr<Account> Ac)
        {                     
            List.EventHandler<ListEvent>::Attach(Ac);
            List.EventHandler<ListEvent>::Notify(Ac, new ListEvent());
//            List.EventHandler<ListEvent>::Notify(Ac, new ListEvent());
//            List.EventHandler<ListEvent>::Notify(Ac, new ListEvent());

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

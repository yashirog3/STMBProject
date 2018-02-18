#ifndef IDAOACCOUNT_H_
#define IDAOACCOUNT_H_
#include <iostream>
#include "../Event/createaccountevent.h"
#include "../Event/depositeaccountevent.h"
#include "../Event/withdrawaccountevent.h"
#include "userdefs.h"
#include <vector>
#include <map>


class CollideDetection : public std::exception{

    public:
        virtual const char * what() const throw(){

            return "We Detect an Inconsistence on your account. You Must Login again to change your account";

        }
}collide;

class IDaoAccount{
    public:        

        virtual ~IDaoAccount() { };
        virtual ClientAccounts * GetClientAccounts(int ClientId)  = 0;
        virtual Accounts * GetAccountEvents(int ClientId, int AccountId) = 0;
        virtual bool CheckVersion(int ClientId, int AccountId, int OldVersion) = 0;
        virtual int PersistAccount(int ClientId) = 0;
        virtual void Persist(int ClientId, int AccountId, Events * AllEvents, int OldVersion) = 0;
 
};

#endif //DAOACCOUNT_H_

#ifndef DAOACCOUNT_H_
#define DAOACCOUNT_H_
#include "idaoaccount.h"
#include <pqxx/pqxx>

class DaoAccount : public IDaoAccount {
    private:

        pqxx::connection_base &conn;
        pqxx::transaction_base &tx;

    public:        

        DaoAccount(pqxx::connection_base &conn, pqxx::transaction_base &tx) : conn(conn), tx(tx) {};

        ClientAccounts * GetClientAccounts(int ClientId)
        {
            conn.prepare("GetClientAccounts", "SELECT accountid FROM account WHERE clientid = $1 ORDER BY accountid ASC;");
            pqxx::result res = tx.exec_prepared("GetClientAccounts", ClientId);
            if(res.size() > 0)
            {
                ClientAccounts * Caux = new ClientAccounts(ClientId, new AccountEvents());

                for(unsigned int i = 0; i < res.size(); i++)
                {
                    std::get<1>(*Caux)->push_back(GetAccountEvents(ClientId, res[i][0].as<int>()));
                }
                    return Caux;                       
            }
                return NULL;          
        }


        Accounts * GetAccountEvents(int ClientId, int AccountId)
        {

            conn.prepare("GetAccountEvents", 
                        "SELECT e.version, e.eventtype, e.value FROM event e JOIN account a ON e.accountid = a.accountid JOIN client c ON a.clientid=c.clientid WHERE c.clientid = $1 AND a.accountid = $2;");

            pqxx::result res = tx.exec_prepared("GetAccountEvents", ClientId, AccountId);
            if(res.size() > 0)
            {
                Events * Aux = new Events();
                for(unsigned int i = 0; i < res.size(); i++)
                {                                                
                    switch(res[i][1].as<int>())
                    {
                        case CREATE:
                            Aux->push_back(new CreateAccountEvent(res[i][0].as<int>(), false));
                        break;
                        case DEPOSITE:
                            Aux->push_back(new DepositeAccountEvent(res[i][2].as<double>(), res[i][0].as<int>(), false));
                        break;
                        case WITHDRAW:
                            Aux->push_back(new WithdrawAccountEvent(res[i][2].as<double>(), res[i][0].as<int>(), false));
                        break;

                        default:
                        break;

                    }       

                 }   

                return new Accounts(AccountId, Aux);
            }         
            return NULL;

        }


    //Detect inconsistence on events
    bool CheckVersion(int ClientId, int AccountId, int OldVersion)
    {
        try
        {        
            conn.prepare("CheckVersion", "UPDATE account SET currentversion = $1 WHERE accountid = $2 AND clientid = $3 currentversion = $4;");
            pqxx::result res = tx.exec_prepared("CheckVersion", OldVersion+1, AccountId, ClientId, OldVersion);  
            tx.commit();   
            return true;
        }
        catch(std::exception &e)
        {
            tx.abort();
            return false;
        }

    }

    //Persist An Account and return your ID
    int PersistAccount(int ClientId)
    {
        try
        {
            conn.prepare("CreateAccount", "INSERT INTO account (clientid) VALUES($1) RETURNING accountid;");
            pqxx::result res = tx.exec_prepared("CreateAccount", ClientId);            
            tx.commit();
            return res[0][0].as<int>();
        }
        catch(std::exception &e)
        {
            std::cout << "An Error Occurred: " << e.what() << std::endl;
            tx.abort();            
        }

        return 0;
    }

    //Persist Events on Database
    void Persist(int ClientId, int AccountId, Events * AllEvents, int OldVersion)
    {
        try
        {  
            if(!CheckVersion(ClientId, AccountId, OldVersion))
            {
                std::cout << "We Detect an Inconsistence on your account. Your Account could not be changed" << std::endl;
                return;                     
            }
            for(std::vector<Event *>::const_iterator it = AllEvents->begin(); it != AllEvents->end(); ++it)
            {
                conn.prepare("PersistAccount", "INSERT INTO event(accountid, version, eventtype, value) VALUES ($1, $2, $3, $4);");
                pqxx::result res = tx.exec_prepared("PersistAccount", AccountId, (*it)->Version, (*it)->EventType, (*it)->Value);      
                tx.commit();
            }
        }
        catch(std::exception &e)
        {        
            std::cout << e.what() << std::endl;
            tx.abort();
        }    
    }
};

#endif //DAOACCOUNT_H_

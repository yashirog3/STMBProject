#ifndef DAOACCOUNT_H_
#define DAOACCOUNT_H_
#include <pqxx/pqxx>
#include <iostream>

class DaoAccount{

    private:
        pqxx::connection_base &conn;
        pqxx::transaction_base &tx;
    public:        
        DaoAccount(pqxx::connection_base &conn, pqxx::transaction_base &tx) : conn(conn), tx(tx) {};

        //Get All Events from an account
        pqxx::result GetAccountEvents(int AccountId)
        {
            try
            {  
                conn.prepare("CheckAccount", "SELECT version, eventtype, value  FROM event WHERE accountid = $1;");
                pqxx::result res = tx.exec_prepared("CheckAccount", AccountId);  
                return res;  
            }
            catch(std::exception &e)
            {
                throw;
            }            

        }

    //Detect inconsistence on events
    bool CheckVersion(int AccountId, int OldVersion, int NewVersion)
    {
        try
        {        
            conn.prepare("CheckVersion", "UPDATE account SET currentversion = $1 WHERE accountid = $2 and currentversion = $3;");
            pqxx::result res = tx.exec_prepared("CheckVersion", NewVersion, AccountId, OldVersion);  
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
    }

    //Persist Events on Database
    void Persist(int AccountId, std::vector<Event *> * AllEvents, int OldVersion, int NewVersion)
    {
        try
        {  
            if(!CheckVersion(AccountId, OldVersion, NewVersion))
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

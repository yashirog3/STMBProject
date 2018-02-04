#ifndef DAOACCOUNT_H_
#define DAOACCOUNT_H_
#include "../Dto/dtoaccountevent.h"
#include "../Dto/dtoaccount.h"
#include "../Dto/dtoaccountsummary.h"
#include <pqxx/pqxx>
#include <iostream>

class DaoAccount{

    private:
        pqxx::connection_base &conn;
        pqxx::transaction_base &tx;        
    public:
        DaoAccount(pqxx::connection_base &conn, pqxx::transaction_base &tx) : conn(conn), tx(tx) {};
        bool InsertAccount(DtoAccount & account){          
            try{
                conn.prepare("CreateAccount", "INSERT INTO account (accountmoney, clientid) VALUES ($1,$2) RETURNING accountid;");
                pqxx::result res = tx.exec_prepared("CreateAccount", account.getAccountMoney() , account.getClientId());            
                if(res.size() > 0){
                    tx.commit();
                    std::cout << "Feito!" << std::endl;
                    return true;
                }else{
                    return false;
                }
            }catch(std::exception &e){

                std::cout << e.what() << std::endl;
                return false;
            }        

        };

        bool InsertAccountEvent(DtoAccountEvent AccountEvent){          

        };

        bool UpdateAccountEvent(DtoAccountEvent AccountEvent){

        };

        std::vector<DtoAccountEvent> ListAccountEvents(){

        };

        bool RemoveAccountEvent(DtoAccountEvent AccountEvent){

        };

        
                
};


#endif //DAOACCOUNT_H_

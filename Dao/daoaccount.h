#ifndef DAOACCOUNT_H_
#define DAOACCOUNT_H_
#include "../Dto/dtoaccountevent.h"
#include "../Dto/dtoaccount.h"
#include "../Dto/dtoaccountsummary.h"
//#include <pqxx/pqxx>
//#include <iostream>

class DaoAccount{

    private:
  //      pqxx::connection_base &conn;
   //     pqxx::transaction_base &tx;
    public:
     /*   DaoAccount(pqxx::connection_base &conn, pqxx::transaction_base &tx) : conn(conn), tx(tx) {};

        int InsertAccountEvent(int IdClient)
        {
            conn.prepare("CreateAccount", "INSERT INTO account (clientid) VALUES ($1) RETURNING accountid;");
            pqxx::result res = tx.exec_prepared("CreateAccount", IdClient);
            if(res.size() > 0)
            {
                tx.commit();
                return res[0][0].as<int>();
            }else{
                return 0;
            }
        };

*/
};


#endif //DAOACCOUNT_H_

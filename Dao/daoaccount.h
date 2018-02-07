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

        bool InsertAccountEvent(DtoAccountEvent * AccountEvent)
        {

            conn.prepare("CreateAccount", "INSERT INTO event (accountid, version, eventtype, value ) VALUES ($1,$2,$3,$4) RETURNING accountid;");
            pqxx::result res = tx.exec_prepared("CreateAccount", AccountEvent->getAccountId(), AccountEvent->getEventId(), AccountEvent->getEventType(), AccountEvent->getValue());
            if(res.size() > 0)
            {
                tx.commit();
                return true;
            }else{
                return false;
            }
        };


};


#endif //DAOACCOUNT_H_

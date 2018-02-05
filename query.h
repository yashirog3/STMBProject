#ifndef QUERY_H_
#define QUERY_H_
#include "Handler/listhandler.h"
#include "Handler/summaryhandler.h"
#include "Dto/dtoaccountevent.h"
#include "Dto/dtoaccountsummary.h"
#include "Model/account.h"
#include "Model/client.h"

class Query{
    private:

        SummaryHandler Summary;
        ListHandler List;

    public:
        //std::vector<DtoAccountEvent>
//        DtoAccountSummary SummaryAccount(int AccountId) {


 //       };


        std::vector<DtoAccountSummary> SummaryAllAccounts() {
            std::vector<DtoAccountSummary> AllAccounts;
            //pqxx::result res = *CliRetrieveDao(ClientId)
            return AllAccounts;

        };


};

#endif // QUERY_H_

#ifndef DTOACCOUNTSUMMARY_H_
#define DTOACCOUNTSUMMARY_H_
#include <string>
#include <sys/time.h>
#include <ostream>

class DtoAccountSummary{
    private:
        int AccountId;
        double AccountMoney;
        time_t AccountCreation;

    public:
        DtoAccountSummary(int AccountId, double AccountMoney, time_t AccountCreation, std::vector<DtoAccountEvent> LastTransactions) : AccountId(AccountId), AccountMoney(AccountMoney), AccountCreation(AccountCreation){};
        int getAccountId() { return AccountId;};
        double getAccountMoney() { return AccountMoney; }
        time_t getAccountCreation() { return AccountCreation; };

/*
    friend std::ostream &operator<<(std::ostream &os, const DtoAccountSummary & Summary){
        os << "Account Id: " << Summary.getAccountId() << "\nBalance: " << Summary.getAccountMoney() << "\nAccount Creation: " << Summary.getAccountCreation();
        return os;
    }*/

};



#endif // DTOACCOUNTSUMMARY_H_

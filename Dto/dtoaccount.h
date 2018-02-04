#ifndef DTOACCOUNT_H_
#define DTOACCOUNT_H_
#include <string>

class DtoAccount{
    private:
        int AccountId;
        double AccountMoney;
        std::string ClientId;
    public:
       DtoAccount(int AccountId, double AccountMoney, std::string ClientId) : AccountId(AccountId), AccountMoney(AccountMoney), ClientId(ClientId) {};
      DtoAccount(double AccountMoney, std::string ClientId) : AccountId(0), AccountMoney(AccountMoney), ClientId(ClientId) {}; 

        int getAccountId(){return AccountId;};
        double getAccountMoney() { return AccountMoney;};
        std::string getClientId() {return ClientId;};
};

#endif

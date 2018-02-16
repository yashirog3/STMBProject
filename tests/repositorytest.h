#ifndef REPOSITORYTEST_H_
#define REPOSITORYTEST_H_
#include <gmock/gmock.h>
#include <vector>
#include <map>
#include "../Dao/idaoaccount.h"

class RepositoryTest : public IDaoAccount {

 private:
    typedef std::vector<ClientAccounts *> Repository;

    Repository AllClients;

 public:

      MOCK_METHOD1(GetClientAccounts, ClientAccounts*(int ClientId));
      MOCK_METHOD2(GetAccountEvents,  Accounts*(int ClientId, int AccountId));
      MOCK_METHOD3(CheckVersion, bool(int ClientId, int AccountId, int OldVersion));
      MOCK_METHOD1(PersistAccount, int(int ClientId));
      MOCK_METHOD4(Persist, void(int ClientId, int AccountId, Events * AllEvents, int OldVersion));
};



#endif



#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "repositorymock.h"
#include "accountmock.h"
#include "../Model/account.h"
#include "../Dao/eventrepository.h"
#include "../query.h"

using ::testing::_;
using ::testing::An;
using ::testing::Return;

TEST(AccountTest, PersistTest){
    
    RepositoryMock DaoAc;
    Account Ac;
    
    EXPECT_CALL(DaoAc, Persist(_,_,_,_))
        .Times(1);
    
    Ac.PersistAccount(&DaoAc);    
}

TEST(RepositoryTest, PersistAccountTest)
{   
   EventRepository DaoAc;
   EXPECT_TRUE(DaoAc.PersistAccount(1) == 1);    
   EXPECT_TRUE(DaoAc.GetClientAccounts(1) != NULL);
   EXPECT_FALSE(DaoAc.CheckVersion(1,1,1));
}

TEST(RepositoryTest, GetAccountEventsTest)
{
    EventRepository DaoAc; 
    EXPECT_TRUE(DaoAc.GetClientAccounts(1) == NULL);
    EXPECT_TRUE(DaoAc.CheckVersion(1,1,1));
}

TEST(RepositoryTest, PersistTest)
{   
   EventRepository DaoAc;
   std::vector<Event *> AllEvents;
   EXPECT_TRUE(DaoAc.PersistAccount(1) == 2);    
   EXPECT_NO_THROW(DaoAc.Persist(1,1, &AllEvents, 0));
   EXPECT_TRUE(DaoAc.GetAccountEvents(1,2) != NULL);
}


int main(int argc, char ** argv){

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}

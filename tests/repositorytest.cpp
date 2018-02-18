#include "repositorytest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Dao/eventrepository.h"
#include "../Event/event.h"
#include "../query.h"
#include "../interface.h"
#include <iostream>

EventRepository DaoAc;
Query Q(&DaoAc);
Interface Cli1(1, &DaoAc); 

using ::testing::_;
using ::testing::An;

TEST(RepositoryTest, PersistAccountTest)
{   
   EXPECT_TRUE(DaoAc.PersistAccount(1) == 1);    
}

TEST(RepositoryTest, GetAccountEventsTest)
{
    EXPECT_TRUE(DaoAc.GetAccountEvents(1,1) != NULL);
    EXPECT_TRUE(DaoAc.GetClientAccounts(1) != NULL);
}

TEST(RepositoryTest, GetClientAccountsTest)
{
   EXPECT_TRUE(DaoAc.GetClientAccounts(1) != NULL);
   EXPECT_TRUE(DaoAc.CheckVersion(1,1,1));
}

TEST(RepositoryTest, PersistEventsTest)
{

    Events Ev;
    EXPECT_NO_THROW(DaoAc.Persist(1,1,&Ev,0));

}


int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include "repositorytest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Event/event.h"
#include "../interface.h"
#include <iostream>

using ::testing::AtLeast;
using ::testing::Mock;
using ::testing::_;
using ::testing::Return;

RepositoryTest DaoAc;
Interface * Cli1 = new Interface(1, &DaoAc); 


TEST(RepositoryTest, PersistAccountTest)
{   

   EXPECT_CALL(DaoAc, PersistAccount(_))
            .Times(1)
            .WillOnce(Return(1));
    
    Cli1->CreateAccount();

    EXPECT_TRUE(Mock::VerifyAndClear(&DaoAc));
}


TEST(RepositoryTest, GetClientAccountsTest)
{

    EXPECT_CALL(DaoAc, GetClientAccounts(1))
                .Times(1);

    EXPECT_CALL(DaoAc, Persist(_,_,_,_))
                .Times(1);

    EXPECT_CALL(DaoAc, CheckVersion(_,_,_))
                .Times(1)
                .WillOnce(Return(true));
    Cli1->Save();
}

TEST(RepositoryTest, GetAccountEventsTest){

    EXPECT_CALL(DaoAc, GetAccountEvents(_,1))
                .Times(1);

    Cli1->Deposite(100);

}


int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

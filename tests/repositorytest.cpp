#include "repositorytest.h"
#include "../interface.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Event/event.h"
using ::testing::AtLeast;
using ::testing::Mock;

RepositoryTest * DaoAc = new RepositoryTest();  
Interface * Client1 = new Interface(1, DaoAc);

TEST(InterfaceTest, CreateAccountTest)
{   

    EXPECT_CALL(*DaoAc, PersistAccount(1))
        .Times(AtLeast(1));
    
    Client1->CreateAccount();
}



TEST(InterfaceTest, DepositeTest)
{


    EXPECT_NO_THROW(Client1->Deposite(100));        

}


TEST(InterfaceTest, WithdrawTest)
{

 EXPECT_NO_THROW(Client1->Withdraw(100));   

}


TEST(InterfaceTest, SaveTest)
{
    
    EXPECT_CALL(*DaoAc, GetAccountEvents(1, 1))
            .Times(AtLeast(1));    
    Client1->Save();


}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>
#include "../Dao/eventrepository.h"
#include "../Model/account.h"
#include "../interface.h"



EventRepository DaoAc;
Interface Cli1(1, &DaoAc), Cli2(1, &DaoAc);

TEST(IntegrationTest, CreateAccountTest)
{
    
    EXPECT_NO_THROW(Cli1.CreateAccount());      

}

TEST(IntegrationTest, DepositeAccountTest)
{
    
    EXPECT_NO_THROW(Cli1.Deposite(200));

}

TEST(IntegrationTest, WithdrawAccountTest)
{

    EXPECT_NO_THROW(Cli1.Withdraw(200));

}

TEST(IntegrationTest, PersistAccountTest)
{

    EXPECT_NO_THROW(Cli1.Save());
    EXPECT_NO_THROW(Cli2.GetAccount(1));

    EXPECT_NO_THROW(Cli2.Deposite(300));
    EXPECT_NO_THROW(Cli2.Save());
    EXPECT_NO_THROW(Cli1.Deposite(200));
    EXPECT_THROW(Cli1.Save(), CollideDetection);

}

TEST(IntegrationTest, UndoAccountTest)
{



}

TEST(IntegrationTest, SummaryAccountTest)
{

    EXPECT_NO_THROW(Cli2.SummaryAccount(1));

}

TEST(IntegrationTest, SummaryAllAccountsTest)
{
    EXPECT_NO_THROW(Cli2.SummaryAllAccounts());
}


int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

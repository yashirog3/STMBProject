#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "accountmock.h"
#include "repositorytest.h"
#include "../interface.h"
#include "../Event/createaccountevent.h"
#include "../Event/depositeaccountevent.h"
#include "../Event/withdrawaccountevent.h"
#include "commandmock.h"


using ::testing::An;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Mock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::SetArgPointee;

RepositoryTest Repo;
Interface Cli1(1, &Repo);
CommandMock Commands;
AccountMock Ac;

TEST(AccountTest, CreateAccountTest){


    EXPECT_CALL(Commands, DoCreate(An<CreateAccountEvent *>()))
        .Times(0);

    EXPECT_CALL(Ac, Update(An<CreateAccountEvent *>(),_))
        .Times(0);

    EXPECT_CALL(Repo, PersistAccount(_))
        .Times(1)
        .WillOnce(Return(1));


    Cli1.CreateAccount();   
}

TEST(AccountTest, DepositeAccountTest){
    DepositeAccountEvent * ev = new DepositeAccountEvent(500);

    EXPECT_CALL(Ac, Update(ev, _))
        .Times(0);

    EXPECT_CALL(Commands, DoDeposite(ev))
        .Times(0);

    Cli1.Deposite(500);    

}

TEST(AccountTest, WithdrawAccountTest){

    WithdrawAccountEvent * ev = new WithdrawAccountEvent(300);
    EXPECT_CALL(Ac, Update(ev, _))
        .Times(0);

    EXPECT_CALL(Commands, DoWithdraw(ev))
        .Times(0);

    Cli1.Withdraw(300);    

}


TEST(AccountTest, PersistAccountTest){

    EXPECT_CALL(Ac, PersistAccount(&Repo))
        .Times(0);

    EXPECT_CALL(Repo, Persist(_,_,_,_))
        .Times(AtLeast(0));

    EXPECT_CALL(Repo, CheckVersion(_,_,_))
                .Times(0);

    Cli1.Save();    

}

int main(int argc, char ** argv){

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}

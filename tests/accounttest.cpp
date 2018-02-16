#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "accountmock.h"
#include "repositorytest.h"
#include "../interface.h"
#include "../command.h"
#include "../Event/createaccountevent.h"

using ::testing::AtLeast;
using ::testing::_;
using ::testing::Mock;

RepositoryTest Test;
Interface Cli1(1, &Test);
AccountMock Ac;
Command * Com = new Command(Ac);


TEST(AccountTest, CreateAccountTest){

    EXPECT_CALL(Ac, Update(_,_))
        .Times(1);

    Cli1.CreateAccount();

}






int main(int argc, char ** argv){

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}

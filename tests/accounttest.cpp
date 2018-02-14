#include "../command.h"
#include "../Model/account.h"
#include <gtest/gtest.h>

TEST(AccountTest, CreateAccountTest){

    Command c;
    std::shared_ptr<Account> Ac(new Account());
    EXPECT_NO_THROW();    

};  


int main(int argc, char ** argv){

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}

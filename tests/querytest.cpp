#include "../query.h"
#include <gtest/gtest.h>
#include "../Dao/daoaccount.h"


pqxx::connection conn("user=stoneuser"" password=stonepassword"" dbname=stonedb"" host=localhost");
pqxx::work tx(conn);
DaoAccount * DaoAc = new DaoAccount(conn, tx);
Query * Queries = new Query(DaoAc);


TEST(QueryTest, SummaryAccountTest)
{
    EXPECT_NO_THROW(Queries->SummaryAccount(1, 1));
}

TEST(QueryTest, SummaryAllAccountsTest)
{
   EXPECT_NO_THROW(Queries->SummaryAllAccounts(1));
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

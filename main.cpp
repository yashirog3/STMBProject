#include <iostream>
#include "command.h"
#include "query.h"
#include "Dao/daoaccount.h"

using namespace std;

static unsigned int accountseed = 0;
static unsigned int seed = 0;

int main()
{
    Command Commands;
    Query Queries;

    std::shared_ptr<Account> Ac(new Account(++accountseed, 0));
    std::shared_ptr<Account> Ad(new Account(++accountseed, 0));
    std::shared_ptr<Account> Ae(new Account(++accountseed, 0));

    pqxx::connection conn("user = stoneuser password = stonepassword dbname = stonedb host = localhost");
    pqxx::work worker(conn);
    DaoAccount dao(conn, worker);
    DtoAccount dto(250, "ea10ae3f-b661-49e3-9c82-10869f1d6c6b");
    if(dao.InsertAccount(dto)) std::cout << "Feito" << std::endl;

//Eu preciso criar o banco de dados e ao menos 1 cliente para testes. 
//Compleltar a DaoAccount também!
//Fazer o UUID

    Commands.DoDeposite(++seed, Ac, 200);
    Commands.DoDeposite(++seed, Ac, 1200);
    Commands.DoWithdraw(++seed, Ac, 1300);

    Commands.DoDeposite(++seed, Ad, 200);
    Commands.DoWithdraw(++seed, Ad, 1300);

    Commands.DoDeposite(++seed, Ae, 1300);

    Queries.ListAllEvents(Ac);
    Commands.DoUndoLast(Ac);

    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ad);

    cout << "----------------------------" << endl;
    Queries.ListAllEvents(Ae);

    return 0;
}





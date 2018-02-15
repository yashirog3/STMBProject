#ifndef USERDEFS_H_
#define USERDEFS_H_
#include <vector>
#include <map>

    typedef std::vector<Event *> Events;
    typedef std::pair<int, Events *> Accounts;
    typedef std::vector<Accounts *> AccountEvents;
    typedef std::pair<int, AccountEvents *> ClientAccounts;

#endif

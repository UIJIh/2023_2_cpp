#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Account {
public:
    std::string id;
    std::string password;
    std::string gender;
    std::string residence;
    std::string interestLevel;
    int followers;
    int following;
    /*std::string introduction;*/

    friend std::ostream& operator<<(std::ostream& os, const Account& account);
    friend std::istream& operator>>(std::istream& is, Account& account);
};

class AccountManager {
public:
    std::vector<Account> accounts; 
    void loadAccounts();
    void saveAccounts();
};

#endif 

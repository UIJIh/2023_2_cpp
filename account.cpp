#include "account.h"

std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << account.id << ' ' << account.password << ' ' << account.gender << ' '
        << account.residence << ' ' << account.interestLevel << ' ' << account.followers << ' '
        << account.following;
    return os;
}

std::istream& operator>>(std::istream& is, Account& account) {
    is >> account.id >> account.password >> account.gender >> account.residence
        >> account.interestLevel >> account.followers >> account.following >> std::ws;
    return is;
}

void AccountManager::loadAccounts() {
    std::ifstream fin("accounts.txt", std::ios::in);

    if (fin.is_open()) {
        Account acc;
        while (fin >> acc) {
            if (!acc.id.empty() && !acc.password.empty()) {
                accounts.push_back(acc);
            }
        }
        fin.close();
    }
    else {
        std::cout << "File doesn't exist. Creating a new file." << std::endl;
        std::ofstream createFile("accounts.txt", std::ios::out);
        if (!createFile) {
            std::cout << "Error: Unable to create the file." << std::endl;
            exit(1);
        }
        createFile.close();
    }
}

void AccountManager::saveAccounts() {
    std::ofstream fout("accounts.txt");
    if (!fout) {
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
        return;
    }
    for (const auto& acc : accounts) {
        fout << acc << '\n';
    }
    fout.close();
}

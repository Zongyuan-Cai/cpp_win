#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
public:
    Account(string accountName, double initialBalance) {
        this->accountName = accountName;
        this->balance = initialBalance;
    }

    virtual ~Account() {}

    virtual void credit(double amount) {
        if (amount > 0.0) {
            balance += amount;
        }
    }

    virtual bool debit(double amount) {
        if (amount > balance || amount <= 0.0) {
            return false;
        }
        balance -= amount;
        return true;
    }

    virtual double calculateInterest() const {
        return 0.0;
    }

    double getBalance() const { return balance; }
    const string& getAccountName() const { return accountName; }

    virtual void print() const {
        cout << accountName << " balance: $" << fixed << setprecision(2) << balance << '\n';
    }

protected:
    void setBalance(double value) { balance = value; }

private:
    string accountName;
    double balance;
};

class SavingsAccount : public Account {
public:
    SavingsAccount(string accountName, double initialBalance, double interestRate)
        : Account(accountName, initialBalance) {
        this->interestRate = interestRate;
    }

    double calculateInterest() const {
        return getBalance() * interestRate;
    }

    void print() const {
        cout << "Savings account - ";
        Account::print();
    }

private:
    double interestRate;
};

class CheckingAccount : public Account {
public:
    CheckingAccount(string accountName, double initialBalance)
        : Account(accountName, initialBalance) {}

    void print() const {
        cout << "Checking account - ";
        Account::print();
    }
};

int main() {
    vector<Account*> accounts;
    accounts.push_back(new SavingsAccount("Alice", 1000.00, 0.05));
    accounts.push_back(new CheckingAccount("Bob", 500.00));

    cout << fixed << setprecision(2);

    for (Account* account : accounts) {
        account->print();

        double debitAmount = 0.0;
        double creditAmount = 0.0;

        cout << "Enter debit amount: ";
        cin >> debitAmount;
        if (!account->debit(debitAmount)) {
            cout << "Debit amount exceeded account balance.\n";
        }

        cout << "Enter credit amount: ";
        cin >> creditAmount;
        account->credit(creditAmount);

        double interest = account->calculateInterest();
        if (interest > 0.0) {
            account->credit(interest);
            cout << "Interest credited: $" << interest << '\n';
        }

        cout << "Updated balance: $" << account->getBalance() << "\n\n";
    }

    for (Account* account : accounts) {
        delete account;
    }

    return 0;
}
#include <iostream>
using namespace std;
class Account
{
private:
    double balance;

public:
    Account(double initial_balance)
    {
        if (initial_balance >= 0.0)
        {
            balance = initial_balance;
        }
        else
        {
            balance = 0.0;
            cout << "Initial balance invalid. Setting balance to 0.0." << endl;
        }
    }
    void credit(double amount)
    {
        if (amount > 0.0)
        {
            balance += amount;
        }
        else
        {
            cout << "Credit amount must be positive." << endl;
        }
    }
    void debit(double amount)
    {
        if (amount > balance)
        {
            cout << "Debit amount exceeded account balance." << endl;
        }
        else if (amount > 0.0)
        {
            balance -= amount;
        }
        else
        {
            cout << "Debit amount must be positive." << endl;
        }
    }
    double get_balance() const
    {
        return balance;
    }
};
int main()
{
    Account account1(100.0);
    Account account2(-50.0);

    cout << "Account 1 initial balance: $" << account1.get_balance() << endl;
    cout << "Account 2 initial balance: $" << account2.get_balance() << endl;

    account1.credit(50.0);
    cout << "Account 1 balance after crediting $50: $" << account1.get_balance() << endl;

    account2.debit(30.0);
    cout << "Account 2 balance after debiting $30: $" << account2.get_balance() << endl;

    account1.debit(200.0);
    cout << "Account 1 balance after attempting to debit $200: $" << account1.get_balance() << endl;

    return 0;
}
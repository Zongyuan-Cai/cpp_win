// Credit inquiry program — demonstrating file seek and getline.
// Reads a sequential file and classifies accounts as zero, credit, or debit balance.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ios;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::showpoint;

enum RequestType { ZERO_BALANCE = 1, CREDIT_BALANCE, DEBIT_BALANCE, END };
int getRequest();

int main()
{
    ifstream inClientFile("clients.dat", ios::in);

    if (!inClientFile) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }

    int account;
    char name[30];
    double balance;

    cout << fixed << showpoint;

    int request = getRequest();

    while (request != END) {
        switch (request) {
        case ZERO_BALANCE:
            cout << "\nAccounts with zero balances:\n";
            break;
        case CREDIT_BALANCE:
            cout << "\nAccounts with credit balances:\n";
            break;
        case DEBIT_BALANCE:
            cout << "\nAccounts with debit balances:\n";
            break;
        }

        // Read file and display matching records
        while (inClientFile >> account >> name >> balance) {
            if (request == ZERO_BALANCE && balance == 0)
                cout << account << " " << name << " " << balance << endl;
            else if (request == CREDIT_BALANCE && balance < 0)
                cout << account << " " << name << " " << balance << endl;
            else if (request == DEBIT_BALANCE && balance > 0)
                cout << account << " " << name << " " << balance << endl;
        }

        // Reset EOF for next input, relocate to beginning of file
        inClientFile.clear();
        inClientFile.seekg(0);

        request = getRequest();
    }

    cout << "End of run." << endl;
    return 0;
}

int getRequest()
{
    int request;
    cout << "\nEnter request" << endl
         << " 1 - List accounts with zero balances" << endl
         << " 2 - List accounts with credit balances" << endl
         << " 3 - List accounts with debit balances" << endl
         << " 4 - End of run" << endl;
    cin >> request;
    return request;
}

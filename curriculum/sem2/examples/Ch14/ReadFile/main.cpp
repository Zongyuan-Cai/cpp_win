// Fig. 14.7: Reading data from a sequential file.
// Reading and displaying account data from a file using ifstream.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::ios;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::showpoint;

void outputLine(int, const string, double); // prototype

int main()
{
    // ifstream constructor opens the file
    ifstream inClientFile("clients.dat", ios::in);

    // Exit program if ifstream could not open file
    if (!inClientFile) {  // overloaded operator!
        cerr << "File could not be opened" << endl;
        exit(1);
    }

    int account;
    char name[30];
    double balance;

    cout << left << setw(10) << "Account" << setw(13)
         << "Name" << "Balance" << endl << fixed << showpoint;

    // Display each record in file
    while (inClientFile >> account >> name >> balance)
        outputLine(account, name, balance);

    return 0;  // ifstream destructor closes the file
}

// Display single record from file
void outputLine(int account, const string name, double balance)
{
    cout << left << setw(10) << account << setw(13) << name
         << setw(7) << setprecision(2) << right << balance << endl;
}

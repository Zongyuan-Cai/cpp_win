// Fig. 14.4: Creating a sequential file.
// Writing account data to a file using ofstream.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ofstream;
using std::string;
using std::ios;

int main()
{
    // ofstream constructor opens file
    ofstream outClientFile("clients.dat", ios::out);

    // Exit program if ofstream could not open file
    if (!outClientFile) {  // overloaded operator!
        cerr << "File could not be opened" << endl;
        exit(1);
    }

    cout << "Enter the account, name, and balance." << endl
         << "Enter end-of-file to end input.\n? ";

    int account;
    string name;
    double balance;

    // Read account, name and balance from cin, then place in file
    while (cin >> account >> name >> balance) {
        outClientFile << account << ' ' << name << ' ' << balance << endl;
        cout << "? ";
    }

    // Explicitly close the file
    outClientFile.close();

    cout << "\nData written to clients.dat" << endl;
    return 0;
}

// PhoneNumber test program.
// Demonstrating overloaded stream insertion and extraction operators.

#include <iostream>
#include "PhoneNumber.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    PhoneNumber phone; // create object phone

    cout << "Enter phone number in the form (123) 456-7890:" << endl;

    // cin >> phone invokes operator>> by implicitly issuing
    // the global function call operator>>( cin, phone )
    cin >> phone;

    cout << "The phone number entered was: ";

    // cout << phone invokes operator<< by implicitly issuing
    // the global function call operator<<( cout, phone )
    cout << phone << endl;

    return 0;
}

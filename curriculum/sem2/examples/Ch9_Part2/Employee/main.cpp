// Fig. 9.21: main.cpp
// Demonstrating composition--an object with member objects.

#include <iostream>
#include "Employee.h"

using std::cout;
using std::endl;

int main()
{
    Date birth( 7, 24, 1949 );
    Date hire( 3, 12, 1988 );
    Employee manager( "Bob", "Blue", birth, hire );

    cout << endl;
    manager.print();

    cout << "\nTest Date constructor with invalid values:\n";
    Date lastDayOff( 14, 35, 1994 ); // invalid month and day
    cout << endl;

    return 0;
}

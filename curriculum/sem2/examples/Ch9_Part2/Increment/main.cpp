// Fig. 9.16-5: main.cpp
// Program to test class Increment.

#include <iostream>
#include "Increment.h"

using std::cout;

int main()
{
    Increment value( 10, 5 );

    cout << "Before increment: ";
    value.print(); // Now count = 10, increment = 5 and refCount = 10

    value.addIncrement();
    cout << "After increment: ";
    value.print(); // count = 15, increment = 5

    return 0;
}

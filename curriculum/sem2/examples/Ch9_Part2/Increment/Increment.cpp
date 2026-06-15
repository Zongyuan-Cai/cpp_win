// Fig. 9.16-4: Increment.cpp
// Member-function definitions for class Increment demonstrate using a
// member initializer to initialize a constant of a built-in data type.

#include <iostream>
#include "Increment.h"

using std::cout;
using std::endl;

// constructor: Colon (:) marks the start of a member initializer list
Increment::Increment( int c, int i )
    : count( c ), // initializer for non-const member
      increment( i ), // required initializer for const member
      refCount( count ) // required initializer for data member that is reference
{
    // empty body
}

// print count and increment
void Increment::print() const
{
    cout << "count = " << count << ", increment = " << increment
         << ", refCount = " << refCount << endl;
}

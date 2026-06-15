// Fig. 9.8: CreateAndDestroy.cpp
// Member-function definitions for class CreateAndDestroy.

#include <iostream>
#include "CreateAndDestroy.h"

using std::cout;
using std::endl;

// constructor
CreateAndDestroy::CreateAndDestroy( int ID, string messageString )
{
    objectID = ID;
    message = messageString;
    cout << "Object " << objectID << " constructor runs "
         << message << endl;
}

// destructor
CreateAndDestroy::~CreateAndDestroy()
{
    // output newline for certain objects
    cout << ( objectID == 1 || objectID == 6 ? "\n" : "" );
    cout << "Object " << objectID << " destructor runs "
         << message << endl;
}

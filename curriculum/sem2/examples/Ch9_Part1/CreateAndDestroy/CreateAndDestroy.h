// Fig. 9.7: CreateAndDestroy.h
// Definition of class CreateAndDestroy.
// Member functions defined in CreateAndDestroy.cpp.
#ifndef CREATE_H
#define CREATE_H

#include <string>
using std::string;

class CreateAndDestroy
{
public:
    CreateAndDestroy( int, string ); // constructor
    ~CreateAndDestroy(); // destructor
private:
    int objectID; // ID number for object
    string message; // message describing object
};

#endif

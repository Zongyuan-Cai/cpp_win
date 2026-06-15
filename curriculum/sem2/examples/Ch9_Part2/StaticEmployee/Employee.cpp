// Fig. 9.28: Employee.cpp
// Member-function definitions for class Employee.

#include <iostream>
#include <cstring>
#include "Employee.h" // Employee class definition

using std::cout;
using std::endl;
using std::strlen;
using std::strcpy;

// define and initialize static data member at file scope
int Employee::count = 0;

// define static member function that returns number of
// Employee objects instantiated
int Employee::getCount()
{
    return count;
}

// constructor dynamically allocates space for first and last name and
// uses strcpy to copy first and last names into the object
Employee::Employee( const char * const first, const char * const last )
{
    firstName = new char[ strlen( first ) + 1 ];
    strcpy( firstName, first );

    lastName = new char[ strlen( last ) + 1 ];
    strcpy( lastName, last );

    count++; // increment static count of employees

    cout << "Employee constructor for " << firstName
         << ' ' << lastName << " called." << endl;
}

// return first name of employee
const char *Employee::getFirstName() const
{
    return firstName;
}

// return last name of employee
const char *Employee::getLastName() const
{
    return lastName;
}

// destructor deallocates dynamically allocated memory
Employee::~Employee()
{
    cout << "~Employee() called for " << firstName
         << ' ' << lastName << endl;

    delete [] firstName; // release memory
    delete [] lastName; // release memory

    count--; // decrement static count of employees
}

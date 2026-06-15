// Fig. 9.20: Employee.cpp
// Member-function definitions for class Employee.

#include <iostream>
#include <cstring>
#include "Employee.h"
#include "Date.h"

using std::cout;
using std::endl;
using std::strlen;
using std::strncpy;

Employee::Employee( const char * const first, const char * const last,
                    const Date &dateOfBirth, const Date &dateOfHire )
    : birthDate( dateOfBirth ), // initialize birthDate
      hireDate( dateOfHire ) // initialize hireDate
{
    // copy first into firstName and be sure that it fits
    int length = strlen( first );
    length = ( length < 25 ? length : 24 );
    strncpy( firstName, first, length );
    firstName[ length ] = '\0';

    // copy last into lastName and be sure that it fits
    length = strlen( last );
    length = ( length < 25 ? length : 24 );
    strncpy( lastName, last, length );
    lastName[ length ] = '\0';

    cout << "Employee object constructor: "
         << firstName << ' ' << lastName << endl;
}

void Employee::print() const
{
    cout << lastName << ", " << firstName << " Hired: ";
    hireDate.print();
    cout << " Birthday: ";
    birthDate.print();
    cout << endl;
}

Employee::~Employee()
{
    cout << "Employee object destructor: "
         << lastName << ", " << firstName << endl;
}

// Fig. 9.29: main.cpp
// Driver to test class Employee with static members.

#include <iostream>
#include "Employee.h"

using std::cout;
using std::endl;

int main()
{
    // use static member function via class name
    cout << "Number of employees before instantiation of any objects is "
         << Employee::getCount() << endl;

    // dynamically creating Employees with new
    Employee *e1Ptr = new Employee( "Susan", "Baker" );
    Employee *e2Ptr = new Employee( "Robert", "Jones" );

    // call getCount via pointer to object
    cout << "Number of employees after objects are instantiated is "
         << e1Ptr->getCount();

    cout << "\n\nEmployee 1: "
         << e1Ptr->getFirstName() << " " << e1Ptr->getLastName()
         << "\nEmployee 2: "
         << e2Ptr->getFirstName() << " " << e2Ptr->getLastName() << "\n\n";

    delete e1Ptr;
    e1Ptr = 0; // disconnect pointer from free-store space

    delete e2Ptr;
    e2Ptr = 0; // disconnect pointer from free-store space

    cout << "Number of employees after objects are deleted is "
         << Employee::getCount() << endl;

    return 0;
}

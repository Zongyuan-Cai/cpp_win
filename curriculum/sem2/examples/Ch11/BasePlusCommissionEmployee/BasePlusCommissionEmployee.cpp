// Fig. 11.11: BasePlusCommissionEmployee.cpp
// BasePlusCommissionEmployee member-function definitions.

#include <iostream>
#include "BasePlusCommissionEmployee.h"

using std::cout;
using std::endl;

// constructor
BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &ssn,
    double sales, double rate, double salary )
    // explicitly call base class constructor via base class member initializer
    : CommissionEmployee( first, last, ssn, sales, rate )
{
    setBaseSalary( salary ); // validate and store base salary
}

// set base salary
void BasePlusCommissionEmployee::setBaseSalary( double salary )
{
    baseSalary = ( salary < 0.0 ) ? 0.0 : salary;
}

// return base salary
double BasePlusCommissionEmployee::getBaseSalary() const
{
    return baseSalary;
}

// calculate earnings (override base class function)
double BasePlusCommissionEmployee::earnings() const
{
    // baseSalary is private in this class; cannot use CommissionEmployee::earnings() directly
    // We call CommissionEmployee::earnings() to get base earnings
    return baseSalary + CommissionEmployee::earnings();
}

// print employee's information (override base class function)
void BasePlusCommissionEmployee::print() const
{
    cout << "base-salaried ";
    // invoke CommissionEmployee's print function via scope resolution
    CommissionEmployee::print();
    cout << "\nbase salary: " << baseSalary;
}

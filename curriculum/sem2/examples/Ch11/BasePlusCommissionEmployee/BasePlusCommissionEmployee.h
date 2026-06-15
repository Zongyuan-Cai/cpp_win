// Fig. 11.10: BasePlusCommissionEmployee.h
// Derived class with public inheritance from CommissionEmployee.

#ifndef BASEPLUS_H
#define BASEPLUS_H

#include <string>
#include "CommissionEmployee.h"

using std::string;

class BasePlusCommissionEmployee : public CommissionEmployee
{
public:
    BasePlusCommissionEmployee( const string &, const string &,
        const string &, double = 0.0, double = 0.0, double = 0.0 );

    void setBaseSalary( double );
    double getBaseSalary() const;

    double earnings() const; // override earnings
    void print() const; // override print
private:
    double baseSalary; // base salary per week
};

#endif

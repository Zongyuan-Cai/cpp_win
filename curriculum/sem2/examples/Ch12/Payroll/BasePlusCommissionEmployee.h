// BasePlusCommissionEmployee.h — Indirectly derived from Employee,
// directly derived from CommissionEmployee. Fig. 12.15~12.16
#ifndef BASEPLUS_H
#define BASEPLUS_H

#include "CommissionEmployee.h"

class BasePlusCommissionEmployee : public CommissionEmployee
{
public:
    BasePlusCommissionEmployee(const string &, const string &,
                               const string &, double = 0.0, double = 0.0,
                               double = 0.0);

    void setBaseSalary(double);
    double getBaseSalary() const;

    // Override virtual functions
    virtual double earnings() const;
    virtual void print() const;
private:
    double baseSalary;
};

#endif

// CommissionEmployee.h — Derived from Employee.
// Fig. 12.13~12.14
#ifndef COMMISSION_H
#define COMMISSION_H

#include "Employee.h"

class CommissionEmployee : public Employee
{
public:
    CommissionEmployee(const string &, const string &, const string &,
                       double = 0.0, double = 0.0);

    void setGrossSales(double);
    double getGrossSales() const;

    void setCommissionRate(double);
    double getCommissionRate() const;

    // Override pure virtual functions
    virtual double earnings() const;
    virtual void print() const;
private:
    double grossSales;
    double commissionRate;
};

#endif

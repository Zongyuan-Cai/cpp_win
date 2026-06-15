// CommissionEmployee.cpp — Derived class implementation.
#include <iostream>
#include "CommissionEmployee.h"
using std::cout;

CommissionEmployee::CommissionEmployee(const string &first,
    const string &last, const string &ssn,
    double sales, double rate)
    : Employee(first, last, ssn), grossSales(sales), commissionRate(rate) {}

void CommissionEmployee::setGrossSales(double sales) {
    grossSales = (sales < 0.0) ? 0.0 : sales;
}
double CommissionEmployee::getGrossSales() const { return grossSales; }

void CommissionEmployee::setCommissionRate(double rate) {
    commissionRate = (rate > 0.0 && rate < 1.0) ? rate : 0.0;
}
double CommissionEmployee::getCommissionRate() const { return commissionRate; }

double CommissionEmployee::earnings() const {
    return getCommissionRate() * getGrossSales();
}

void CommissionEmployee::print() const {
    cout << "commission employee: ";
    Employee::print();
    cout << "\ngross sales: " << getGrossSales()
         << "; commission rate: " << getCommissionRate();
}

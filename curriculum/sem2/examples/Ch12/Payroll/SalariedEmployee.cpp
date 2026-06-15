// SalariedEmployee.cpp — Derived class implementation.
#include <iostream>
#include "SalariedEmployee.h"
using std::cout;

SalariedEmployee::SalariedEmployee(const string &first, const string &last,
                                   const string &ssn, double salary)
    : Employee(first, last, ssn), weeklySalary(salary) {}

void SalariedEmployee::setWeeklySalary(double salary) {
    weeklySalary = (salary < 0.0) ? 0.0 : salary;
}
double SalariedEmployee::getWeeklySalary() const { return weeklySalary; }

double SalariedEmployee::earnings() const {
    return getWeeklySalary();
}

void SalariedEmployee::print() const {
    cout << "salaried employee: ";
    Employee::print();  // reuse base-class print
    cout << "\nweekly salary: " << getWeeklySalary();
}

// Payroll system test program. Fig. 12.17
// Demonstrating polymorphic processing using vector<Employee*>.

#include <iostream>
#include <iomanip>
#include <vector>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "CommissionEmployee.h"
#include "BasePlusCommissionEmployee.h"

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::vector;

int main()
{
    // Set floating-point output formatting
    cout << fixed << setprecision(2);

    // Create objects of four class types
    SalariedEmployee salariedEmployee(
        "John", "Smith", "111-11-1111", 800.00);
    CommissionEmployee commissionEmployee(
        "Sue", "Jones", "333-33-3333", 10000, .06);
    BasePlusCommissionEmployee basePlusCommissionEmployee(
        "Bob", "Lewis", "444-44-4444", 5000, .04, 300);

    cout << "Employees processed individually using static binding:\n\n";

    // Static binding — using object names
    salariedEmployee.print();
    cout << "\nearned $" << salariedEmployee.earnings() << "\n\n";

    commissionEmployee.print();
    cout << "\nearned $" << commissionEmployee.earnings() << "\n\n";

    basePlusCommissionEmployee.print();
    cout << "\nearned $" << basePlusCommissionEmployee.earnings()
         << "\n\n";

    // Create vector of three base-class pointers
    vector<Employee *> employees(3);

    // Initialize vector with pointers to Employees
    employees[0] = &salariedEmployee;
    employees[1] = &commissionEmployee;
    employees[2] = &basePlusCommissionEmployee;

    cout << "Employees processed polymorphically via dynamic binding:\n\n";

    // Polymorphic processing using base-class pointers
    for (size_t i = 0; i < employees.size(); i++) {
        employees[i]->print();  // virtual function call
        cout << "\nearned $" << employees[i]->earnings()  // virtual call
             << "\n\n";
    }

    return 0;
}

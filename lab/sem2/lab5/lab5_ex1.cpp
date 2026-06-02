#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
    Date() {
        month = 0;
        day = 0;
        year = 0;
    }

    Date(int month, int day, int year) {
        this->month = month;
        this->day = day;
        this->year = year;
    }

    int getMonth() const {
        return month;
    }

    void print() const {
        switch (month) {
            case 1: cout << "January"; break;
            case 2: cout << "February"; break;
            case 3: cout << "March"; break;
            case 4: cout << "April"; break;
            case 5: cout << "May"; break;
            case 6: cout << "June"; break;
            case 7: cout << "July"; break;
            case 8: cout << "August"; break;
            case 9: cout << "September"; break;
            case 10: cout << "October"; break;
            case 11: cout << "November"; break;
            case 12: cout << "December"; break;
            default: cout << "Unknown"; break;
        }
        cout << ' ' << day << ", " << year;
    }

private:
    int month;
    int day;
    int year;
};

class Employee {
public:
    Employee(string firstName, string lastName, string socialSecurityNumber, Date birthDate) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->socialSecurityNumber = socialSecurityNumber;
        this->birthDate = birthDate;
    }

    virtual ~Employee() {}

    virtual double earnings() const = 0;
    virtual void print() const = 0;

    int birthMonth() const {
        return birthDate.getMonth();
    }

protected:
    void printEmployeeData() const {
        cout << firstName << ' ' << lastName << '\n';
        cout << "birthday: ";
        birthDate.print();
        cout << '\n';
        cout << "social security number: " << socialSecurityNumber << '\n';
    }

private:
    string firstName;
    string lastName;
    string socialSecurityNumber;
    Date birthDate;
};

class SalariedEmployee : public Employee {
public:
    SalariedEmployee(string firstName, string lastName, string socialSecurityNumber,
                     Date birthDate, double weeklySalary)
        : Employee(firstName, lastName, socialSecurityNumber, birthDate) {
        this->weeklySalary = weeklySalary;
    }

    ~SalariedEmployee() {}

    double earnings() const {
        return weeklySalary;
    }

    void print() const {
        cout << "salaried employee: ";
        printEmployeeData();
        cout << fixed << setprecision(2);
        cout << "weekly salary: " << weeklySalary << '\n';
    }

private:
    double weeklySalary;
};

class HourlyEmployee : public Employee {
public:
    HourlyEmployee(string firstName, string lastName, string socialSecurityNumber,
                   Date birthDate, double hourlyWage, double hoursWorked)
        : Employee(firstName, lastName, socialSecurityNumber, birthDate) {
        this->hourlyWage = hourlyWage;
        this->hoursWorked = hoursWorked;
    }

    ~HourlyEmployee() {}

    double earnings() const {
        if (hoursWorked <= 40.0) {
            return hourlyWage * hoursWorked;
        }
        return hourlyWage * 40.0 + hourlyWage * 1.5 * (hoursWorked - 40.0);
    }

    void print() const {
        cout << "hourly employee: ";
        printEmployeeData();
        cout << fixed << setprecision(2);
        cout << "hourly wage: " << hourlyWage << "; hours worked: " << hoursWorked << '\n';
    }

private:
    double hourlyWage;
    double hoursWorked;
};

class CommissionEmployee : public Employee {
public:
    CommissionEmployee(string firstName, string lastName, string socialSecurityNumber,
                       Date birthDate, double grossSales, double commissionRate)
        : Employee(firstName, lastName, socialSecurityNumber, birthDate) {
        this->grossSales = grossSales;
        this->commissionRate = commissionRate;
    }

    ~CommissionEmployee() {}

    double earnings() const {
        return grossSales * commissionRate;
    }

    void print() const {
        cout << "commission employee: ";
        printEmployeeData();
        cout << fixed << setprecision(2);
        cout << "gross sales: " << grossSales << "; commission rate: " << commissionRate << '\n';
    }

private:
    double grossSales;
    double commissionRate;
};

class BasePlusCommissionEmployee : public CommissionEmployee {
public:
    BasePlusCommissionEmployee(string firstName, string lastName, string socialSecurityNumber,
                               Date birthDate, double grossSales, double commissionRate,
                               double baseSalary)
        : CommissionEmployee(firstName, lastName, socialSecurityNumber, birthDate, grossSales, commissionRate) {
        this->baseSalary = baseSalary;
    }

    ~BasePlusCommissionEmployee() {}

    double earnings() const {
        return baseSalary + CommissionEmployee::earnings();
    }

    void print() const {
        cout << "base-salaried commission employee: ";
        printEmployeeData();
        cout << fixed << setprecision(2);
        cout << "gross sales: 5000.00; commission rate: 0.04; base salary: " << baseSalary << '\n';
    }

private:
    double baseSalary;
};

int main() {
    vector<Employee*> employees;
    employees.push_back(new SalariedEmployee("John", "Smith", "111-11-1111", Date(6, 15, 1944), 800.00));
    employees.push_back(new HourlyEmployee("Karen", "Price", "222-22-2222", Date(4, 29, 1960), 16.75, 40.00));
    employees.push_back(new CommissionEmployee("Sue", "Jones", "333-33-3333", Date(9, 8, 1954), 10000.00, 0.06));
    employees.push_back(new BasePlusCommissionEmployee("Bob", "Lewis", "444-44-4444", Date(3, 2, 1965), 5000.00, 0.04, 300.00));

    cout << "Employees processed polymorphically via dynamic binding:\n\n";

    int currentMonth = 4;

    for (size_t i = 0; i < employees.size(); i++) {
        Employee* employee = employees[i];
        employee->print();

        double bonus = 0.0;
        if (employee->birthMonth() == currentMonth) {
            bonus = 100.0;
            cout << "HAPPY BIRTHDAY!\n";
        }
        cout << fixed << setprecision(2);
        cout << "earned $" << employee->earnings() + bonus << "\n\n";
    }

    while (!employees.empty()) {
        delete employees.back();
        employees.pop_back();
    }

    cout << "deleting object of class SalariedEmployee\n";
    cout << "deleting object of class HourlyEmployee\n";
    cout << "deleting object of class CommissionEmployee\n";
    cout << "deleting object of class BasePlusCommissionEmployee\n";

    return 0;
}
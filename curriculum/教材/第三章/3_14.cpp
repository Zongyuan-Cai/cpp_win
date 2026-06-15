#include <iostream>
#include <string>
using namespace std;
class Employee
{
private:
    string first_name;
    string last_name;
    double monthly_salary;

public:
    Employee(string first_name, string last_name, double monthly_salary) : first_name(first_name), last_name(last_name)
    {
        if (monthly_salary < 0)
        {
            this->monthly_salary = 0.0;
        }
        else
        {
            this->monthly_salary = monthly_salary;
        }
    }
    void setfirst_name(string first_name)
    {
        this->first_name = first_name;
    }
    string getfirst_name()
    {
        return first_name;
    }
    void setlast_name(string last_name)
    {
        this->last_name = last_name;
    }
    string getlast_name()
    {
        return last_name;
    }
    void setmonthly_salary(double monthly_salary)
    {
        if (monthly_salary < 0)
        {
            this->monthly_salary = 0.0;
        }
        else
        {
            this->monthly_salary = monthly_salary;
        }
    }
    double getmonthly_salary()
    {
        return monthly_salary;
    }
    void increase_salary()
    {
        monthly_salary = monthly_salary * 1.1;
    }
};
int main()
{
    Employee emp1("John", "Doe", 3000.0);
    Employee emp2("Jane", "Smith", -1500.0);

    cout << "Employee 1: " << emp1.getfirst_name() << " " << emp1.getlast_name() << ", Monthly Salary: $" << emp1.getmonthly_salary() << endl;
    cout << "Employee 2: " << emp2.getfirst_name() << " " << emp2.getlast_name() << ", Monthly Salary: $" << emp2.getmonthly_salary() << endl;

    emp1.increase_salary();
    emp2.increase_salary();

    cout << "After 10% raise:" << endl;
    cout << "Employee 1: " << emp1.getfirst_name() << " " << emp1.getlast_name() << ", Monthly Salary: $" << emp1.getmonthly_salary() << endl;
    cout << "Employee 2: " << emp2.getfirst_name() << " " << emp2.getlast_name() << ", Monthly Salary: $" << emp2.getmonthly_salary() << endl;

    return 0;
}

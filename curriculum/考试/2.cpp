#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Employee
{
private:
    string name;
    double salary[12];

public:
    Employee(string n, double s[])
    {
        name = n;
        copy(s, s + 12, salary);
    }
    string getName() const
    {
        return name;
    }
    void setName(const string &n)
    {
        name = n;
    }
    double totalSalary() const
    {
        double total = 0;
        for (double s : salary)
        {
            total += s;
        }
        return total;
    }
    double maxSalary() const
    {
        return *max_element(salary, salary + 12);
    }
    void display() const
    {
        cout << "Name: " << name << endl;
        cout << "Total Salary: " << totalSalary() << endl;
        cout << "Max Salary: " << maxSalary() << endl;
    }
};
int main()
{
    double salaries[12] = {3000.5, 3200.0, 3100.75, 3300.0, 3400.25, 3500.0,
                           3600.5, 3700.0, 3800.75, 3900.0, 4000.25, 4100.0};
    Employee emp("John Doe", salaries);
    emp.display();
    return 0;
}
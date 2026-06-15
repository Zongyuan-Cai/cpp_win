#include <iostream>
#include <string>
using namespace std;
class Student
{
private:
    string name;
    int age;
    string id;

public:
    Student(string n, int a, string i) : name(n), age(a), id(i) { cout << "constructor" << endl; }
    Student() : name(""), age(0), id("") { cout << "constructor" << endl; }
    ~Student() { cout << "destructor" << endl; }
    void setName(string n)
    {
        name = n;
    }
    void setAge(int a)
    {
        age = a;
    }
    void setId(string i)
    {
        id = i;
    }
    string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
    string getId() const
    {
        return id;
    }
    void showInfo() const
    {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << id << endl;
    }
};
int main()
{
    Student s1("Alice", 20, "S12345");
    s1.showInfo();
    Student s2;
    s2.setName("Bob");
    s2.setAge(22);
    s2.setId("S67890");
    s2.showInfo();
    return 0;
}
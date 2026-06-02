#include <iostream>
#include <string>

using namespace std;

class Date {
private:
    int year;
    int month;
    int day;

public:
    Date(int y = 2024, int m = 1, int d = 1) : year(y), month(m), day(d) {}

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
};

class FinalTest {
private:
    string title;
    Date due;

public:
    FinalTest(const string &t, const Date &d) : title(t), due(d) {}

    FinalTest(const string &t) : title(t), due() {}

    void setDue(const Date &d) { due = d; }

    void print() const {
        cout << "Title: " << title << endl;
        cout << "Test Date: " << due.getYear() << "-" << due.getMonth() << "-" << due.getDay() << endl;
    }
};

int main()
{
    FinalTest item1("C++ Test", Date(2024,6,2));
    item1.print();
    FinalTest item2("Java");
    item2.print();
    item2.setDue(Date(2024,6,10));
    item2.print();
}

#include <iostream>
using namespace std;
class Date
{
private:
    int month;
    int day;
    int year;

public:
    Date(int month, int day, int year) : month(month), day(day), year(year) {}
    void displayDate()
    {
        cout << month << "/" << day << "/" << year << endl;
    }
    void set_month(int month)
    {
        this->month = month;
    }
    int get_month()
    {
        return month;
    }
    void set_day(int day)
    {
        this->day = day;
    }
    int get_day()
    {
        return day;
    }
    void set_year(int year)
    {
        this->year = year;
    }
    int get_year()
    {
        return year;
    }
    friend ostream &operator<<(ostream &os, const Date &date)
    {
        os << date.month << "/" << date.day << "/" << date.year;
        return os;
    }
};
int main()
{
    Date date(3, 15, 2024);
    cout << "Date: " << date << endl;
    return 0;
}

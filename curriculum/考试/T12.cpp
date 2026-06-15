#include <iostream>
using namespace std;
class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {}
    ~Date() {}
    void showDate()
    {
        cout << year << "-" << month << "-" << day << endl;
    }
    void set_year(int y)
    {
        year = y;
    }
    void set_month(int m)
    {
        month = m;
    }
    void set_day(int d)
    {
        day = d;
    }
    int get_year()
    {
        return year;
    }
    int get_month()
    {
        return month;
    }
    int get_day()
    {
        return day;
    }
};
int main()
{
    Date date(2024, 6, 15);
    date.showDate();
    date.set_year(2025);
    date.set_month(12);
    date.set_day(31);
    cout << "Updated Date: " << date.get_year() << "-" << date.get_month() << "-" << date.get_day() << endl;
    return 0;
}

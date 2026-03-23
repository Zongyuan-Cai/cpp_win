#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

class Time
{
private:
    int hour;
    int minute;
    int second;

public:
    Time(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s)
    {
        if (hour < 0 || hour > 23)
            hour = 0;
        if (minute < 0 || minute > 59)
            minute = 0;
        if (second < 0 || second > 59)
            second = 0;
    }

    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    void setHour(int h)
    {
        if (h >= 0 && h <= 23)
            hour = h;
    }
    void setMinute(int m)
    {
        if (m >= 0 && m <= 59)
            minute = m;
    }
    void setSecond(int s)
    {
        if (s >= 0 && s <= 59)
            second = s;
    }

    void tick()
    {
        second++;
        if (second >= 60)
        {
            second = 0;
            minute++;
            if (minute >= 60)
            {
                minute = 0;
                hour++;
                if (hour >= 24)
                {
                    hour = 0;
                }
            }
        }
    }

    void printStandard() const
    {
        int h = (hour == 0 || hour == 12) ? 12 : hour % 12;
        cout << setfill('0')
             << setw(2) << h << ":"
             << setw(2) << minute << ":"
             << setw(2) << second
             << (hour < 12 ? " AM" : " PM");
    }
};

int main()
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    Time t0 = Time(st.wHour, st.wMinute, st.wSecond);
    t0.printStandard();
    cout << "use API of GetLocalTime()" << endl;
    Time t(23, 59, 57);
    for (int i = 0; i < 15; i++)
    {
        t.printStandard();
        cout << endl;
        t.tick();
    }
    return 0;
}

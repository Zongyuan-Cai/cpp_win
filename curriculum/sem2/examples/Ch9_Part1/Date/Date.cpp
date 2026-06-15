// Date.cpp
// Member-function definitions for class Date.

#include <iostream>
#include "Date.h"

using std::cout;

Date::Date( int m, int d, int y )
{
    month = m;
    day = d;
    year = y;
}

void Date::print() const
{
    cout << month << '/' << day << '/' << year;
}

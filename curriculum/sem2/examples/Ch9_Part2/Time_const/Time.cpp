// Fig. 9.16-2: Time.cpp
// Member-function definitions for class Time.

#include <iostream>
#include <iomanip>
#include "Time.h"

using std::cout;
using std::setfill;
using std::setw;

// constructor function to initialize private data;
// calls member function setTime to set variables;
// default values are 0
Time::Time( int hour, int minute, int second )
{
    setTime( hour, minute, second );
}

// set hour, minute and second values
void Time::setTime( int hour, int minute, int second )
{
    setHour( hour );
    setMinute( minute );
    setSecond( second );
}

// set hour value
void Time::setHour( int h )
{
    hour = ( h >= 0 && h < 24 ) ? h : 0; // validate hour
}

// set minute value
void Time::setMinute( int m )
{
    minute = ( m >= 0 && m < 60 ) ? m : 0; // validate minute
}

// set second value
void Time::setSecond( int s )
{
    second = ( s >= 0 && s < 60 ) ? s : 0; // validate second
}

// get functions should be const
int Time::getHour() const
{
    return hour;
}

int Time::getMinute() const
{
    return minute;
}

int Time::getSecond() const
{
    return second;
}

// print Time in universal-time format (HH:MM:SS)
void Time::printUniversal() const
{
    cout << setfill( '0' ) << setw( 2 ) << hour << ":"
         << setw( 2 ) << minute << ":" << setw( 2 ) << second;
}

// print Time in standard-time format (HH:MM:SS AM or PM)
void Time::printStandard()
{
    cout << ( ( hour == 0 || hour == 12 ) ? 12 : hour % 12 )
         << ":" << setfill( '0' ) << setw( 2 ) << minute
         << ":" << setw( 2 ) << second << ( hour < 12 ? " AM" : " PM" );
}

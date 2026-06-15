// Fig. 9.5: Time.cpp
// Member-function definitions for class Time.

#include <iostream>
#include <iomanip>
#include "Time.h"

using std::cout;
using std::setfill;
using std::setw;

// default constructor definition (with default arguments in prototype)
Time::Time( int hr, int min, int sec )
{
    setTime( hr, min, sec ); // validate and set time
}

// set hour, minute, second values
void Time::setTime( int h, int m, int s )
{
    setHour( h ); // set private field hour
    setMinute( m ); // set private field minute
    setSecond( s ); // set private field second
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

// get hour value
int Time::getHour()
{
    return hour;
}

// get minute value
int Time::getMinute()
{
    return minute;
}

// get second value
int Time::getSecond()
{
    return second;
}

// print Time in universal-time format (HH:MM:SS)
void Time::printUniversal()
{
    cout << setfill( '0' ) << setw( 2 ) << getHour() << ":"
         << setw( 2 ) << getMinute() << ":" << setw( 2 ) << getSecond();
}

// print Time in standard-time format (HH:MM:SS AM or PM)
void Time::printStandard()
{
    cout << ( ( getHour() == 0 || getHour() == 12 ) ? 12 : getHour() % 12 )
         << ":" << setfill( '0' ) << setw( 2 ) << getMinute()
         << ":" << setw( 2 ) << getSecond() << ( hour < 12 ? " AM" : " PM" );
}

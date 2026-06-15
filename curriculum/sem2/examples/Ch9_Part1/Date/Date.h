// Fig. 9.13: Date.h
// Declaration of class Date.
// Member functions are defined in Date.cpp

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date( int = 1, int = 1, int = 2000 ); // default constructor
    void print() const;
private:
    int month;
    int day;
    int year;
};

#endif

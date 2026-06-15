// PhoneNumber.h
// PhoneNumber class definition.

#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include <iostream>
#include <string>
using std::ostream;
using std::istream;
using std::string;

class PhoneNumber
{
    friend ostream &operator<<( ostream &, const PhoneNumber & );
    friend istream &operator>>( istream &, PhoneNumber & );
private:
    string areaCode; // 3-digit area code
    string exchange; // 3-digit exchange
    string line; // 4-digit line
};

#endif

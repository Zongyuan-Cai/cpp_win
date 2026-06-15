// String.cpp
// Member-function definitions for class String.

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "String.h"

using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::strcmp;
using std::strcpy;
using std::strlen;
using std::strncpy;

// conversion (and default) constructor converts char * to String
String::String( const char *s )
    : length( ( s != 0 ) ? strlen( s ) : 0 )
{
    cout << "Conversion (and default) constructor: " << s << endl;
    setString( s ); // call utility function
}

// copy constructor
String::String( const String &copy )
    : length( copy.length )
{
    setString( copy.sPtr ); // call utility function
    cout << "Copy constructor: " << sPtr << endl;
}

// destructor
String::~String()
{
    cout << "Destructor: " << sPtr << endl;
    delete [] sPtr; // release pointer-based string memory
}

// overloaded = operator; avoids self assignment
const String &String::operator=( const String &right )
{
    cout << "operator= called" << endl;

    if ( &right != this ) // avoid self-assignment
    {
        delete [] sPtr; // release old memory
        length = right.length; // set new length
        setString( right.sPtr ); // call utility function
    }

    return *this; // enables concatenated calls
}

// concatenate right operand to this object and store in this object
const String &String::operator+=( const String &right )
{
    size_t newLength = length + right.length; // new length
    char *tempPtr = new char[ newLength + 1 ]; // create memory

    strcpy( tempPtr, sPtr ); // copy sPtr
    strcpy( tempPtr + length, right.sPtr ); // copy right.sPtr

    delete [] sPtr; // reclaim old space
    sPtr = tempPtr; // assign new array to sPtr
    length = newLength; // assign new length to length
    return *this; // enables cascaded calls
}

// is String empty?
bool String::operator!() const
{
    return length == 0;
}

// is this String equal to right String?
bool String::operator==( const String &right ) const
{
    return strcmp( sPtr, right.sPtr ) == 0;
}

// Is this String less than right String?
bool String::operator<( const String &right ) const
{
    return strcmp( sPtr, right.sPtr ) < 0;
}

// return reference to character in String as a modifiable lvalue
char &String::operator[]( int subscript )
{
    // test for subscript out of range
    if ( subscript < 0 || subscript >= length )
    {
        cerr << "Error: Subscript " << subscript
             << " out of range" << endl;
        exit( 1 ); // terminate program
    }

    return sPtr[ subscript ]; // non-const return; modifiable lvalue
}

// return reference to character in String as rvalue
char String::operator[]( int subscript ) const
{
    // test for subscript out of range
    if ( subscript < 0 || subscript >= length )
    {
        cerr << "Error: Subscript " << subscript
             << " out of range" << endl;
        exit( 1 ); // terminate program
    }

    return sPtr[ subscript ]; // returns copy of this element
}

// return a substring starting at index and of length subLength
String String::operator()( int index, int subLength ) const
{
    // if index is out of range or subLength < 0
    if ( index < 0 || index >= length || subLength < 0 )
        return ""; // converted to an empty String

    // determine length of substring
    int len;

    if ( ( subLength == 0 ) || ( index + subLength > length ) )
        len = length - index;
    else
        len = subLength;

    // allocate temporary array for substring
    char *tempPtr = new char[ len + 1 ];

    // copy substring into char array
    strncpy( tempPtr, &sPtr[ index ], len );
    tempPtr[ len ] = '\0';

    // create temporary String object containing the substring
    String tempString( tempPtr );
    delete [] tempPtr; // delete temporary array
    return tempString; // return copy of temporary String
}

// return string length
int String::getLength() const
{
    return length;
}

// utility function called by constructors and operator=
void String::setString( const char *string2 )
{
    sPtr = new char[ length + 1 ]; // allocate memory

    if ( string2 != 0 ) // if string2 is not null pointer
        strcpy( sPtr, string2 ); // copy literal to object
    else // if string2 is a null pointer
        sPtr[ 0 ] = '\0'; // empty string
}

// overloaded output operator
ostream &operator<<( ostream &output, const String &s )
{
    output << s.sPtr;
    return output; // enables cascading
}

// overloaded input operator
istream &operator>>( istream &input, String &s )
{
    char temp[ 100 ]; // buffer to store input
    input >> setw( 100 ) >> temp;
    s = temp; // use String class assignment operator
    return input; // enables cascading
}

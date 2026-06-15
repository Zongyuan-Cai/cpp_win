// Date class test program.
// Demonstrating overloaded ++ operators.

#include <iostream>
#include "Date.h"

using std::cout;
using std::endl;

int main()
{
    Date d1( 12, 27, 2010 ); // December 27, 2010
    Date d2; // defaults to January 1, 1900

    cout << "d1 is " << d1 << "\nd2 is " << d2;
    cout << "\n\nd1 += 7 is " << ( d1 += 7 );

    d2 = d1;
    cout << "\n\n  d2 = d1 = " << d2;
    cout << "\n++d2 = " << ++d2 << " (prefix)";
    cout << "\n  d2 = " << d2;
    cout << "\n\nd2++ = " << d2++ << " (postfix)";
    cout << "\n  d2 = " << d2 << endl;

    return 0;
}

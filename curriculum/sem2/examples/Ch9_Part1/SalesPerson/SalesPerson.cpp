// SalesPerson.cpp
// Member functions for class SalesPerson.
#include <iostream>
#include <iomanip>
#include "SalesPerson.h" // include SalesPerson class definition

using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;

// initialize elements of array sales to 0.0
SalesPerson::SalesPerson()
{
    for ( int i = 0; i < 12; i++ )
        sales[ i ] = 0.0;
}

// get 12 sales figures from the user at the keyboard
void SalesPerson::getSalesFromUser()
{
    double salesFigure;

    for ( int i = 1; i <= 12; i++ )
    {
        cout << "Enter sales amount for month " << i << ": ";
        cin >> salesFigure;
        setSales( i, salesFigure );
    }
}

// set sales for a specific month
void SalesPerson::setSales( int month, double amount )
{
    // test for valid month and amount values
    if ( month >= 1 && month <= 12 && amount > 0 )
        sales[ month - 1 ] = amount; // adjust for subscripts 0-11
    else // invalid month or amount value
        cout << "Invalid month or sales figure" << endl;
}

// print total annual sales (with the help of utility function)
void SalesPerson::printAnnualSales()
{
    cout << setprecision( 2 ) << fixed
         << "\nThe total annual sales are: $"
         << totalAnnualSales() << endl; // call utility function
}

// private utility function to total annual sales
double SalesPerson::totalAnnualSales()
{
    double total = 0.0; // initialize total

    for ( int i = 0; i < 12; i++ ) // summarize sales results
        total += sales[ i ]; // add month i sales to total

    return total;
}

// main.cpp
// Demonstrating class SalesPerson.
#include <iostream>
#include "SalesPerson.h"

using std::cout;
using std::endl;

int main()
{
    SalesPerson s; // create SalesPerson object s

    s.getSalesFromUser(); // note simple sequential code;
    s.printAnnualSales(); // no control statements in main

    return 0;
}

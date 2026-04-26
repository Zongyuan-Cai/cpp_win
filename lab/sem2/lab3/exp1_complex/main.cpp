#include <iostream>
#include "Complex.h"

int main() {
    Complex x;
    Complex y(4.3, 8.2);
    Complex z(3.3, 1.1);
    Complex k;

    std::cout << "Enter a complex number in the form: (a, b)\n? ";
    std::cin >> k;
    if (!std::cin) {
        std::cout << "Input format error. Example: (1, 2)\n";
        return 1;
    }

    std::cout << "x: " << x << "\ny: " << y << "\nz: " << z << "\nk: " << k << '\n';

    x = y + z;
    std::cout << "\nx = y + z:\n" << x << " = " << y << " + " << z << '\n';

    x = y - z;
    std::cout << "\nx = y - z:\n" << x << " = " << y << " - " << z << '\n';

    x = y * z;
    std::cout << "\nx = y * z:\n" << x << " = " << y << " * " << z << "\n\n";

    if (x != k) {
        std::cout << x << " != " << k << '\n';
    }

    std::cout << '\n';
    x = k;

    if (x == k) {
        std::cout << x << " == " << k << '\n';
    }

    return 0;
}

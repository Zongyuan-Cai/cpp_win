#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
    friend std::ostream &operator<<(std::ostream &output, const Complex &c);
    friend std::istream &operator>>(std::istream &input, Complex &c);

public:
    Complex(double real = 0.0, double imaginary = 0.0);

    Complex operator+(const Complex &rhs) const;
    Complex operator-(const Complex &rhs) const;
    Complex operator*(const Complex &rhs) const;

    bool operator==(const Complex &rhs) const;
    bool operator!=(const Complex &rhs) const;

private:
    double realPart;
    double imaginaryPart;
};

#endif

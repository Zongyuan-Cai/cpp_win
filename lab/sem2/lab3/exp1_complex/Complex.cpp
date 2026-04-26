#include "Complex.h"

Complex::Complex(double real, double imaginary)
    : realPart(real), imaginaryPart(imaginary) {
}

Complex Complex::operator+(const Complex &rhs) const {
    double resultReal = realPart + rhs.realPart;
    double resultImag = imaginaryPart + rhs.imaginaryPart;
    return Complex(resultReal, resultImag);
}

Complex Complex::operator-(const Complex &rhs) const {
    double resultReal = realPart - rhs.realPart;
    double resultImag = imaginaryPart - rhs.imaginaryPart;
    return Complex(resultReal, resultImag);
}

Complex Complex::operator*(const Complex &rhs) const {
    double resultReal = realPart * rhs.realPart - imaginaryPart * rhs.imaginaryPart;
    double resultImag = realPart * rhs.imaginaryPart + imaginaryPart * rhs.realPart;
    return Complex(resultReal, resultImag);
}

bool Complex::operator==(const Complex &rhs) const {
    return realPart == rhs.realPart && imaginaryPart == rhs.imaginaryPart;
}

bool Complex::operator!=(const Complex &rhs) const {
    return !(*this == rhs);
}

std::ostream &operator<<(std::ostream &output, const Complex &c) {
    output << '(' << c.realPart << ", " << c.imaginaryPart << ')';
    return output;
}

std::istream &operator>>(std::istream &input, Complex &c) {
    char left = 0;
    char comma = 0;
    char right = 0;
    double real = 0.0;
    double imag = 0.0;

    input >> left >> real >> comma >> imag >> right;
    if (input && left == '(' && comma == ',' && right == ')') {
        c.realPart = real;
        c.imaginaryPart = imag;
    } else {
        input.setstate(std::ios::failbit);
    }

    return input;
}

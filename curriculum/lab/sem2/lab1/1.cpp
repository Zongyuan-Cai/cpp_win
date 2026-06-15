#include <iostream>
using namespace std;

class Complex {
private:
    double realPart;
    double imaginaryPart;

public:
    Complex(double r = 0.0, double i = 0.0) : realPart(r), imaginaryPart(i) {}

    Complex add(const Complex& other) const {
        return Complex(realPart + other.realPart, imaginaryPart + other.imaginaryPart);
    }

    Complex subtract(const Complex& other) const {
        return Complex(realPart - other.realPart, imaginaryPart - other.imaginaryPart);
    }

    void print() const {
        cout << "<" << realPart << ", " << imaginaryPart << ">";
    }
};

int main() {
    Complex c1(1, 7), c2(9, 2);
    c1.print();
    cout << " + ";
    c2.print();
    cout << " = ";
    c1.add(c2).print();
    cout << endl;

    Complex c3(10, 1), c4(11, 5);
    c3.print();
    cout << " - ";
    c4.print();
    cout << " = ";
    c3.subtract(c4).print();
    cout << endl;

    return 0;
}

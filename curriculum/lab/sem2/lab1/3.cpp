#include <iostream>
#include <iomanip>
#include <numeric>
using namespace std;

class Rational {
private:
    int numerator;
    int denominator;

    void reduce() {
        if (denominator == 0) return;
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Rational(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) denominator = 1;
        reduce();
    }

    Rational add(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational subtract(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational multiply(const Rational& other) const {
        return Rational(numerator * other.numerator, denominator * other.denominator);
    }

    Rational divide(const Rational& other) const {
        if (other.numerator == 0) return *this;
        return Rational(numerator * other.denominator, denominator * other.numerator);
    }

    void printFraction() const {
        cout << numerator << "/" << denominator;
    }

    void printFloat() const {
        if (denominator == 0) cout << "Invalid";
        else cout << static_cast<double>(numerator) / denominator;
    }
};

int main() {
    Rational r1(1, 3), r2(7, 8);
    cout << fixed << setprecision(6);

    cout << "1/3 + 7/8 = ";
    r1.add(r2).printFraction();
    cout << endl;
    r1.add(r2).printFloat();
    cout << endl;

    cout << "1/3 - 7/8 = ";
    r1.subtract(r2).printFraction();
    cout << endl;
    r1.subtract(r2).printFloat();
    cout << endl;

    cout << "1/3 x 7/8 = ";
    r1.multiply(r2).printFraction();
    cout << endl;
    r1.multiply(r2).printFloat();
    cout << endl;

    cout << "1/3 / 7/8 = ";
    r1.divide(r2).printFraction();
    cout << endl;
    r1.divide(r2).printFloat();
    cout << endl;

    return 0;
}

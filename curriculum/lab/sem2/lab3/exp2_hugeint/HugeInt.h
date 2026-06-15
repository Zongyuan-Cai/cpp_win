#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>

class HugeInt {
    friend std::ostream &operator<<(std::ostream &output, const HugeInt &num);

public:
    HugeInt(long value = 0);
    HugeInt(const char *value);

    HugeInt operator+(const HugeInt &rhs) const;
    HugeInt operator+(int rhs) const;
    HugeInt operator+(const char *rhs) const;

    bool operator==(const HugeInt &rhs) const;
    bool operator!=(const HugeInt &rhs) const;
    bool operator<(const HugeInt &rhs) const;
    bool operator<=(const HugeInt &rhs) const;
    bool operator>(const HugeInt &rhs) const;
    bool operator>=(const HugeInt &rhs) const;

    HugeInt operator-(const HugeInt &rhs) const;
    HugeInt operator*(const HugeInt &rhs) const;
    HugeInt operator/(const HugeInt &rhs) const;

    int getLength() const;

private:
    short integer[30];

    void clear();
    bool isZero() const;
    int compare(const HugeInt &rhs) const;
};

#endif

#include "HugeInt.h"

#include <cctype>
#include <cstring>

HugeInt::HugeInt(long value) {
    clear();

    if (value < 0) {
        value = 0;
    }

    for (int i = 29; i >= 0 && value > 0; --i) {
        integer[i] = static_cast<short>(value % 10);
        value /= 10;
    }
}

HugeInt::HugeInt(const char *value) {
    clear();

    if (value == nullptr) {
        return;
    }

    int len = static_cast<int>(std::strlen(value));
    int digitIndex = 29;

    for (int i = len - 1; i >= 0 && digitIndex >= 0; --i) {
        if (std::isdigit(static_cast<unsigned char>(value[i])) != 0) {
            integer[digitIndex] = static_cast<short>(value[i] - '0');
            --digitIndex;
        }
    }
}

HugeInt HugeInt::operator+(const HugeInt &rhs) const {
    HugeInt result;
    int carry = 0;

    for (int i = 29; i >= 0; --i) {
        int sum = integer[i] + rhs.integer[i] + carry;
        result.integer[i] = static_cast<short>(sum % 10);
        carry = sum / 10;
    }

    return result;
}

HugeInt HugeInt::operator+(int rhs) const {
    return *this + HugeInt(rhs);
}

HugeInt HugeInt::operator+(const char *rhs) const {
    return *this + HugeInt(rhs);
}

bool HugeInt::operator==(const HugeInt &rhs) const {
    return compare(rhs) == 0;
}

bool HugeInt::operator!=(const HugeInt &rhs) const {
    return compare(rhs) != 0;
}

bool HugeInt::operator<(const HugeInt &rhs) const {
    return compare(rhs) < 0;
}

bool HugeInt::operator<=(const HugeInt &rhs) const {
    return compare(rhs) <= 0;
}

bool HugeInt::operator>(const HugeInt &rhs) const {
    return compare(rhs) > 0;
}

bool HugeInt::operator>=(const HugeInt &rhs) const {
    return compare(rhs) >= 0;
}

HugeInt HugeInt::operator-(const HugeInt &rhs) const {
    if (*this < rhs) {
        return HugeInt(0L);
    }

    HugeInt result;
    int borrow = 0;

    for (int i = 29; i >= 0; --i) {
        int diff = integer[i] - rhs.integer[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.integer[i] = static_cast<short>(diff);
    }

    return result;
}

HugeInt HugeInt::operator*(const HugeInt &rhs) const {
    HugeInt result;

    for (int i = 29; i >= 0; --i) {
        int carry = 0;

        for (int j = 29; j >= 0; --j) {
            int pos = i + j - 29;
            if (pos < 0) {
                break;
            }

            int value = result.integer[pos] + integer[i] * rhs.integer[j] + carry;
            result.integer[pos] = static_cast<short>(value % 10);
            carry = value / 10;
        }

        int carryPos = i - 1;
        while (carry > 0 && carryPos >= 0) {
            int value = result.integer[carryPos] + carry;
            result.integer[carryPos] = static_cast<short>(value % 10);
            carry = value / 10;
            --carryPos;
        }
    }

    return result;
}

HugeInt HugeInt::operator/(const HugeInt &rhs) const {
    HugeInt zero(0L);
    if (rhs == zero) {
        return zero;
    }

    HugeInt quotient;
    HugeInt remainder;

    for (int i = 0; i < 30; ++i) {
        for (int k = 0; k < 29; ++k) {
            remainder.integer[k] = remainder.integer[k + 1];
        }
        remainder.integer[29] = integer[i];

        short digit = 0;
        while (remainder >= rhs) {
            remainder = remainder - rhs;
            ++digit;
        }

        quotient.integer[i] = digit;
    }

    return quotient;
}

int HugeInt::getLength() const {
    for (int i = 0; i < 30; ++i) {
        if (integer[i] != 0) {
            return 30 - i;
        }
    }
    return 1;
}

void HugeInt::clear() {
    for (int i = 0; i < 30; ++i) {
        integer[i] = 0;
    }
}

bool HugeInt::isZero() const {
    for (int i = 0; i < 30; ++i) {
        if (integer[i] != 0) {
            return false;
        }
    }
    return true;
}

int HugeInt::compare(const HugeInt &rhs) const {
    for (int i = 0; i < 30; ++i) {
        if (integer[i] < rhs.integer[i]) {
            return -1;
        }
        if (integer[i] > rhs.integer[i]) {
            return 1;
        }
    }
    return 0;
}

std::ostream &operator<<(std::ostream &output, const HugeInt &num) {
    bool printed = false;

    for (int i = 0; i < 30; ++i) {
        if (num.integer[i] != 0) {
            printed = true;
        }

        if (printed) {
            output << num.integer[i];
        }
    }

    if (!printed) {
        output << 0;
    }

    return output;
}

#include "String.h"

#include <cassert>
#include <cstring>

String::String(const char *const value) {
    length = static_cast<int>(std::strlen(value));
    sPtr = new char[length + 1];
    assert(sPtr != nullptr);
    std::strcpy(sPtr, value);
}

String::String(const String &other) {
    length = other.length;
    sPtr = new char[length + 1];
    assert(sPtr != nullptr);
    std::strcpy(sPtr, other.sPtr);
}

String::~String() {
    delete[] sPtr;
}

const String &String::operator=(const String &rhs) {
    if (this != &rhs) {
        delete[] sPtr;

        length = rhs.length;
        sPtr = new char[length + 1];
        assert(sPtr != nullptr);
        std::strcpy(sPtr, rhs.sPtr);
    }

    return *this;
}

String String::operator+(const String &rhs) {
    int newLength = length + rhs.length;
    char *temp = new char[newLength + 1];
    assert(temp != nullptr);

    std::strcpy(temp, sPtr);
    std::strcat(temp, rhs.sPtr);

    String result(temp);
    delete[] temp;

    return result;
}

std::ostream &operator<<(std::ostream &output, const String &s) {
    output << s.sPtr;
    return output;
}

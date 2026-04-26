#ifndef STRING_H
#define STRING_H

#include <iostream>

class String {
    friend std::ostream &operator<<(std::ostream &output, const String &s);

public:
    String(const char *const value = "");
    String(const String &other);
    ~String();

    const String &operator=(const String &rhs);
    String operator+(const String &rhs);

private:
    char *sPtr;
    int length;
};

#endif

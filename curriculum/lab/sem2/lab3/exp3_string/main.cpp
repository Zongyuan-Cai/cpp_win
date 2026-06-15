#include <iostream>

#include "String.h"

int main() {
    String string1;
    String string2("The date is");
    String string3(" August 1, 1993");

    std::cout << "string1 = string2 + string3\n";
    string1 = string2 + string3;

    std::cout << "\"" << string1 << "\" = \"" << string2 << "\" + \""
              << string3 << "\"" << std::endl;

    return 0;
}

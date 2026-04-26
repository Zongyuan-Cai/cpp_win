#include <iostream>
#include "HugeInt.h"

int main() {
    HugeInt n1(7654321);
    HugeInt n2("99999999999999999999999999999");
    HugeInt n3("123456789123456789");
    HugeInt n4("1000000000000");

    std::cout << "===== Original Values =====\n";
    std::cout << "n1 = " << n1 << '\n';
    std::cout << "n2 = " << n2 << '\n';
    std::cout << "n3 = " << n3 << '\n';
    std::cout << "n4 = " << n4 << "\n\n";

    std::cout << "===== Arithmetic Operators =====\n";
    std::cout << "n1 + n3 = " << (n1 + n3) << '\n';
    std::cout << "n2 - n4 = " << (n2 - n4) << '\n';
    std::cout << "n3 * n4 = " << (n3 * n4) << '\n';
    std::cout << "n2 / n4 = " << (n2 / n4) << "\n\n";

    std::cout << "===== Relational Operators =====\n";
    std::cout << std::boolalpha;
    std::cout << "n1 == n3 : " << (n1 == n3) << '\n';
    std::cout << "n1 != n3 : " << (n1 != n3) << '\n';
    std::cout << "n1 <  n3 : " << (n1 < n3) << '\n';
    std::cout << "n1 <= n3 : " << (n1 <= n3) << '\n';
    std::cout << "n2 >  n4 : " << (n2 > n4) << '\n';
    std::cout << "n2 >= n4 : " << (n2 >= n4) << '\n';

    return 0;
}

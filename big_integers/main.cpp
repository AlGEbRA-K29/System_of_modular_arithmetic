#include "bigint.h"

int main() {
    bigint a = 1000000000000123456789000000000_BI;
    bigint b = 1000_BI;
    bigint c = a * b;
    bigint d = c * c;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << a / b << std::endl;

    bigint x = 129_BI;
    bigint y = 7_BI;
    bigint i = modInverse(x, y);
    std::cout << i << std::endl;
    return 0;
}
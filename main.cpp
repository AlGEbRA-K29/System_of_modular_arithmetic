#include <iostream>
#include "bigint.h"
#include "helpers.h"

int main() {
    bigint bb1 = 0xAAAAAAAA;
    bigint bb2 = bb1 * bb1;
    bigint bb3 = bb2 * bb2;
    bigint bb4 = bb3 * bb3;
    bigint bb5 = bb4 * bb4;

    std::cout << bb1 << std::endl;
    std::cout << bb2 << std::endl;
    std::cout << bb3 << std::endl;
    std::cout << bb4 << std::endl;
    return 0;
}

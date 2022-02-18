#include <iostream>
#include "bigint.h"
#include "helpers.h"

int main() {
    bigint bb1 = 10000;

    for(int i = 0; i < 4; ++i) {
        bb1 = bb1 * bb1;
    }

    std::cout << bb1 << std::endl;

    return 0;
}

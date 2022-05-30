#include <iostream>
#include "big_integers\bigint.h"



[[nodiscard]] bigint find_sqrt(bigint n) const {
        bigint result = 0;
        bigint guess = *n;


        while(guess != result) {
            result = guess;
            guess = (result + *n / result) / 2;
        }

        return result;
    }

int main() {
    bigint a = new bigint(169);
    a = find_sqrt(a);
    std::cout << a;
    return 0;
}

#pragma once
#include "big_integers/bigint.h"
#include "big_integers/mod_bigint.h"

bigint order_gcd(bigint a, bigint b) {
    if (a + 1 == 1)
        return b;
    if (b + 1 == 1)
        return a;

    if (a == b)
        return a;

    if (a > b)
        return order_gcd(a - b, b);
    return order_gcd(a, b - a);
}

bigint find_order(const bigint& n, const bigint& a) {
    bigint zero = 0;
    bigint one = 1;

    if (!(order_gcd(a, n) == one)) {
        return zero;
    }
    bigint res = 1;
    bigint k = 1;
    while (n > k) {

        res = modular_product(res, a, n);;
        if (res == one) {
            return k;
        }
        k = modular_add(k, one, n);
    }

    return zero;

}

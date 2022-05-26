#pragma once
#include "big_integers/bigint.h"
#include "big_integers/mod_bigint.h"

bigint order_gcd(bigint a, bigint b) ;

bigint find_order(const bigint& n, const bigint& a);

#pragma once
#include "big_integers/bigint.h"
#include<vector>
#include<string>
#include <cmath>
using namespace std;


bigint inverse(bigint a, bigint m);

bigint power(bigint x,  bigint y,  bigint m);

bigint inverse_gcd(bigint a, bigint b);

bigint modInverse(bigint a, bigint m);

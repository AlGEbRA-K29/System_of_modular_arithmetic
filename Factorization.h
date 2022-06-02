#pragma once
#include <iostream>
#include <numeric>
#include <math.h>
#include <ctime>
#include <vector>
#include "big_integers/bigint.h"


[[nodiscard]] std::vector<bigint> naiveAlgorithm(bigint to_factorize);

bigint gcd_f(bigint a, bigint b);

bigint PollardRho(bigint n);

bool isPrime(bigint n);

void PrintFactors(bigint n, std::vector<bigint> factors);

[[nodiscard]] std::vector<bigint> factorize(bigint n, std::vector<bigint> factors);

[[nodiscard]] std::vector<bigint> Factorization(bigint n, bool isToUsePollard = false);

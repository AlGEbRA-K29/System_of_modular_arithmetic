#pragma once
#pragma once
#include "big_integers/bigint.h"
#include "montgomery_form.h"
#include "Factorization.h"
#include <map>

bool isPrimeCheck(bigint number);

bigint my_gcd_for_finding_order(bigint a, bigint b);

bigint mod_power(const bigint& a, const bigint& b, const bigint& n);


bigint phi(const bigint& n0);


bigint find_order(bigint a, bigint n);

bool isGenerator(bigint a, bigint n, bool checked = 0);

#pragma once
#include <iostream>
#include <numeric>
#include <math.h>
#include <ctime>
#include <vector>
#include "big_integers/bigint.h"


[[nodiscard]] std::vector<bigint> naiveAlgorithm(bigint to_factorize) {
	if (to_factorize < 2_BI) {
		return {};
	}

	std::vector<bigint> result;

	while (to_factorize % 2_BI == 0_BI) {
		result.push_back(2_BI);
		to_factorize /= 2_BI;
	}

	bigint cur_divisor = 3_BI;

	while (cur_divisor * cur_divisor <= to_factorize) {
		if (to_factorize % cur_divisor == 0) {
			result.push_back(cur_divisor);
			to_factorize /= cur_divisor;
		}
		else {
			cur_divisor += 2_BI;
		}
	}

	if (to_factorize != 1_BI) {
		result.push_back(to_factorize);
	}

	return result;
}

bigint gcd_f(bigint a, bigint b) {
	if (a == 0_BI)
		return b;
	if (b == 0_BI)
		return a;

	if (a == b)
		return a;

	if (a > b)
		return gcd_f(a - b, b);
	return gcd_f(a, b - a);
}


bigint PollardRho(bigint n)
{
	srand(std::time(NULL));

	if (n == 1_BI) return n;

	if (n % 2 == 0_BI) return 2_BI;


	bigint x = (bigint(rand()+1) % (n - 2_BI)) + 2_BI;
	bigint y = x;

	bigint c = (bigint(rand()+1) % (n - 1_BI)) + 1_BI;

	bigint d = 1_BI;


	while (d == 1_BI)
	{
		if (x == 0_BI) {
			x = (c + n) % n;
		}
		else {
			x = (((x*x) % n) + c + n) % n;
		}

		if (y == 0_BI) {
			y = (c + n) % n;
		}
		else {
			y = (((y*y) % n) + c + n) % n;
		}


		if (y == 0_BI) {
			y = (c + n) % n;
		}
		else {
			y = (((y*y) % n) + c + n) % n;
		}

		if (x == 0_BI && y == 0_BI) {
			d = n;
		}
		else {
			d = gcd_f((x - y).abs(), n);
		}


		if (d == n) return PollardRho(n);
	}
	return d;
}

bool isPrime(bigint n)
{
	if (n <= 1_BI)
		return false;
	if (n <= 3_BI) {
		return true;
	}

	if (n % 2 == 0_BI || n % 3 == 0_BI)
		return false;

	for (int i = 5; bigint(i * i) <= n; i = i + 6)
		if (n % i == 0_BI || n % (i + 2) == 0_BI)
			return false;
	return true;

}

void PrintFactors(bigint n, std::vector<bigint> factors) {
	bool is_first = true;
	std::cout << n << " = ";
	for (const bigint& factor : factors) {
		if (!is_first) {
			std::cout << " * ";
		}
		std::cout << factor;
		is_first = false;
	}
	std::cout << "\n";
}

[[nodiscard]] std::vector<bigint> factorize(bigint n, std::vector<bigint> factors)
{
	if (n == 1_BI)
		return factors;
	if (isPrime(n))
	{
		factors.push_back(n);
		return factors;
	}

	bigint divisor = PollardRho(n);
	factors = factorize(divisor, factors);
	factors = factorize(n / divisor, factors);
	return factors;
}

[[nodiscard]] std::vector<bigint> Factorization(bigint n, bool isToUsePollard = false) {
	if (n <= 1_BI) {
		std::vector<bigint> factors;
		factors.push_back(n);
		return factors;
	}
	if (isToUsePollard) {
		std::vector<bigint> factors;
		return factorize(n, factors);
	}
	else {
		return naiveAlgorithm(n);
	}
}

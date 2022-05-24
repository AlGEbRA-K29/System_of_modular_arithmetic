#include "stdafx.h"
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
    bigint cur_divisor = 2_BI;

    while (to_factorize != 1_BI) {
        if (to_factorize % cur_divisor == 0_BI) {
            result.push_back(cur_divisor);
            to_factorize /= cur_divisor;
        }
        else {
            ++cur_divisor;
        }
    }

    return result;
}

bigint gcd(bigint a, bigint b) {
	if (a+1 == 1)
		return b;
	if (b+1 == 1)
		return a;

	if (a == b)
		return a;

	if (a > b)
		return gcd(a - b, b);
	return gcd(a, b - a);
}


bigint PollardRho(bigint n)
{
	srand(std::time(NULL));

	if (n == 1) return n;

	if (n % 2 + 1 == 1) return 2;

	bigint x = (bigint(rand()) % (n - 2)) + 2;
	bigint y = x;

	bigint c = (bigint(rand()) % (n - 1)) + 1;

	bigint d = 1;

	while (d == 1)
	{
		x = ((x*x%n) + c + n) % n;

		y = ((y*y%n) + c + n) % n;
		y = ((y*y%n) + c + n) % n;

		if (!(x - y).isPositive()) {
			d = gcd(bigint(-1)*(x - y), n);
			
		}
		else {
			d = gcd((x - y), n);
		}
		if (d == n) return PollardRho(n);
	}
	return d;
}

bool isPrime(bigint n)
{
		if (n <= 1)
			return false;
		if (n <= 3) {
			return true;
		}
			
		if (n % 2 + 1 == 1 || n % 3 + 1 == 1)
			return false;

		for (int i = 5; bigint(i * i) <= n; i = i + 6)
			if (n % i + 1 == 1 || n % (i + 2) + 1 == 1)
				return false;

		return true;
	
}

std::vector<bigint> factors;

void factorize(bigint n)  
{
	if (n == 1)
		return;
	if (isPrime(n))      
	{
		factors.push_back(n);
		return;
	}
	bigint divisor = PollardRho(n);
	factorize(divisor);
	factorize(n / divisor);
}


int main()
{
	std::cout << "Enter number\n";

	bigint n;
	std::cin >> n;

	bool use_pollard;
	std::cout << "Enter method(0 - Naive, 1 - Pollard)\n";
	std::cin >> use_pollard;

	if (use_pollard) {
		if (isPrime(n)) {
			std::cout << "Number " << n << " is prime\n";
		}
		else {
			factorize(n);
			std::cout << n << " = ";
			for (int i = 0; i < factors.size(); i++) {
				std::cout << factors[i];
				if (i < factors.size() - 1) {
					std::cout << " * ";
				}
			}
			std::cout << "\n";
		}
	}
	else {
		auto res = naiveAlgorithm(n);
		bool is_first = true;

		std::cout << n << " = ";

		for (const bigint& factor : res) {
			if (!is_first) {
				std::cout << " * ";
			}
			std::cout << factor;
			is_first = false;
		}
	}

	return 0;
}

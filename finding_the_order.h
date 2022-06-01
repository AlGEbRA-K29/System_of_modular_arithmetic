#pragma once
#pragma once
#include "big_integers/bigint.h"
#include "montgomery_form.h"
#include "factorization.h"

bool isPrimeCheck(bigint number) {
	if (number <= 1)  return false;
	if (number <= 3)  return true;
	for (bigint i = 5; i * i <= number; i++)
	{
		if ((number % i).isZero()) {
			return false;
		}
	}
	return true;
}

bigint my_gcd_for_finding_order(bigint a, bigint b) {
	if (b.isZero())
		return a;
	return my_gcd_for_finding_order(b, a % b);
}

bigint mod_power(const bigint& a, const bigint& b, const bigint& n) {
	bigint x = a;
	bigint y = b;
	bigint p = 1;
	while (y > bigint(0)) {

		while ((y % 2).isZero()) {
			y = y / 2;
			x = (x * x) % n;
			if (y.isZero())
			{
				break;
			}
		}
		y = y - 1;
		p = (p * x) % n;
		if (y.isZero())
		{
			break;
		}

	}
	return p;
}


bigint phi(const bigint& n0) {
	bigint n = bigint(n0);
	bigint result = bigint(n);
	for (bigint i = 2; i * i <= n; i++) {
		if ((n % i).isZero()) {
			while ((n % i).isZero()) {
				n /= i;
			}
			result -= (result / i);
			//std::cout << i << " " << " " << result << " t \n";

		}
	}
	//std::cout <<result<<" n = "<< n << " n \n";
	if (!(n.isZero() || n.isOne()))
		result -= (result / n);
	return result;
}


bigint find_order(bigint a, bigint n) {

	if (a == bigint(0) || a < bigint(0) || a >= n) {
		return bigint(0);
	}
	if (!my_gcd_for_finding_order(a, n).isOne())
	{
		return bigint(0);
	}
	bigint phiN;

	phiN = phi(n);

	std::vector<bigint> dividers = Factorization(phiN, 1);
	std::map<bigint, int> powers;
	for (int i = 0; i < dividers.size(); i++)
	{
		powers[dividers[i]]++;
	}
	bigint t = phiN;
	bigint a1 = 1;
	for (const auto& p : powers) {
		t = t / p.first.pow(p.second);
		a1 = mod_power(a, t, n);
		while (a1 != 1) {
			a1 = mod_power(a1, p.first, n);
			t = (t * p.first);

		}
	}
	return t;
}

bool isGenerator(bigint a, bigint n, bool checked = 0) {

	if (isPrime(n) && find_order(a, n) == n - 1)
	{
		return true;
	}
	return false;
}

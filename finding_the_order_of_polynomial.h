#pragma once
#include "bigint.h"
#include "montgomery_form.h"


bool isPrimeCheck(bigint number) {
	if (number <= 1)  return false;
	if (number <= 3)  return true;
	for (bigint i = 5; i * i <= number; i++)
	{
		if (number % i == bigint(0)) {
			return false;
		}
	}
	return true;
}

bigint my_gcd_for_finding_order(bigint a, bigint b) {
	if (b == bigint(0))
		return a;
	return my_gcd_for_finding_order(b, a % b);
}

bool isGenerator(bigint a, bigint n) {
	if (a == bigint(0) || a < bigint(0) || a >= n || !isPrimeCheck(n)) {
		return false;
	}
	montgomery mont1(a, n);
	montgomery mont3 = mont1 ^ n;
	bigint res = mont3.convertToStandartForm(mont3.getmontgform());
	if (res == bigint(1))
	{
		return true;
	}
	return false;
}
bigint find_order_not_for_prime(bigint a, bigint n) {

	if (a == bigint(0) || a < bigint(0) || a >= n) {
		return bigint(0);
	}

	bigint res = 1;
	bigint k = 1;
	while (n > k) {

		res = (res * a) % n;
		if (res == bigint(1)) {
			return k;
		}
		k++;
	}
	return 0;
}
bigint find_order(bigint a, bigint n) {
	if (a == bigint(0) || a < bigint(0) || a >= n) {
		return bigint(0);
	}

	if (!isPrimeCheck(n)) {
		return find_order_not_for_prime(a, n);
	}
	if (isGenerator(a, n)) {
		return n - 1;
	}
	/*if ((my_gcd_for_finding_order(a, n) == bigint(1))) {
		return bigint(0);
	}*/
	bigint maxL = n.sqrt();
	for (bigint i = maxL; i >= 1; i--)
	{
		if ((n - 1) % i == 0) {
			std::cout << i << "\n";
			montgomery num(a, n);
			montgomery res1 = num ^ ((n - 1) / i);
			montgomery res2 = num ^ (i);

			if (res1.convertToStandartForm(res1.getmontgform()) == 1)
			{
				return ((n - 1) / i);
			}
			if (i != 1 && res2.convertToStandartForm(res2.getmontgform()) == 1)
			{
				return i;
			}
		}
	}
	return bigint(1);
}


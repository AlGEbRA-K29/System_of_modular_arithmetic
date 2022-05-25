#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <cstdlib>
#include "BigInteger.h"
#include "doctest.h"


bool MillerRabin_Test(bigint t, bigint n) {
	//choose a random integer a in the interval[2, n − 2]
	bigint a = 2 + rand() % (n - 2);


	//x ← a^ t mod n
	//the function was additionally written for the class
	bigint x = pow(a, t, n);
	if (x == 1 || x == n - 1)
		return true;

	//keep squaring x while one of the following doesn't 
	 // happen 
	 // t does not reach n-1 
	 // (x^2) % n is not 1 
	 // (x^2) % n is not n-1 
	while (t != n - 1) {
		x = (x * x) % n;
		t = t * 2;

		if (x == 1) return false;
		if (x == n - 1) return true;
	}
	return false;
}

bool isPrime(bigint n, int k) {
	//corner cases 
	if (n == 2 || n == 3)
		return true;
	//if n<2 or n is even - return false
	if (n < 2 || n % 2 == 0)
		return false;


	// represent n − 1 as (2^s) t, where t is odd, this can be done by successively dividing n - 1 by 2
	bigint t = n - 1;
	while (t % 2 == 0)
		t = t / 2;

	//Since the test does not give an exact understanding of whether a number is prime, we use a k times loop. (recomended to use log_2(n))

	for (int i = 0; i < k; i++)
		if (!MillerRabin_Test(t, n))
			return false;

	return true;

}

TEST_CASE("primality check") {
	CHECK(isPrime(1709,2)== true); 
	CHECK(isPrime(2539, 2) == true);
	CHECK(isPrime(2833, 2) == true);
	CHECK(isPrime(2834, 2) == false);
    CHECK(isPrime(7057, 2) == true);
	CHECK(isPrime(22189, 2) == true);
	CHECK(isPrime(4398042316799, 2) == true);
	CHECK(isPrime(18014398241046527, 2) == true);
	CHECK(isPrime(4398042316799, 2) == true);
	CHECK(isPrime(99194853094755497, 2) == true);	
	
}

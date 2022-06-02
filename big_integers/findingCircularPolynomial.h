#pragma once
#include"polynomial_field.h"
#include"polynoms_divide_remainder_gcd.h"
#include"polynomial_ring.h"
#include<vector>
#include<string>
#include <cmath>
using namespace std;
vector<int> findDividers(int n) {
	vector<int> dividers;
	for (int i = 1; i <= n; i++) {
		if (n % i == 0) {
			dividers.push_back(i);
		}
	}
	return dividers;
}

bool prime(int n) {
	if (n == 1) { return false; }
	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

bool checkForFreeFromSquares(int a) {
	for (int i = 2; i < a; i++) {
		if (prime(i)) {
			int k = i * i;
			if (a % k == 0) { return false; }
		}
	}

	return true;
}

int countPrimeDividers(int n) {
	int k=0;
	for (int i = 1; i <= n; i++) {
		if (prime(i) && n % i == 0) {
			k++;
		}
	}
	return k;
}

int Mobiusfunction(int d) {
	int mobiusfunction;
	if (d == 1) { return 1; }
	if (!checkForFreeFromSquares(d)) {
		mobiusfunction = 0;
	}
	if (checkForFreeFromSquares(d)) {
		mobiusfunction = pow(-1, countPrimeDividers(d));
	}

	return mobiusfunction;
}


polynomial_ring CircularPolynom(int n, int primeCP) {
	if (!prime(primeCP)) { return polynomial_ring("0", primeCP); }
	if (prime(n)) { return polynomial_ring(vector<bigint>(n, 1), primeCP); }
	vector<int> dividers = findDividers(n);
	polynomial_ring res("1", primeCP);
	polynomial_ring denominatorCP("1", primeCP);
	for (auto d : dividers) {
		auto str = "1*x^" + to_string(n / d) + "-1";
		polynomial_ring curr(str, primeCP);
		if (Mobiusfunction(d) == 1) {
			res = res * curr;
		}

		if (Mobiusfunction(d) == -1) {
			denominatorCP = denominatorCP * curr;
		}
	}

	res.divide(res, denominatorCP);
	return res;
}



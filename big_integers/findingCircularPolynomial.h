#pragma once
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
	if (!prime(primeCP)) { return polynomial_ring("0", 2); }

	int m = n / 2;
	vector<bigint> keys{ 1 };
	polynomial_ring res(keys, primeCP);
	if (n % 2 == 0 && prime(m) && m % 2 != 0 && m != 1) {

			vector<bigint> keys(m, 1);
			for (int i = 0; i < m; i++) {
				if (i % 2 != 0)
					keys[i] = -1;
			}
			return polynomial_ring(keys, primeCP);

	}

	else {
		if (prime(n)) { return polynomial_ring(vector<bigint>(n, 1), primeCP); }

		for (int d = 1; d <= n; d++) {
			if (n % d == 0 && Mobiusfunction(n / d) == 1) {
				vector<bigint> keys(d + 1, 0);
				keys[d] = 1;
				keys[0] = -1;
				polynomial_ring mult(keys, primeCP);
				res = res * mult;
			}
		}
		for (int d = 1; d <= n; d++) {
			if (n % d == 0 && Mobiusfunction(n / d) == -1) {
				vector<bigint> keys(d + 1, 0);
				keys[d] = 1;
				keys[0] = -1;
				polynomial_ring div(keys, primeCP);
				res.divide(res, div);
			}
		}
	}

	return res;
}

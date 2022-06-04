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

	// якщо n просте
	if (prime(n)) { return polynomial_ring(vector<bigint>(n, 1), primeCP); }

	//якщо n-степінь двійки
	int test_n = n;
	int deg = 0;
	while (test_n % 2 == 0) {
		deg++;
		test_n = test_n / 2;
		if (test_n == 2) {
			deg++;
			int power = pow(2, deg - 1);
			auto str = "x^" + to_string(power) + "+1";
			return polynomial_ring(str, primeCP);
			break;
		}
	}
	// загальний випадок
	vector<int> dividers = findDividers(n);
	polynomial_ring res("1", primeCP);
	polynomial_ring denominatorCP("1", primeCP);
	polynomial_ring numeratorCP("1", primeCP);
	for (auto d : dividers) {
		auto str = "x^" + to_string(n / d) + "-1";
		polynomial_ring curr(str, primeCP);
		if (Mobiusfunction(d) == 1) {
			numeratorCP = numeratorCP * curr;
			//cout << "numerator: " << curr << endl;
		}

		if (Mobiusfunction(d) == -1) {
			denominatorCP = denominatorCP * curr;
			//cout << "denominato: " << curr << endl;
		}
	}
	cout << "numerator: " << numeratorCP << endl;
	cout << "denominator: " << denominatorCP << endl;
	// умножение работает не правильно 

	res = numeratorCP.divide(numeratorCP, denominatorCP);
	return res;
}



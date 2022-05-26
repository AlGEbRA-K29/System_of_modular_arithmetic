#pragma once
#include"polynomial.h"
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


polynomial findCircularPolynomial(int n) {
	vector<int> dividers = findDividers(n);
	polynomial output("1_BI");
	for (auto value : dividers)
	{
		auto str = "1*x^" + to_string(n/value) + "-1";
		polynomial p(str);
		int mobiusfunction = Mobiusfunction(value);

		if(mobiusfunction==1){ output = output * p;
		}
		if(mobiusfunction==-1){output = output / p;
			
		}
		
	}

	return output;
}
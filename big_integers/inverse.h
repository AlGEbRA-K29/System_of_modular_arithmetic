#pragma once
#include"bigintM.h"
#include<vector>
#include<string>
#include <cmath>
using namespace std;



bigint inverse(bigint a, bigint m) {
	if (a % m == 0_BI || m % a == 0_BI) { cout << "There is no modular multiplicative inverse for this integer" << endl; return 0_BI; }
	if (a == 1_BI) { return a; }
	a = a % m;
	bigint x = 1_BI;
	while (x<m)
	{
		if((a * x) % m == 1_BI){ return x; }
		x += 1_BI;
	}

	//return 0_BI;
}




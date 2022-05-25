#pragma once
#include"bigint.h"
#include<vector>
#include<string>
#include <cmath>



bigint inverse(bigint a, bigint m) {
	if (a == 1_BI) { return a; }
	bigint x = 1_BI;
	while (x<m)
	{
		if(((a % m) * (x % m)) % m == 1_BI){ return x; }

		x += 1_BI;
	}

	return 0_BI;
}

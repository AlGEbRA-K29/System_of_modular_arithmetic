#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "Factorization.h"
using namespace std;

bigint carmaicle(vector<bigint> arr, int n);

bigint eurel(bigint n);

[[nodiscard]] std::vector<bigint> factorizeForEurelFunction(bigint n, std::vector<bigint> factors);




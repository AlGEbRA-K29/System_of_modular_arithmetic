#pragma once
#include"polynomial_ring.h"
#include<vector>
#include<string>
#include <cmath>

using namespace std;

vector<int> findDividers(int n);

bool prime(int n);

bool checkForFreeFromSquares(int a);

int countPrimeDividers(int n);

int Mobiusfunction(int d);

polynomial_ring CircularPolynom(int n, int primeCP);

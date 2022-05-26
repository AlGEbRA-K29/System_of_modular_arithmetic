#pragma once
//
//  main.cpp
//  Euler_func_and karmayrl_func
//
//  Created by Blotenko on 06.05.2022.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "big_integers/bigint.h"
using namespace std;

bigint phi (bigint n);

bigint gcd( bigint a, bigint b );
bigint pw(bigint a,int b,bigint c);
int carmichael(bigint n) ;


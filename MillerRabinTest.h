#pragma once
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <cstdlib>
#include "BigInteger.h"


bool MillerRabin_Test(BigInt t, BigInt n);
bool isPrime(BigInt n, int k);


#ifndef ALL_FUNC_CALL_H
#define ALL_FUNC_CALL_H

#include <iostream>
#include "polynomial.h"
#include "polynomial_field.h"
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
#include "big_integers/mod_bigint.h"
#include "findingCircularPolynomial.h"
#include <vector>

using namespace std;
bigint finFieldAddition(const string& a, const string& b);
bigint finFieldSubstraction(const string& a, const string& b);
bigint finFieldMultiplication(const string& a, const string& b);
bigint finFieldInverse(const string& first, const string& second);
bigint finFieldDivision(const string& a, const string& b);
bigint finFieldPow(const string& a, const string& b);
vector<bigint> finFieldFacrorizationNaive(const string& a);
vector<bigint> finFieldFacrorizationPolard(const string& a);
bigint finFieldSqrt(const string& a);
bigint finFieldOrder(const string& a, const string& modulus);
bool finFieldIsGenerator(const string& a, const string& modulus);
bigint finFieldEuler(const string& a);
bigint finFieldCarmaicle(const string& a);
bool finFieldPrime(const string& a, const string& b);
/*
*theme PolField
*/
polynomial_ring polFieldAddition(const string& a, const string& b, const string& modulus, const string& irred);
polynomial_ring polFieldSubtraction(const string& a, const string& b, const string& modulus, const string& irred);
polynomial_ring polFieldMultiply(const string& a, const string& b, const string& modulus, const string& irred);
polynomial_ring polFieldNormality(const string& a, const string& modulus);
polynomial_ring polFieldFastPow(const string& a, const string& b, const string& modulus, const string& irred);
bool polFieldIsIrred(const string& a, const string& modulus);
polynomial_ring polFieldGetInverse(const string& a, const string& modulus, const string& irred );
/*
*theme PolRing
*/
polynomial_ring polRingAddition(const string& a, const string& b, const string& modulus);
polynomial_ring polRingSubtraction(const string& a, const string& b, const string& modulus);
polynomial_ring polRingMultiply(const string& a, const string& b, const string& modulus);
polynomial_ring polRingDerivative(const string& a, const string& modulus);
bigint polRingValueInPoint(const string& a, const string& b, const string& modulus);
polynomial_ring polRingDivide(const string& a, const string& b, const string& modulus);
polynomial_ring polRingRemainder(const string& a, const string& b, const string& modulus);
polynomial_ring polRingGCD(const string& a, const string& b, const string& modulus);
polynomial_ring polRingGetCycled(const string& a, const string& modulus);


#endif // ALL_FUNC_CALL_H

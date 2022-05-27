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
polynomial polRingAddition(const string& a, const string& b);
polynomial polRingSubtraction(const string& a, const string& b);
polynomial polRingMultiply(const string& a, const string& b);
polynomial polRingDerivative(const string& a);
bigint polRingValueInPoint(const string& a, const string& b);
polynomial polRingGetCycled(const string& a);

bigint finFieldAddition(const string& a, const string& b);
bigint finFieldSubstraction(const string& a, const string& b);
bigint finFieldMultiplication(const string& a, const string& b);
bigint finFieldInverse(const string& first, const string& second);
bigint finFieldDivision(const string& a, const string& b);
bigint finFieldPow(const string& a, const string& b);
vector<bigint> finFieldFacrorizationNaive(const string& a);
vector<bigint> finFieldFacrorizationPolard(const string& a);
bigint finFieldSqrt(const string& a);
bigint finFieldEuler(const string& a);
bigint finFieldCarmaicle(const string& a);
bool finFieldPrime(const string& a);

//bigint polFieldIrreducible(const string& a, const string& b);
polynomial_field polFieldAddition(const string& a, const string& b, const string& modulus);
polynomial_field polFieldSubstraction(const string& a, const string& b, const string& modulus);
polynomial_field polFieldMultiply(const string& a, const string& b, const string& modulus);
polynomial_field polFieldNormality(const string& a, const string& modulus);
polynomial_field polFieldFastPow(const string& a, const string& b, const string& modulus);
//bigint polFieldInverse(const string& a, const string& b);


#endif // ALL_FUNC_CALL_H

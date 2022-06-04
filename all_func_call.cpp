#include "all_func_call.h"


using namespace std;
bigint finFieldAddition(const string& a, const string& b, const string& c){
    bigint first(a);
    bigint second(b);
    bigint third(c);
    return (first+second)%third;
}
bigint finFieldSubstraction(const string& a, const string& b, const string& c){
    bigint first(a);
    bigint second(b);
    bigint third(c);
    return (first-second)%third;
}
bigint finFieldMultiplication(const string& a, const string& b, const string& c){
    bigint first(a);
    bigint second(b);
    bigint third(c);
    return (first*second)%third;
}
bigint finFieldInverse(const string& first, const string& second, const string& c){
    bigint a(first);
    bigint b(second);
    bigint modulus(c);
    bigint i = modInverse(a, b);
    if (i==-1){
        return bigint(0);
    } else {
        return i%modulus;
    }
}
bigint finFieldDivision(const string& a, const string& b, const string& c){
    bigint first(a);
    bigint second(b);
    bigint modulus(c);
    return (first/second)%modulus;
}
bigint finFieldPow(const string& a, const string& b, const string& c){
    bigint bint1(a);
    bigint bint2(b);
    bigint modulus(c);
    montgomery mont1(bint1, bigint("999999000001"));
    montgomery mont3 = mont1 ^ bint2;//*
    bint2 = mont3.getmontgform();
    return bint2%modulus;
}
vector<bigint> finFieldFacrorizationNaive(const string& a){
    bigint first(a);
    std::vector<bigint> res = Factorization(first, false);
    return res;
}
vector<bigint> finFieldFacrorizationPolard(const string& a){
    bigint first(a);
    std::vector<bigint> res = Factorization(first, true);
    return res;
}
bigint finFieldSqrt(const string& a, const string& modulus){
    bigint first(a);
    bigint b(modulus);
    return first.sqrt()%b;
}
bigint finFieldOrder(const string& a, const string& modulus){
    bigint first(a);
    bigint mod1(modulus);
    return find_order(first, mod1);
}
bool finFieldIsGenerator(const string& a, const string& modulus){
    bigint first(a);
    bigint mod1(modulus);
    return isGenerator(first, mod1);
}
bigint finFieldEuler(const string& a){
    bigint n(a);
    vector<bigint> vec;
    vec = factorizeForEurelFunction(n, vec);
    return eurel(vec,vec.size());
}
bigint finFieldCarmaicle(const string& a){
    bigint n(a);
    vector<bigint> vec;
    vec = factorizeForEurelFunction(n, vec);
    return carmaicle(vec,vec.size());
}
bool finFieldPrime(const string& a, const string& b){
    BigInt first(a);
    int key = std::stoi(b);
    return isPrime(first,key);
}
/*
*finding the order by mykola
*/
/*
*theme PolRing
*/
polynomial_ring polRingAddition(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    polynomial_ring test2(b, polyMod);
    polynomial_ring c = test1 + test2;
    return c;
}
polynomial_ring polRingSubtraction(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    polynomial_ring test2(b, polyMod);
    polynomial_ring c = test1 - test2;
    return c;
}
polynomial_ring polRingMultiply(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    polynomial_ring test2(b, polyMod);
    polynomial_ring c = test1 * test2;
    return c;
}
polynomial_ring polRingDerivative(const string& a, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    return test1.derivative();
}
bigint polRingValueInPoint(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    bigint value(b);
    return test1.get_value(value);
}
polynomial_ring polRingDivide(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    polynomial_ring test2(b, polyMod);
    return test1.divide(test1, test2);
}
polynomial_ring polRingRemainder(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    polynomial_ring test2(b, polyMod);
    return test1.remainder(test1, test2);
}
polynomial_ring polRingGCD(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring test1(a, polyMod);
    polynomial_ring test2(b, polyMod);
    return test1.polynom_gcd(test1, test2);
}
polynomial_ring polRingGetCycled(const string& a, const string& modulus){
    int b = std::stoi(a);
    int c = std::stoi(modulus);
    polynomial_ring p = CircularPolynom(b, c);
    return p;
}
/*
*theme PolField
*/
/*bigint polFieldIrreducible(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first*second;
} */
polynomial_ring polFieldAddition(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring p2(b, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    PolynomialField c(irreducible);
    return c.addition(p1,p2);
}
polynomial_ring polFieldSubtraction(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring p2(b, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    PolynomialField c(irreducible);
    return c.subtract(p1, p2);
}
polynomial_ring polFieldMultiply(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring p2(b, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    PolynomialField c(irreducible);
    return c.multiply(p1, p2);
}
polynomial_ring polFieldNormality(const string& a, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    p1.normalize();
    return p1;
}
polynomial_ring polFieldFastPow(const string& a, const string& b, const string& modulus, const string& irred){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    bigint degree(b);
    polynomial_ring irreducible(irred, polyMod);
    PolynomialField c(irreducible);
    return c.quickPow(p1, degree);
}
/*�������� == true */
bool polFieldIsIrred(const string& a, const string& modulus){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);

    return p1.isIrreducible();
}
polynomial_ring polFieldGetInverse(const string& a, const string& modulus, const string& irred ){
    bigint polyMod(modulus);
    polynomial_ring p1(a, polyMod);
    polynomial_ring irreducible(irred, polyMod);
    PolynomialField c(irreducible);
    return c.extended_Euclidean_algorithm(p1, irreducible);
}

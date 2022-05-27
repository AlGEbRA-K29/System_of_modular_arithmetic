#include "all_func_call.h"

using namespace std;
polynomial polRingAddition(const string& a, const string& b){
    polynomial test_1(a);
    polynomial test_2(b);
    return test_1+test_2;
}
polynomial polRingSubtraction(const string& a, const string& b){
    polynomial test_1(a);
    polynomial test_2(b);
    return test_1-test_2;
}
polynomial polRingMultiply(const string& a, const string& b){
    polynomial test_1(a);
    polynomial test_2(b);
    return test_1*test_2;
}
polynomial polRingDerivative(const string& a){
    polynomial test(a);
    return test.derivate();
}
bigint polRingValueInPoint(const string& a, const string& b){
    polynomial test(a);
    bigint value(b);
    return test.get_value(value);
}

polynomial polRingGetCycled(const string& a){
    int b = std::stoi(a);
    polynomial p = findCircularPolynomial(b);
    return p;
}

bigint finFieldAddition(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first+second;
}
bigint finFieldSubstraction(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first-second;
}
bigint finFieldMultiplication(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first*second;
}
bigint finFieldInverse(const string& first, const string& second){
    bigint a(first);
    bigint b(second);
    bigint i = modInverse(a, b);
    if (i==-1){
        return bigint(0);
    } else {
        return i;
    }
}
bigint finFieldDivision(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first/second;
}
bigint finFieldPow(const string& a, const string& b){
    bigint bint1(a);
    bigint bint2(b);
    montgomery mont1(bint1, bigint("59"),bigint("64"));
    montgomery mont2(bint2, bigint("59"), bigint("64"));
    montgomery mont3 = mont1 ^ mont2;
    bint2 = mont3.getmontgform();
    return bint2;
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
bigint finFieldSqrt(const string& a){
    bigint first(a);
    return first.sqrt();
}
bigint finFieldEuler(const string& a){
    bigint n(a);
    vector<bigint> vec;
    vec=factorize(n,vec);
    return eurel(vec,vec.size());
}
bigint finFieldCarmaicle(const string& a){
    bigint n(a);
    vector<bigint> vec;
    vec=factorize(n,vec);
    return carmaicle(vec,vec.size());
}
bool finFieldPrime(const string& a){
    BigInt first(a);
    return isPrime(first,1);
}

/*bigint polFieldIrreducible(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first*second;
}*/
polynomial_field polFieldAddition(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_field field1(a, polyMod);
    polynomial_field field2(b, polyMod);
    polynomial_field c = field1 + field2;
    return c;
}
polynomial_field polFieldSubstraction(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_field field1(a, polyMod);
    polynomial_field field2(b, polyMod);
    polynomial_field c = field1 - field2;
    return c;
}
polynomial_field polFieldMultiply(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    polynomial_field field1(a, polyMod);
    polynomial_field field2(b, polyMod);
    polynomial_field c = field1 * field2;
    return c;
}
polynomial_field polFieldNormality(const string& a, const string& modulus){
    bigint polyMod(modulus);
    polynomial_field field1(a, polyMod);
    field1.normalize();
    return field1;
}
polynomial_field polFieldFastPow(const string& a, const string& b, const string& modulus){
    bigint polyMod(modulus);
    bigint power(b);
    polynomial_field field1(a, polyMod);
    field1.quickPow(power);
    return field1;
}
/*bigint polFieldInverse(const string& a, const string& b){
    bigint first(a);
    bigint second(b);
    return first*second;
}*/



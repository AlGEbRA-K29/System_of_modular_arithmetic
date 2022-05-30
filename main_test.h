#pragma once
#include <iostream>
#include "polynomial_ring.h"
//#include "polynomial_field.h" //polishuk and procopchuk fix it
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
//#include "findingCircularPolynomial.h" //ilyin task
#include <vector>
using namespace std;
/*
*theme Field 
*/
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
	polynomial_ring rez=test1.divide(test1, test2);
	return rez;
}
polynomial_ring polRingRemainder(const string& a, const string& b, const string& modulus){
	bigint polyMod(modulus);
	polynomial_ring test1(a, polyMod);
	polynomial_ring test2(b, polyMod);
	polynomial_ring rez=test1.remainder(test1, test2);
	return rez;
}
polynomial_ring polRingGCD(const string& a, const string& b, const string& modulus){
	bigint polyMod(modulus);
	polynomial_ring test1(a, polyMod);
	polynomial_ring test2(b, polyMod);
	polynomial_ring rez=test1.polynom_gcd(test1, test2);
	return rez;
}
//waiting...
/*polynomial polRingGetCycled(const string& a){
	int b = std::stoi(a);	
	polynomial p = findCircularPolynomial(b);
	return p;
}*/
//waiting...
/*
*theme PolField
*/
/*bigint polFieldIrreducible(const string& a, const string& b){
	bigint first(a);
	bigint second(b);
	return first*second;
}
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
	field1=field1.quickPow(power);	
	return field1;
}
bigint polFieldInverse(const string& a, const string& b){
	bigint first(a);
	bigint second(b);
	return first*second;
}*/


/*int main() {
	//console tests block 1
	cout <<"	FINITE FIELD" << endl;
	cout <<finFieldAddition("10", "20")<< endl;
	cout <<finFieldSubstraction("10", "20")<< endl;
	cout <<finFieldMultiplication("10", "20")<< endl;
	bigint inversAns = finFieldInverse("129", "7");
	cout <<finFieldDivision("200", "20")<< endl;
	cout << finFieldPow("2","15") << endl;
	finFieldFacrorizationNaive("100");
    finFieldFacrorizationPolard("200");
 	cout << finFieldSqrt("121") << endl;
 	cout << finFieldOrder("3", "100") <<endl;
	cout << finFieldIsGenerator("33", "101293") << endl;
    cout<<finFieldEuler("12")<<endl;
    cout<<finFieldCarmaicle("10")<<endl;
	cout <<finFieldPrime("2147483647")<< endl;      
	//console tests block 1
	cout <<"	POLYNOMIAL" << endl;
	cout << polRingAddition("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123", "11")<< endl;
	cout << polRingSubtraction("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123", "11")<< endl;
	cout << polRingMultiply("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123", "11")<< endl;
	cout << polRingDerivative("-10000x^-12-9000x^4200+12x^1+123", "11") << endl;
	cout << polRingValueInPoint("-10000x^-12-9000x^4200+12x^1+123", "1", "11") <<  endl;
	cout << endl;
	
    
    cout <<"Press any key to exit " << endl;
    int k;
    cin >> k;
    return 0;
	
	
	return 0;
}*/

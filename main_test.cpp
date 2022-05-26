#include <iostream>
#include "polynomial.h"
#include "polynomial_field.h"
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
#include <vector>
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
/*bigint finFieldEuler(const string& a){
	bigint first(a);
	return phi(first);
}*/
/*bigint finFieldKarmayr(const string& a){
	bigint first(a);
	return carmichael(first);
}*/
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


int main() {
	/*
	*OK
	*/
	/*cout <<"	POLYNOMIAL" << endl;
	cout << polRingAddition("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123")<< endl;
	cout << polRingSubtraction("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123")<< endl;
	cout << polRingMultiply("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123")<< endl;
	cout << polRingDerivative("-10000x^-12-9000x^4200+12x^1+123") << endl;
	cout <<  polRingValueInPoint("-10000x^-12-9000x^4200+12x^1+123", "1") <<  endl;
	cout << endl;*/
	/*
	*OK
	*/
/*	cout <<"	FINITE FIELD" << endl;
	cout <<finFieldAddition("10", "20")<< endl;
	cout <<finFieldSubstraction("10", "20")<< endl;
	cout <<finFieldMultiplication("10", "20")<< endl;
	bigint inversAns = finFieldInverse("129", "7");
	cout <<finFieldDivision("200", "20")<< endl;*/
	/*
	*OK
	*/
//	cout << finFieldPow("2","15") << endl;
	
    /*
    *OK
    */
/*  finFieldFacrorizationNaive("100");
    finFieldFacrorizationPolard("200");*/
    /*
    *OK
    */
   // cout << finFieldSqrt("121") << endl;

	//khlopyk
		/**/
		
	//bloshenko hrishenko
	/*
	*CYCLED, BAD
	*/
	/*cout <<"Eylera and Carmichael function: " << endl;
	int n = 90;
    cout<<"Eylera("<<n<<") : "<<phi(n)<<endl;
    cout<<"Carmichael("<<n<<") : "<<carmichael(n)<<endl;*/
    
    /*
    *OK
    */
//	cout <<finFieldPrime("2147483647")<< endl;
       
    
    /*
    *OK
    */
/*	cout <<"	POLYNOMIAL FIELD" << endl;
	cout << polFieldAddition("5x^2+4","3x^3+11","5") << endl;
	cout << polFieldSubstraction("5x^2+4","3x^2+11","5") << endl;
	cout << polFieldMultiply("5x^2+4","3x^3+11","5") << endl;
	cout << polFieldNormality("5x^2+4","5") << endl;
	cout << polFieldFastPow("5x^2+4","12","5") << endl;*/
	
	
	
    
    cout <<"Press any key to exit " << endl;
    int k;
    cin >> k;
    return 0;
	
	
	return 0;
}
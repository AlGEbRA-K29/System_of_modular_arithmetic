#include <iostream>
#include "polynomial.h"
#include "polynomial_field.h"
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
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
/*bigint finFieldPow(const string& a, const string& b){
	bigint first(a);
	bigint second(b);
	return first/second;
}*/
/*bigint finFieldFacrorizationNaive(const string& a){
	bigint first(a);
	std::vector<bigint> res = Factorization(first, false);
	PrintFactors(test_data, res);
	return first/second;
}*/
/*bigint finFieldFacrorizationPolard(const string& a){
	bigint first(a);
	std::vector<bigint> res = Factorization(first, true);
	PrintFactors(test_data, res);
	return first/second;
}*/

int main() {
	/*cout <<"	POLYNOMIAL" << endl;
	cout << polRingAddition("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123")<< endl;
	cout << polRingSubtraction("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123")<< endl;
	cout << polRingMultiply("100x^2+x^3+12", "-100x^2-9000x^3+12x^1+123")<< endl;
	cout << polRingDerivative("-10000x^-12-9000x^4200+12x^1+123") << endl;
	cout <<  polRingValueInPoint("-10000x^-12-9000x^4200+12x^1+123", "1") <<  endl;
	cout << endl;*/
	
/*	cout <<"	FINITE FIELD" << endl;
	cout <<finFieldAddition("10", "20")<< endl;
	cout <<finFieldSubstraction("10", "20")<< endl;
	cout <<finFieldMultiplication("10", "20")<< endl;
	bigint inversAns = finFieldInverse("129", "7");
	cout <<finFieldDivision("200", "20")<< endl;*/
		//polishuk
/*	cout <<"Rapid rise to the degree: " << endl;
    bigint bint1("10");
    bigint bint2("12");
    montgomery mont1(bint1, bigint("59"),bigint("64"));
    montgomery mont2(bint2, bigint("59"), bigint("64"));
    montgomery mont3;
    mont3 = mont1 * mont2;
    mont3 = mont1 ^ bint2;
    mont3 = mont1 ^ mont2;
    bint2 = mont3.convertToStandartForm(mont3.getmontgform());
    cout << "Good!" << endl;
    cout << endl;*/
    
     	//kotlyarova prokopchuk
    /*cout <<"Multiplication of numbers: " << endl;
    bigint test_data = 100;
	bool use_pollard = true;
	std::vector<bigint> res = Factorization(test_data, use_pollard);
	std::cout << "Naive method(100): ";
	PrintFactors(test_data, res);
	use_pollard = true;
	res = Factorization(test_data, use_pollard);
	std::cout << "Pollard method(100): ";
	PrintFactors(test_data, res);*/

	//bloshenko hrishenko
	//CYCLED
	/*cout <<"Eylera and Carmichael function: " << endl;
	int n = 90;
    cout<<"Eylera("<<n<<") : "<<phi(n)<<endl;
    cout<<"Carmichael("<<n<<") : "<<carmichael(n)<<endl;*/

	
	//khlopyk
	/**/
	
	//bocharova hromadiuk
/*	cout <<"Miller Rabin Test: " << endl;
	BigInt Miiller_test = 100;
	cout <<"Is prime 100(no==0): " << isPrime(Miiller_test,1) << endl;
	Miiller_test = 2147483647;
	cout <<"Is prime 2147483647(yes==1): " << isPrime(Miiller_test,1) << endl;*/
	
    
    
    //prokopchuk polishuk
/*	cout <<"	POLYNOMIAL FIELD" << endl;
	cout <<"PART3: " << endl;
	bigint number("-10");
	polynomial_field field1("2x^4+3x^2-1x^1", bigint(7));
	cout << field1 << endl;
	polynomial_field field2("5x^5+15x^3-2x^1", bigint(7));
	cout << field2 << endl;
	polynomial_field c = field1 * field2;
	cout <<"("<<field1<<")*("<<field2<<") = "<< c <<endl;
	c = field1 - field2;
	cout <<"("<<field1<<")-("<<field2<<") = "<< c <<endl;
	c = field1 + field2;
	cout <<"("<<field1<<")+("<<field2<<") = "<< c <<endl;
	c = c * number;
	cout <<"("<<field1<<")*("<<number<<") = "<< c <<endl;*/
	
	
	
    
    cout <<"Press any key to exit " << endl;
    int k;
    cin >> k;
    return 0;
	
	
	return 0;
}

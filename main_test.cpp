#include <iostream>
#include "polynomial.h"
#include "Euler_and_Karmayr.h"
//#include "Factorization.h"
//#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "Montgomery_form.h"

using namespace std;

int main() {
	//safroniuk coba
	cout <<"	POLYNOMIAL" << endl;
	cout <<"PART1: " << endl;
	polynomial test_1("100x^2+x^3+12");
	cout << test_1 << endl;
	polynomial test_2("-100x^2-9000x^3+12x^1+123");
	cout << test_2 << endl;
	cout <<"Addition: " << test_1+test_2 << endl;
	cout <<"Subtraction: " << test_1-test_2 << endl;
	cout <<"Multiplication: " << test_1*test_2 <<endl;
	cout << endl;
	//bocharova muzyka
	cout <<"PART2: " << endl;
	polynomial p1("-10000x^-12-9000x^4200+12x^1+123");	
	polynomial derivate_p1=p1.derivate();
	cout << "Polynomial: "<< p1 << endl;
	cout << "Value of polynmial at point 1: "<< p1.get_value(1) <<  endl;
	cout << "Derivative: "<< derivate_p1 << endl;
	cout << endl;
	cout << endl;

	cout <<"	FINITE FIELD" << endl;
	//safroniuk coba
	cout <<"Additional, Substraction, Multiplication: " << endl;
	bigint a=1000000;
	bigint b=2000000;
	cout <<"Additional "<<a<<"+"<<b<<": " << a+b << endl;
	cout <<"Multiplication "<<a<<"*"<<b<<": " << a*b << endl;
	cout <<"Substraction "<<a<<"-"<<b<<": " << a-b << endl;
	//doroshenko
	a*=10;
	cout << "Division "<<a<<"/"<<b<<": " << a/b << endl;
	//bloshenko hrishenko
	/*cout <<"Eylera and Carmichael function: " << endl;
	bigint n = 90;
    cout<<"Eylera("<<n<<") : "<<phi(n)<<endl;
    cout<<"Carmichael("<<n<<") : "<<carmichael(n)<<endl;*/
    
    //kotlyarova prokopchuk
    /*cout <<"Multiplication of numbers: " << endl;
    bigint n = 100;
	bool use_pollard = true;
	std::vector<bigint> res = Factorization(n, use_pollard);
	std::cout << "Naive method(100): ";
	PrintFactors(n, res);
	use_pollard = true;
	std::vector<bigint> res = Factorization(n, use_pollard);
	std::cout << "Pollard method(100): ";
	PrintFactors(n, res);*/
	
	//khlopyk
	/**/
	
	//bocharova hromadiuk
	cout <<"Miller Rabin Test: " << endl;
	BigInt n = 100;
	cout <<"Is prime 100(no==0): " << isPrime(n,1) << endl;
	n = 2147483647;
	cout <<"Is prime 2147483647(yes==1): " << isPrime(n,1) << endl;
	
	//polishuk
	/*cout <<"Rapid rise to the degree: " << endl;
    bigint bint1("10");
    bigint bint2("12");
    montgomery mont1(bint1, bigint("2"),bigint("3"));
    montgomery mont2(bint2, bigint("2"), bigint("3"));
    montgomery mont3;
    mont3 = mont1 * mont2;
    mont3 = mont1 ^ bint2;
    mont3 = mont1 ^ mont2;
    bint2 = mont3.convertToStandartForm(mont3.getmontgform());
    cout << bint2 << endl;*/
	
    
    
    
    
    return 0;
	
	
	return 0;
}

#include <iostream>
#include "polynomial.h"

using namespace std;

int main() {
	/*part1*/
	cout <<"PART1: " << endl;
	polynomial test_1("100x^2+x^3+12");
	cout << test_1 << endl;
	polynomial test_2("-100x^2-9000x^3+12x^1+123");
	cout << test_2 << endl;
	cout <<"Addition: " << test_1+test_2 << endl;
	cout <<"Subtraction: " << test_1-test_2 << endl;
	cout <<"Multiplication: " << test_1*test_2 <<endl;
	cout << endl;
	
	cout <<"PART2: " << endl;
	polynomial p1("-10000x^-12-9000x^4200+12x^1+123");	
	polynomial derivate_p1=p1.derivate();
	cout << "Polynomial: "<< p1 << endl;
	cout << "Value of polynmial at point 1: "<< p1.get_value(1) <<  endl;
	cout << "Derivative: "<< derivate_p1 << endl;
	
	return 0;
}

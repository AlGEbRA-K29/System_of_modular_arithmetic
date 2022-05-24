#include <iostream>
#include "polynomial.h"

using namespace std;

int main()
{
	polynomial p1("10000x^12-9000x^4200");
	polynomial p2("10000x^-6-9000x^-2000");
	polynomial p3 = p1 * p2;
	cout << p1 << endl << p2 << endl << p3;
	return 0;
}
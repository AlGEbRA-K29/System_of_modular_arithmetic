#include <iostream>
#include "polynomial.h"

using namespace std;

int main() {
	polynomial p1("-10000x^-12-9000x^4200+12x^1+123");
	polynomial derivate_p1=p1.derivate();
	cout << p1 << endl;
	cout << p1.get_value(1) <<  endl;
	cout << derivate_p1 << endl;
	
	return 0;
}

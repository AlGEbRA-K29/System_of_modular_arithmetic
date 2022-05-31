#include"polynomial_ring.h"
#include"findingCircularPolynomial.h"
#include <iostream>



int main() {
	
	
	polynomial_ring test1 = CircularPolynom(36, 2);
	cout << test1 << endl;

	polynomial_ring test2 = CircularPolynom(18, 3);
	cout << test2 << endl;

	polynomial_ring test3 = CircularPolynom(5, 5);
	cout << test3 << endl;

	polynomial_ring test4 = CircularPolynom(15, 7);
	cout << test4 << endl;

	polynomial_ring test5 = CircularPolynom(68, 12);
	cout << test5 << endl;

	

	return 0;
}

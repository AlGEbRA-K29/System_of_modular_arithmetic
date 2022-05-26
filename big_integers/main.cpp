#include"polynomial.h"
#include"findingCircularPolynomial.h"
#include <iostream>



int main() {
	polynomial p = findCircularPolynomial(29);
	std::cout << p << "\n";

	return 0;
}

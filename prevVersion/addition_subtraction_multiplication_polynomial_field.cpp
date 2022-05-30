
#include <iostream>
#include "polynomial_field.h"
#include "../big_integers/bigint.h"

int main()
{
	//(2x^4 + 3x^2 - x) * (5x^5 + 15x^3 - 2x)     for wolfram
	bigint mod_ ("-10");

	
	
	polynomial_field a("2x^4+3x^2-1x^1", bigint("7"));
	polynomial_field b("5x^5+15x^3-2x^1", bigint("7"));
	/*check modulus
	a.setModulus(mod_);
	a.setModulus(bigint("-127"));
	a.setModulus(bigint("6"));*/

	polynomial_field c = a * b;
	c = a - b;
	c = b - a;
	c = a + b;
	c = c * mod_;
	

	return 0;
}

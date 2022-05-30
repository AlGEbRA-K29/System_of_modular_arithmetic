#include <iostream>
#include "polynoms_divide_remainder_gcd.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Finding the fraction and reminder") {
	
	polynomial_field a1("x^4+3*x^3+2*x^1+4", 5);
	polynomial_field b1("2*x^1+4", 5);
	polynomial_field division1("3*x^3+3*x^2+4*x^1+3", 5);
	polynomial_field remainder1("2", 5);
	CHECK(divide(a1, b1).getData() == division1.getData());
	CHECK(remainder(a1, b1).getData() == remainder1.getData());
	
	polynomial_field a2("2*x^4+3*x^3+2*x^1", 5);
	polynomial_field b2("x^1+4", 5);
	polynomial_field division2("2*x^3+2", 5);
	polynomial_field remainder2("2", 5);
	CHECK(divide(a2, b2).getData() == division2.getData());
	CHECK(remainder(a2, b2).getData() == remainder2.getData());

	polynomial_field a3("x^2+x^1", 5);
	polynomial_field b3("1*x^1+1", 5);
	polynomial_field gcd3("x^1+1", 5);
	CHECK(polynom_gcd(a3, b3).getData() == gcd3.getData());
}

/*
int main()
{
	polynomial_field a1("x^4+3*x^3+2*x^1+4", 5);
	polynomial_field b1("2*x^1+4", 5);
	
	std::cout << divide(a1, b1) <<"\n";
	std::cout << remainder(a1, b1) <<"\n";
	std::cout << divide(a1, b1) * b1 + remainder(a1, b1) << "\n";

	polynomial_field a2("2*x^4+3*x^3+2*x^1", 5);
	polynomial_field b2("x^1+4", 5);
	std::cout << divide(a2, b2) << "\n";
	std::cout << remainder(a2, b2) << "\n";
	std::cout << divide(a2, b2)*b2 + remainder(a2, b2) << "\n";

	polynomial_field a3("x^2+x^1", 5);
	polynomial_field b3("1*x^1+1", 5);
	std::cout << polynom_gcd(a3, b3);
	

	return 0;
}*/
#pragma once
#include <map>
#include "bigint.h"
#include "polynomial_field.h"
#include "inverse.h"

polynomial_field divide(const polynomial_field& a, const polynomial_field& b) {
	if (a.getModulus() != b.getModulus()) {
		throw std::invalid_argument("Fields have different orders");
	}
	int powerA = (--a.getData().end())->first;
	int powerB = (--b.getData().end())->first;

	if (powerB > powerA)
	{
		return polynomial_field();
	}

	auto current = polynomial_field(a);
	auto output = polynomial_field("", b.getModulus());
	polynomial_field x("x^1", b.getModulus());
	bigint bigPowInverse = modInverse((--b.getData().end())->second, b.getModulus());
	std::vector <bigint>result(powerA + 1);
	while ((--current.getData().end())->first >= powerB) {
		bigint koef = (--current.getData().end())->second * bigPowInverse;
		//std::cout <<"power " << (--current.getData().end())->first - powerB<<" koef "<< koef << "\n";
		result[(--current.getData().end())->first - powerB] = koef;
		//output.getData()[(--current.getData().end())->first - powerB] = koef;
		polynomial_field subtractor = b * koef;

		for (bigint i = 0; i < (--current.getData().end())->first - powerB; i++)
		{
			subtractor = subtractor * polynomial_field("x^1", subtractor.getModulus());
		}
		/*	std::cout << current <<" cur \n";
			std::cout << subtractor << " sub \n";
			*/
		current = current - subtractor;
		//	std::cout << current << " cur \n";

		if (current.getData().empty())
		{
			break;
		}
	}

	return polynomial_field(result, b.getModulus());
}

polynomial_field remainder(const polynomial_field& a, const polynomial_field& b) {
	if (a.getModulus() != b.getModulus()) {
		throw std::invalid_argument("Fields have different orders");
	}
	int powerA = (--a.getData().end())->first;
	int powerB = (--b.getData().end())->first;


	polynomial_field div = divide(a, b);
	if (powerB > powerA || div.getData().empty())
	{
		return polynomial_field(a);
	}

	return a - (div * b);
}

polynomial_field polynom_gcd(const polynomial_field& a, const polynomial_field& b) {

	if (b.getData().empty()) {
		return a;
	}
	if ((--a.getData().end())->first < (--b.getData().end())->first)
	{
		return polynom_gcd(b, a);
	}
	return polynom_gcd(b, remainder(a, b));
}
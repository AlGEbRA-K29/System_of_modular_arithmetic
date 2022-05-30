#pragma once
#include "bigint.h"
#include "polynomial_ring.h"



class PolynomialField
{
	
public:
	PolynomialField() = delete;
	
	PolynomialField( polynomial_ring pol) {
		
		setIrreducible(pol);
	};
	void setIrreducible(polynomial_ring& pol)
	{
		pol.normalize();
		if (!pol.isIrreducible())
			throw std::invalid_argument("Polynomial is not irreducible");
		else
			irreducible = pol;
	}


	polynomial_ring add( polynomial_ring& a,  polynomial_ring& b)
	{
		if (a.getModulus() != b.getModulus() || a.getModulus() != irreducible.getModulus()) 
		{
			throw std::invalid_argument("Fields have different orders");
		}
		polynomial_ring res = a + b;
		std::cout << res << std::endl;
		res = res.remainder(res,irreducible);
		return(res);
	}

	polynomial_ring subtract(polynomial_ring& a, polynomial_ring& b)
	{
		if (a.getModulus() != b.getModulus() || a.getModulus() != irreducible.getModulus())
		{
			throw std::invalid_argument("Fields have different orders");
		}
		polynomial_ring res = a - b;
		res = res.remainder(res, irreducible);
		return(res);
	}

	polynomial_ring multiply(polynomial_ring& a, polynomial_ring& b)
	{
		if (a.getModulus() != b.getModulus() || a.getModulus() != irreducible.getModulus())
		{
			throw std::invalid_argument("Fields have different orders");
		}
		polynomial_ring res = a * b;
		res = res.remainder(res, irreducible);
		return(res);
	}


	polynomial_ring quickPow(polynomial_ring poly,bigint power) const {
		if (power < 1_BI) {
			throw std::invalid_argument("Power value must be greater than 0");
		}

		polynomial_ring result({ 1_BI }, poly.getModulus());
		polynomial_ring multiplier = poly;

		while (!power.isZero()) {
			if (power % 2_BI == 0_BI) {
				multiplier *= multiplier;
				power /= 2;
			}
			else {
				result *= multiplier;
				--power;
			}
		}

		return result.remainder(result,irreducible);
	}

	


private:
	polynomial_ring irreducible;


};
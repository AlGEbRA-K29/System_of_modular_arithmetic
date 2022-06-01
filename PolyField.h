#pragma once
#include "bigint.h"
#include "polynomial_ring.h"



class PolynomialField
{
	
public:
	PolynomialField() = delete;
	
	PolynomialField(const polynomial_ring& pol) {	
		if (pol.getDegree() == 0) {
			throw std::invalid_argument("Expected non-constant polynomial");
		}
		
		setIrreducible(pol);
	};

	void setIrreducible(polynomial_ring pol)
	{
		pol.normalize();
		if (!pol.isIrreducible())
			throw std::invalid_argument("Polynomial is not irreducible");
		else
			irreducible = pol;
	}


	polynomial_ring add(const polynomial_ring& a, const polynomial_ring& b) const
	{
		//checkDegree(a);
		//checkDegree(b);

		polynomial_ring res = a + b;
		//std::cout << res << std::endl;
		res = res.remainder(res, irreducible);
		return res;
	}

	polynomial_ring subtract(const polynomial_ring& a, const polynomial_ring& b) const
	{
		//checkDegree(a);
		//checkDegree(b);

		polynomial_ring res = a - b;

		res = res.remainder(res, irreducible);
		return res;
	}

	polynomial_ring multiply(const polynomial_ring& a, const polynomial_ring& b) const
	{
		//checkDegree(a);
	//	checkDegree(b);

		polynomial_ring res = a * b;

		res = res.remainder(res, irreducible);
		return res;
	}


	polynomial_ring quickPow(const polynomial_ring& poly,bigint power) const {
		if (power < 1_BI) {
			throw std::invalid_argument("Power value must be greater than 0");
		}

		//checkDegree(poly);

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

	//Bloshenko's code
	// знаходження inverse полінома а по модулю b, та invers b по модулю a
	//
	// u - поліном в якому буде inverse полінома а по модулю b
	// v - поліном в якому буде inverse полінома a по модулю b
	//
	// w- поліном в якому буде polynom_gcd(a,b)
	//
	// x,y,z - дефолтни поліноми для підрахунків та збереження данних
	//
	// Що вводити в функцію :
	// два поліноми a, b та дефолтни
	// u("1",modulus), v("0",modulus), w("0",modulus), x("0",modulus), y("1",modulus), z("0",modulus)
	// Що виводити як відповідь : u як inverse a по модулю b та 
	// v як b по модулю a
	//
	// для тестів можно взяти polynom_gcd(), тобто polynom_gcd(a,b) == w  (после виволнения функции)
	
	void extended_Euclidean_algorithm(polynomial_ring a, polynomial_ring b, polynomial_ring& u, polynomial_ring& v, polynomial_ring& w, polynomial_ring& x, polynomial_ring& y, polynomial_ring& z) {

		w = a;
		z = b;

		polynomial_ring q;

		polynomial_ring one("1", a.getModulus());
		while (!z.getData().empty()) {

			q = w.divide(w, z);

			u -= q * x;
			v -= q * y;
			w -= q * z;

			std::swap(u, x);
			std::swap(v, y);
			std::swap(w, z);
		}

		u = u.remainder(u,irreducible);
		v = v.remainder(v,irreducible);
	}

private:
	polynomial_ring irreducible;

	/*void checkDegree(const polynomial_ring& to_check) const {
		if (to_check.getDegree() > irreducible.getDegree()) {
			throw std::invalid_argument("Polynomial isn't in the field");
		}
	}*/
};

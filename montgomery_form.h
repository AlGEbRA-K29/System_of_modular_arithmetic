#pragma once
// Requires including Fail's bigint headers 
#include <vector>
#include "big_integers/bigint.h"
#include "big_integers/mod_bigint.h"

class montgomery
{
public:
	montgomery() = default;

	montgomery(bigint bint, bigint m,bigint factor) :modulus(m), r(factor)
	{
		transform(bint);
	}
	montgomery(bigint bint, bigint m) : modulus(m)
	{
		r = 1;
		while (r < m)
			r *= 2;
		transform(bint);	
	}				
	


[[nodiscard]] montgomery operator*(montgomery& mont1)
	{
	try {
		if (this->r == mont1.getr() && this->getmodulus() == mont1.getmodulus())
		{
			bigint bint1 = this->montgform * mont1.montgform;
			bint1 = redc(bint1);
			bint1 = convertToStandartForm(bint1);                 //conversion to standart form here, because function returns new montgomery number, 
																  //which has conversion to montgomery form in its constructor
																  //i.e. we are avoiding double conversion to montgomery form here,
																  //as bint1 is already in montgomery form
			return montgomery(bint1, this->modulus, this->r);
		}
		else
			throw(bigint("-1"));
		}
	catch (bigint a)
	{
		std::cout << "Montgomery forms have different modulus or factors" << std::endl;
		return montgomery(a,bigint("0"), bigint("0"));
	}
	}

// If exponentiation is impossible returns -1
[[nodiscard]] montgomery operator^(bigint exp)
{
	bigint zero("0");
	bigint one("1");
	montgomery base = *this;
	montgomery result(one, this->modulus,this->r);
	

	if (!exp.isPositive())
	{


		try {
			base.montgform = base.inverseBint(base.montgform);
			if (base.montgform == bigint())
			{
				base = *this;
				base.montgform = base.naiveInverseBint(base.montgform);
				if (base.montgform == bigint())
					throw(base);
				else exp *= bigint("-1");
			}
			else exp *= bigint("-1");
		}
		catch (montgomery res)
		{
			std::cout << "Exponentiation is impossible" << std::endl;
		 base.setMontgform(bigint("-1"));
		 base.setFactor(bigint("0"));
		 base.setModulus(bigint("0"));
		 return base;
		}

	}
		
	
	while (exp > zero)
	{
		if (exp % 2 == one)
		{
			result = result * base;
		}

		exp /= 2;
		base = base * base;

	}

	return result;
}

[[nodiscard]] montgomery operator^(montgomery exp)
{
	return *this ^ exp.getmontgform();
}

	[[nodiscard]]/* [[deprecated]]*/ bigint getr() {
		return this->r;
	}
	[[nodiscard]] bigint getmontgform()
	{
		return this->montgform;
	}
	[[nodiscard]] /*[[deprecated]]*/bigint getmodulus()
	{
		return this->modulus;
	}
	
	[[nodiscard]] bigint convertToStandartForm(bigint bint1)
	{
		return ((bint1 * inverseBint(r)) % this->modulus);
	}
	

private:
	
	void transform(bigint& bint)
	{
		this->montgform = bint * r;
		this->montgform = this->montgform % modulus;
	}

	// Inverse value of factor (r) modulo (modulus), if inverse doesn't exist, returns "0" 
	[[nodiscard]] bigint inverseBint(bigint bint1)
	{
		bigint x("1"), y("0"), modulus0 = modulus;
		while (!(modulus0 == bigint()))
		{
			bigint quotient = bint1 / modulus0;
			bigint temp = modulus0;
			modulus0 = bint1 % modulus0;
			bint1 = temp;

			temp = y;

			y = x - quotient * y;
			x = temp;


		}
		if (bint1.getData().size() == 1 || bint1.getData()[0] == 1)
		{
			if (x.isPositive() == false)
				x += modulus;
			return x;
		}
		return bigint("0");
	}
	//If inverse doesn't exist, returns "0"
	[[nodiscard]] bigint naiveInverseBint(bigint bint1)
	{
		for (bigint i = bigint("1"); i < this->modulus; i = i + bigint("1"))
		{
			if ((bint1 * i) % this->modulus == bigint("1"))
				return i;
		}

		return bigint("0");
	}

	//Reduction algorithm
	[[nodiscard]] bigint redc(bigint& bint1)
	{
		bigint inverse = inverseBint(this->r);
		bigint k = (r * inverse - 1) / this->modulus;
		bigint s = (bint1 * k) % this->r;

		s = bint1 + s * this->modulus;
		s /= this->r;

		if (s < bigint("0") || s >= this->modulus)
			return (s - this->modulus);

		return s;


	}

	void setMontgform(bigint bint1)
	{
		this->montgform = bint1;
	}

	void setModulus(bigint bint1)
	{
		this->modulus = bint1;
	
	}

	void setFactor(bigint bint1)
	{
		this->r = bint1;
	}

	bigint montgform;
	bigint modulus;
	bigint r;

	

};

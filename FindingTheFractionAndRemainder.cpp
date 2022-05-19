#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "big_integers/bigint.h"


class Polynom {
	int degree;
	bigint *coef;
public:
	Polynom(int newDegree);
	Polynom(int newDegree, bigint newCoef[]);
	Polynom(const Polynom &p);
	void reduce(void);
	friend Polynom operator / (const Polynom &p1, const Polynom &p2);
	friend Polynom operator % (const Polynom &p1, const Polynom &p2);
	friend std::ostream &operator << (std::ostream &stream, const Polynom &p);
	friend std::istream &operator >> (std::istream &stream, Polynom &p);
};

Polynom::Polynom(int newDegree) {
	degree = newDegree;
	coef = new bigint[degree];
	for (int i = 0; i < degree; i++) {
		coef[i] = 0.0;
	}
}

Polynom::Polynom(int newDegree, bigint newCoef[]) {
	degree = newDegree;
	coef = new bigint[degree];
	for (int i = 0; i < degree; i++) {
		coef[i] = newCoef[i];
	}
}

Polynom::Polynom(const Polynom &polinom) {
	degree = polinom.degree;
	coef = new bigint[degree];
	for (int i = 0; i < degree; i++) {
		coef[i] = polinom.coef[i];
	}
}

void Polynom::reduce(void) {
	int recducedDeg = degree;
	for (int i = degree - 1; i >= 0; i--) {
		if (coef[i] == 0)
			recducedDeg--;
		else
			break;
			
	}
	degree = recducedDeg;
}

Polynom operator / (const Polynom &polinom1, const Polynom &polinom2) {
	Polynom temp = polinom1;
	int resultDeg = temp.degree - polinom2.degree + 1;
	if (resultDeg < 0) {
		return Polynom(0);
	}
	Polynom res(resultDeg);
	
	for (int i = 0; i < resultDeg; i++) {
		//Use * inverse number instead of /
		res.coef[resultDeg - i - 1] = temp.coef[temp.degree - i - 1] / polinom2.coef[polinom2.degree - 1];
		
		for (int j = 0; j < polinom2.degree; j++) {
			temp.coef[temp.degree - j - i - 1] -= polinom2.coef[polinom2.degree - j - 1] * res.coef[resultDeg - i - 1];
		}
	}

	return res;
}

Polynom operator % (const Polynom &polinom1, const Polynom &polinom2) {
	Polynom temp = polinom1;
	int rdeg = temp.degree - polinom2.degree + 1;
	if (rdeg < 0) {
		return Polynom(0);
	}
	Polynom res(rdeg);
	for (int i = 0; i < rdeg; i++) {
		//Use * inverse number instead of /
		res.coef[rdeg - i - 1] = temp.coef[temp.degree - i - 1] / polinom2.coef[polinom2.degree - 1];
		for (int j = 0; j < polinom2.degree; j++) {
			temp.coef[temp.degree - j - i - 1] -= polinom2.coef[polinom2.degree - j - 1] * res.coef[rdeg - i - 1];
		}
	}

	temp.reduce();
	return temp;
}

std::string bigintToString(bigint num) {
	std::ostringstream os;
	os << num;
	std::string str = os.str();
	return str;
}

std::ostream &operator << (std::ostream &stream, const Polynom &polynom) {
	std::string str = "";
	for (int i = polynom.degree - 1; i >= 0; i--) {
		if (str != "" && polynom.coef[i] > 0) {
			str += " + ";
		}
		//polynom.coef[i]!=0 - doesn't work
		if (!(polynom.coef[i]+1 == 1)) {
			str += bigintToString(polynom.coef[i]);
			
			if (i != 0) {
				str += "x^" + std::to_string(i);
			}
		}
	} 
	if (str == "") {
		str = "0";
	}

	stream << str;
	return stream;
}

std::istream &operator >> (std::istream &stream, Polynom &polynom) {
	int n = 0;
	std::cout << "Enter polynomial degree: ";
	stream >> n;
	n++;
	if (n != polynom.degree) {
		delete[] polynom.coef;
		polynom.degree = n;
		polynom.coef = new bigint[n];
		for (int i = 0; i < n; i++)
			polynom.coef[i] = 0.0;
	}
	std::cout << "Enter polynomial coefficients: ";
	for (int i = n-1; i >= 0; i--)
		stream >> polynom.coef[i];
	return stream;
}


int main()
{
	Polynom p1(0);
	Polynom p2(0);
	std::cin >> p1;
	std::cin >> p2;
	std::cout << "Polynoms:\n" << p1 << std::endl << p2 << std::endl;

	std::cout << "p1 / p2: " << p1 / p2 << std::endl;
	std::cout << "p1 % p2: " << p1 % p2 << std::endl;


    return 0;
}


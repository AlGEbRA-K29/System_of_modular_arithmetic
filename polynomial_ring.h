#pragma once
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "inverse.h"
#include "bigint.h"
#include <exception>




class polynomial_ring {
	void trim() {
		auto it = data.begin();
		while (it != data.end()) {
			if (it->second == bigint(0) || it->second == 0) data.erase(it++);
			else it++;
		}
	}

	void add(int pow, const bigint& coefficient) {
		data[pow] = modulo(data[pow] + coefficient);
	}

	void updateElem(int pow, const bigint& coeff, bool signPow, bool signCoefficient, bool coefficientChanged) {
		auto coefficient = modulo(coeff);
		pow *= (signPow ? -1 : 1);
		if (coefficient == 0 && !coefficientChanged) {
			coefficient = 1;
		}
		if (signCoefficient) coefficient = modulo(-coefficient);
		add(pow, coefficient);
	}

	bool checkMod(bigint& mod_)
	{
		if (mod_ <= bigint("1"))
			return false;
		if (mod_ <= bigint("3"))
			return true;
		if (mod_ % bigint("3") == 0 || mod_ % bigint("2") == 0)
			return false;

		bigint sqrtMod = mod_.sqrt();

		for (bigint i = 5; i < sqrtMod; i += bigint("6"))
		{
			if (mod_ % i == 0 || mod_ % (i + 2) == 0)
				return false;
		}


		return true;
	}

	bigint modulo(bigint bint) const
	{
		if (!bint.isPositive())
		{
			bigint temp = -(bint / modulus) + 1;
			bint += temp * modulus;
		}
		bint = bint % modulus;

		return bint;
	}

	void checkFieldOrders(const polynomial_ring& rhs) const {
		if (this->modulus != rhs.modulus) {
			throw std::invalid_argument("Fields have different orders");
		}
	}

	/*[[maybe_unused]] [[nodiscard]] bigint inverseElement(const bigint& to_inverse) {
		for (bigint i = 1_BI; i < modulus; ++i) {
			if (((to_inverse % modulus) * (i % modulus)) % modulus == 1_BI) {
				return i;
			}
		}

		return 0_BI;
	}*/

public:
	polynomial_ring() :modulus(1) {};

	polynomial_ring(std::vector<bigint> keys, bigint mod_ = 1) {


		try
		{
			if (!checkMod(mod_))
				throw(std::invalid_argument("Invalid modulus"));

			modulus = mod_;
			for (auto i = 0; i < keys.size(); ++i) {
				if (keys[i] != 0) data[i] = modulo(keys[i]);
			}
			trim();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}


	}

	polynomial_ring(std::string str, bigint mod_ = 1) {
		try
		{
			if (!checkMod(mod_))
				throw(std::invalid_argument("Invalid modulus"));
			modulus = mod_;
			std::stringstream ss(str);
			ss >> *this;
			trim();
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	friend std::ostream& operator<<(std::ostream& ss, const polynomial_ring& rhs) {
		auto p = rhs;
		p.trim();
		if (p.data.empty()) {
			ss << "0";
			return ss;
		}

		bool isFirst = true;

		for (auto it = p.data.rbegin(); it != p.data.rend(); ++it) {
			if (!isFirst) ss << (it->second < 0 ? " - " : " + ");
			else {
				if (it->second < 0) ss << "-";
				isFirst = false;
			}

			auto value = it->second.abs();
			if (value != 1 || it->first == 0) {
				ss << value;
			}
			if (it->first != 0) {
				if (value != 1) ss << "*";
				ss << "x";
				if (it->first != 1) ss << "^" << it->first;
			}
		}

		return ss;
	}

	friend std::istream& operator>>(std::istream& ss, polynomial_ring& rhs) {
		std::string str;
		ss >> str;
		bool isPow = false;
		bool signCoefficient = false;
		bool signPow = false;
		bool coefficientChanged = false;
		bigint coefficient;
		int pow = 0;
		for (int i = 0, n = str.size(); i < n; i++) {
			if (isdigit(str[i])) {
				if (isPow) pow = pow * 10 + (int)(str[i] - '0');
				else {
					coefficient = coefficient * 10 + (int)(str[i] - '0');
					coefficientChanged = true;
				}
			}
			else if (str[i] == '-' || str[i] == '+') {
				if (isPow) {
					if (pow == 0) {
						signPow = str[i] == '-';
					}
					else {
						rhs.updateElem(pow, coefficient, signPow, signCoefficient, coefficientChanged);
						signPow = false;
						signCoefficient = str[i] == '-';
						coefficient = 0;
						pow = 0;
						isPow = false;
						coefficientChanged = false;
					}
				}
				else {
					signCoefficient = str[i] == '-';
				}
			}
			else if (str[i] == '^') {
				isPow = true;
			}
		}



		rhs.updateElem(pow, coefficient, signPow, signCoefficient, coefficientChanged);

		return ss;
	}
	polynomial_ring divide(const polynomial_ring& a, const polynomial_ring& b) {
		if (a.getModulus() != b.getModulus()) {
			throw std::invalid_argument("Fields have different orders");
			return polynomial_ring(std::vector<bigint>(0), a.getModulus());
		}
		int powerA = a.getDegree();
		int powerB = b.getDegree();
		//std::cout << b.getData().size();
		if (b.getData().size() == 0)
		{
			std::cout << "divide by 0" << "\n";
			return polynomial_ring(std::vector<bigint>(0), a.getModulus());
		}

		if (a.getData().size() == 0 || powerB > powerA) {
			return polynomial_ring(std::vector<bigint>(0), a.getModulus());
		}

		auto current = polynomial_ring(a);
		auto output = polynomial_ring("", b.getModulus());
		polynomial_ring x("x^1", b.getModulus());
		bigint bigPowInverse = modInverse((--b.getData().end())->second, b.getModulus());
		std::vector <bigint>result(powerA + 1);
		while ((--current.getData().end())->first >= powerB) {
			bigint koef = (--current.getData().end())->second * bigPowInverse;

			result[(--current.getData().end())->first - powerB] = koef;

			polynomial_ring subtractor = b * koef;

			for (bigint i = 0; i < (--current.getData().end())->first - powerB; i++) {
				subtractor = subtractor * polynomial_ring("x^1", subtractor.getModulus());
			}

			current = current - subtractor;


			if (current.getData().empty()) {
				break;
			}
		}

		return polynomial_ring(result, b.getModulus());
	}

	polynomial_ring remainder(const polynomial_ring& a, const polynomial_ring& b) {
		if (a.getModulus() != b.getModulus()) {
			throw std::invalid_argument("Fields have different orders");
			return polynomial_ring(std::vector<bigint>(0), a.getModulus());
		}
		if (b.getData().size() == 0)
		{
			std::cout << "divide by 0" << "\n";
			return polynomial_ring(std::vector<bigint>(0), a.getModulus());
		}
		int powerA = a.getDegree();
		int powerB = b.getDegree();
		if (a.getData().size() == 0) {
			return polynomial_ring(std::vector<bigint>(0), a.getModulus());
		}

		polynomial_ring div = divide(a, b);

		if (powerB > powerA || div.getData().empty()) {
			return polynomial_ring(a);
		}

		return a - (div * b);
	}

	polynomial_ring polynom_gcd(const polynomial_ring& a, const polynomial_ring& b) {

		if (b.getData().empty()) {
			return a;
		}
		if (a.getDegree() < b.getDegree()) {
			return polynom_gcd(b, a);
		}
		return polynom_gcd(b, remainder(a, b));
	}

	bool isIrreducible()
	{
		int power = (data.rbegin())->first;
		if (power == 0 || data.empty())
			return false;
		auto f = *this;
		f.normalize();
		for (bigint i = 0_BI; i <= power / 2; i++)
		{
			std::stringstream SS;
			if (i != 0_BI)
				SS << "x^" << modulus.pow(i);
			else
				SS << "1";
			polynomial_ring g = polynomial_ring(SS.str(), modulus) - polynomial_ring({ 0_BI, 1_BI }, modulus);
			std::cout << g <<"\t" << i << std::endl;
			g = divide(g, f);
			std::cout << g << "\t" << i <<  std::endl;
			if (!g.getData().empty())
			{ 
				if (polynom_gcd(f, g).getData().rbegin()->first > 0)
				{
					std::cout << polynom_gcd(f, g) << std::endl;
					return false;
				}
			}
		}
		return true;
	}
	
	friend bool operator==(const polynomial_ring& lhs, const polynomial_ring& rhs) {
		return lhs.data == rhs.data && lhs.modulus == rhs.modulus;
	}

	friend bool operator!=(const polynomial_ring& lhs, const polynomial_ring& rhs) {
		return lhs.data != rhs.data || lhs.modulus != rhs.modulus;
	}

	[[nodiscard]] polynomial_ring derivative() const {
		auto rhs = *this;
		auto output = polynomial_ring();

		for (const auto& p : rhs.data) {
			output.data[p.first - 1] = modulo(output.data[p.first - 1] + p.second * (bigint)p.first);
		}

		output.trim();
		return output;
	}

	[[nodiscard]] bigint get_value(bigint x) const {
		auto rhs = *this;
		bigint ans = 0;

		for (const auto& p : rhs.data) {
			ans += p.second * x.pow((bigint)p.first);
		}

		return modulo(ans);
	}

	[[nodiscard]] polynomial_ring operator+() const {
		return *this;
	}

	[[nodiscard]] polynomial_ring operator-() const {
		return (*this) * (-1);
	}

	[[nodiscard]] polynomial_ring operator+(const polynomial_ring& rhs) const {
		checkFieldOrders(rhs);

		auto output = *this;

		for (const auto& p : rhs.data) {
			output.data[p.first] = modulo(output.data[p.first] + p.second);
		}

		output.trim();
		return output;
	}

	[[nodiscard]] polynomial_ring operator-(const polynomial_ring& rhs) const {
		checkFieldOrders(rhs);

		auto output = *this;
		for (const auto& p : rhs.data) {
			output.data[p.first] = modulo(output.data[p.first] - p.second);
		}

		output.trim();
		return output;
	}

	[[nodiscard]] polynomial_ring operator*(const polynomial_ring& rhs) const {
		checkFieldOrders(rhs);

		auto output = polynomial_ring();
		output.modulus = rhs.modulus;

		for (const auto& p1 : (*this).data) {
			for (const auto& p2 : rhs.data) {
				output.data[p1.first + p2.first] = modulo(output.data[p1.first + p2.first] + p1.second * p2.second);
			}
		}

		output.trim();
		return output;
	}

	[[nodiscard]] polynomial_ring operator*(const bigint& number) const {
		auto output = *this;
		for (const auto& p : output.data) {
			output.data[p.first] = modulo(output.data[p.first] * number);
		}

		output.trim();
		return output;
	}


	//Prokopchuk's code
	void normalize() {
		const auto highest_degree = data.rbegin();
		if (highest_degree == data.rend() || highest_degree->second == 1_BI) {
			return;
		}

		bigint multiplier = modInverse(highest_degree->second,this->modulus);

		for (auto& p : data) {
			p.second = modulo(multiplier * p.second);
		}

		trim();
	}

	polynomial_ring quickPow(polynomial_ring poly, bigint power) const {
		

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

		return result;
	}
	

	polynomial_ring& operator+=(const polynomial_ring& rhs) {
		return *this = *this + rhs;
	}

	polynomial_ring& operator-=(const polynomial_ring& rhs) {
		return *this = *this - rhs;
	}

	polynomial_ring& operator*=(const polynomial_ring& rhs) {
		return *this = *this * rhs;
	}

	std::map<int, bigint> getData() const {
		return data;
	}

	bigint getModulus() const {
		return modulus; //prime
	}

	int getDegree() const {
		const auto highest_degree = data.rbegin();
		return highest_degree == data.rend() ? 0 : highest_degree->first;
	}
private:
	std::map<int, bigint> data;
	bigint modulus;
};


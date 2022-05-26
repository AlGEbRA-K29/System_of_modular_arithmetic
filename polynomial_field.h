#pragma once
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "big_integers/bigint.h"
#include <exception>

/*
* NOTE : 
* 
* Class polynomial_field has inverseElement() method, which needs to be replaced by 
* function from task 1.2 (find inverse element in field)
*/

class polynomial_field {
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

	void checkFieldOrders(const polynomial_field& rhs) const {
		if (this->modulus != rhs.modulus) {
			throw std::invalid_argument("Fields have different orders");
		}
	}

	[[maybe_unused]] [[nodiscard]] bigint inverseElement(const bigint& to_inverse) {
		for (bigint i = 1_BI; i < modulus; ++i) {
			if (((to_inverse % modulus) * (i % modulus)) % modulus == 1_BI) {
				return i;
			}
		}

		return 0_BI;
	}

public:
	polynomial_field() :modulus(1) {};

	polynomial_field(std::vector<bigint> keys, bigint mod_ = 1) {


		try
		{
			if (!checkMod(mod_))
				throw(std::invalid_argument("Invalid modulus"));

			modulus = mod_;
			for (auto i = 0; i < keys.size(); ++i) {
				if (keys[i] != 0) data[i] = modulo(keys[i]);
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}


	}

	polynomial_field(std::string str, bigint mod_ = 1) {
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

	friend std::ostream& operator<<(std::ostream& ss, const polynomial_field& rhs) {
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

	friend std::istream& operator>>(std::istream& ss, polynomial_field& rhs) {
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

	[[nodiscard]] polynomial_field derivative() const {
		auto rhs = *this;
		auto output = polynomial_field();

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

	[[nodiscard]] polynomial_field operator+() const {
		return *this;
	}

	[[nodiscard]] polynomial_field operator-() const {
		return (*this) * (-1);
	}

	[[nodiscard]] polynomial_field operator+(const polynomial_field& rhs) const {
		checkFieldOrders(rhs);

		auto output = *this;

		for (const auto& p : rhs.data) {
			output.data[p.first] = modulo(output.data[p.first] + p.second);
		}

		output.trim();
		return output;
	}

	[[nodiscard]] polynomial_field operator-(const polynomial_field& rhs) const {
		checkFieldOrders(rhs);

		auto output = *this;
		for (const auto& p : rhs.data) {
			output.data[p.first] = modulo(output.data[p.first] - p.second);
		}

		output.trim();
		return output;
	}

	[[nodiscard]] polynomial_field operator*(const polynomial_field& rhs) const {
		checkFieldOrders(rhs);

		auto output = polynomial_field();
		output.modulus = rhs.modulus;

		for (const auto& p1 : (*this).data) {
			for (const auto& p2 : rhs.data) {
				output.data[p1.first + p2.first] = modulo(output.data[p1.first + p2.first] + p1.second * p2.second);
			}
		}

		output.trim();
		return output;
	}

	[[nodiscard]] polynomial_field operator*(const bigint& number) const {
		auto output = *this;
		for (const auto& p : output.data) {
			output.data[p.first] = modulo(output.data[p.first] * number);
		}

		output.trim();
		return output;
	}

	void normalize() {
		const auto highest_degree = data.rbegin();
		if (highest_degree == data.rend() || highest_degree->second == 1_BI) {
			return;
		}

		bigint multiplier = inverseElement(highest_degree->second);

		for (auto& p : data) {
			p.second = modulo(multiplier * p.second);
		}

		trim();
	}

	polynomial_field quickPow(bigint power) const {
		if (power < 1_BI) {
			throw std::invalid_argument("Power value must be greater than 0");
		}

		polynomial_field result({ 1_BI }, modulus);
		polynomial_field multiplier = *this;

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

	polynomial_field& operator+=(const polynomial_field& rhs) {
		return *this = *this + rhs;
	}

	polynomial_field& operator-=(const polynomial_field& rhs) {
		return *this = *this - rhs;
	}

	polynomial_field& operator*=(const polynomial_field& rhs) {
		return *this = *this * rhs;
	}

	std::map<int, bigint> getData() const {
		return data;
	}

	bigint getModulus() const {
		return modulus;
	}
private:
	std::map<int, bigint> data;
	bigint modulus;
};

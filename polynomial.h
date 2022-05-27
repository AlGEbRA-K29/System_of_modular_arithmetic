#pragma once
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "big_integers/bigint.h"

class polynomial {
		void trim() {
			auto it = data.begin();
			while (it != data.end()) {
				if (it->second == bigint(0) || it->second == 0) data.erase(it++);
				else it++;
			}
		}
		void add(int pow, const bigint& coefficient) {
			data[pow] += coefficient;
		}

		void updateElem(int pow, const bigint& coeff, bool signPow, bool signCoefficient, bool coefficientChanged) {
			auto coefficient = coeff;
			pow *= (signPow ? -1 : 1);
			if (coefficient == 0 && !coefficientChanged) {
				coefficient = 1;
			}
			if (signCoefficient) coefficient = -coefficient;
			add(pow, coefficient);
		}
	public:
		polynomial() = default;

		polynomial(std::vector<bigint> keys) {
			for (auto i = 0; i < keys.size(); ++i) {
				if (keys[i] != 0) data[i] = keys[i];
			}
		}

		polynomial(std::string str) {
			std::stringstream ss(str);
			ss >> *this;
			trim();
		}

		friend std::ostream& operator<<(std::ostream& ss, const polynomial& rhs) {
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

		friend std::istream& operator>>(std::istream& ss, polynomial& rhs) {
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
				} else if (str[i] == '-' || str[i] == '+') {
					if (isPow) {
						if (pow == 0) {
							signPow = str[i] == '-';
						} else {
							rhs.updateElem(pow, coefficient, signPow, signCoefficient, coefficientChanged);
							signPow = false;
							signCoefficient = str[i] == '-';
							coefficient = 0;
							pow = 0;
							isPow = false;
							coefficientChanged = false;
						}
					} else {
						signCoefficient = str[i] == '-';
					}
				} else if (str[i] == '^') {
					isPow = true;
				}
			}

			rhs.updateElem(pow, coefficient, signPow, signCoefficient, coefficientChanged);

			return ss;
		}

		[[nodiscard]] polynomial derivate() const {
			auto rhs = *this;
			auto output = polynomial();
			for (const auto& p : rhs.data) {
				output.data[p.first - 1] += p.second * (bigint)p.first;
			}
			return output;
		}

		[[nodiscard]] bigint get_value(bigint x) const {
			auto rhs = *this;
			bigint ans = 0;
			auto output = polynomial();
			for (const auto& p : rhs.data) {
				ans += p.second * x.pow((bigint)p.first);
			}
			return ans;
		}


		[[nodiscard]] polynomial operator+() const {
			return *this;
		}

		[[nodiscard]] polynomial operator-() const {
			return (*this) * (-1);
		}

		[[nodiscard]] polynomial operator+(const polynomial& rhs) const {
			auto output = *this;
			for (const auto& p : rhs.data) {
				output.data[p.first] += p.second;
			}
			return output;
		}

		[[nodiscard]] polynomial operator-(const polynomial& rhs) const {
			auto output = *this;
			for (const auto& p : rhs.data) {
				output.data[p.first] -= p.second;
			}
			return output;
		}

		[[nodiscard]] polynomial operator*(const polynomial& rhs) const {
			auto output = polynomial();
			for (const auto& p1 : (*this).data) {
				for (const auto& p2 : rhs.data) {
					output.data[p1.first + p2.first] += p1.second * p2.second;
				}
			}
			return output;
		}

		[[nodiscard]] polynomial operator*(const bigint& number) const {
			auto output = *this;
			for (const auto& p : output.data) {
				output.data[p.first] *= number;
			}
			return output;
		}

		polynomial& operator+=(const polynomial& rhs) {
			return *this = *this + rhs;
		}

		polynomial& operator-=(const polynomial& rhs) {
			return *this = *this - rhs;
		}

		polynomial& operator*=(const polynomial& rhs) {
			return *this = *this * rhs;
		}

		std::map<int, bigint> getData() {
			return data;
		}
		[[nodiscard]] polynomial operator/(const polynomial& rhs) const {
			auto temp = *this;
			int tempP = (--temp.data.end())->first + 1;
			int rhsP = (--rhs.data.end())->first + 1;
			bigint* tempK = new bigint[tempP];
			bigint* rhsK = new bigint[rhsP];
			for (int i = 0; i < tempP; i++) {
				tempK[i] = 0;
			}
			for (int i = 0; i < rhsP; i++) {
				rhsK[i] = 0;
			}
			for (std::map<int, bigint>::iterator it = temp.data.begin(); it != temp.data.end(); ++it)
				tempK[it->first] = it->second;

			std::map<int, bigint> rhsM = rhs.data;
			for (std::map<int, bigint>::iterator it = rhsM.begin(); it != rhsM.end(); ++it) {
				rhsK[it->first] = it->second;
			}
			Polynom polT(tempP, tempK);
			Polynom polR(rhsP, rhsK);

			Polynom res = polR / polT;

			std::vector<bigint> result(res.degree);
			for (int i = 0; i < res.degree; i++) {
				result[i] = res.coef[i];
			}
			return polynomial(result);
		}
	private:
		std::map<int, bigint> data;
};

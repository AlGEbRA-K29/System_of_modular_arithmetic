#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "../big_integers/bigint.h"

class polynomial {
	void trim() {
		auto it = data.begin();
		while (it != data.end()) {
			if (it->second == bigint(0) || it->second == 0) data.erase(it++);
			else it++;
		}
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
		bigint coefficient = 0;
		int pow = 0;
		for (int i = 0, n = str.size(); i < n; i++) {
			if (isdigit(str[i])) {
				if (isPow) pow = pow * 10 + (int)(str[i] - '0');
				else coefficient = coefficient * 10 + (int)(str[i] - '0');
			}
			else if (str[i] == '-' || str[i] == '+') {
				if (isPow) {
					if (pow == 0) {
						signPow = str[i] == '-';
					}
					else {
						pow *= (signPow ? -1 : 1);
						if (signCoefficient) coefficient = -coefficient;
						rhs.add(pow, coefficient);
						signPow = false;
						signCoefficient = str[i] == '-';
						coefficient = 0;
						pow = 0;
						isPow = false;
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

		pow *= (signPow ? -1 : 1);
		if (signCoefficient) coefficient = -coefficient;
		rhs.add(pow, coefficient);

		return ss;
	}

	void add(int pow, bigint coefficient) {
		data[pow] += coefficient;
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
private:
	std::map<int, bigint> data;
};
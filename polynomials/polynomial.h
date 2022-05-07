#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "../big_integers/bigint.h"

class polynomial {
    void trim() {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->second == 0) data.erase(it--);
        }
    }
public:
	polynomial() = default;

    polynomial(std::vector<bigint> keys) {
        for (auto i = 0; i < keys.size(); ++i) {
            if (keys[i] != 0) data[i] = keys[i];
        }
    }

    friend std::ostream& operator<<(std::ostream& ss, const polynomial& rhs) {
        if (rhs.data.empty()) {
            ss << "0";
            return ss;
        }

        auto p = rhs;
        bool isFirst = true;

        for (auto it = p.data.rbegin(); it != p.data.rend(); ++it) {
            if (!isFirst) ss << (it -> second < 0 ? " - " : " + ");
            else {
                if (it -> second < 0) ss << "-";
                isFirst = false;
            }

            ss << it -> second.abs();
            if (it -> first > 0) {
                ss << "*x";
                if (it -> first != 1) ss << "^" << it -> first;
            }
        }

        return ss;
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
        for (const auto& p1 : (* this).data) {
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
private:
	std::map<uint32_t, bigint> data;
};
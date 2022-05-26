//
// Created by fail on 2/18/22.
//

#ifndef LAB_MOD_BIGINT_H
#define LAB_MOD_BIGINT_H

#include "bigint.h"

[[maybe_unused]] [[nodiscard]] bigint modular_add(const bigint& lhs, const bigint& rhs, const bigint& modulo);

[[maybe_unused]] [[nodiscard]] bigint modular_subtract(const bigint& lhs, const bigint& rhs, const bigint& modulo) ;

[[maybe_unused]] [[nodiscard]] bigint modular_product(const bigint& lhs, const bigint& rhs, const bigint& modulo);\

template <const char* modulo>
struct [[maybe_unused]] mod {
    [[maybe_unused]] mod(int64_t v) noexcept : value(proper_mod(v)) {};
    [[maybe_unused]] mod(const bigint& v) noexcept : value(proper_mod(v)) {};
    constexpr mod() noexcept : value(0) {};
    [[nodiscard]] [[maybe_unused]] explicit operator bigint() const { return value; }
    [[nodiscard]] mod operator+(const mod& other) const { return value + other.value; }
    [[nodiscard]] mod operator-(const mod& other) const { return value - other.value; }
    [[nodiscard]] mod operator*(const mod& other) const { return value * other.value; }
    mod& operator+=(const mod& other) { *this = *this + other; return *this; }
    mod& operator-=(const mod& other) { *this = *this - other; return *this; }
    mod& operator*=(const mod& other) { *this = *this * other; return *this; }
    [[nodiscard]] mod operator+() const noexcept { return *this; }
    [[nodiscard]] mod operator-() const noexcept { return mod<modulo>(-value); }

    friend std::ostream& operator<<(std::ostream& ss, const mod& mm)  {
        ss << mm.value;
        return ss;
    }

    friend std::istream& operator>>(std::istream& ss, mod& mm)  {
        ss >> mm.value;
        mm.value = mm.proper_mod(mm.value);
        return ss;
    }
private:
    [[nodiscard]] bigint proper_mod(bigint val) const {
        bigint m(modulo);
        auto temp = val % m;
        return temp.isPositive() ? temp : (temp + m);
    }
    bigint value = 0;
};

#endif //LAB_MOD_BIGINT_H

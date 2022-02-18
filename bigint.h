//
// Created by fail on 2/18/22.
//

#ifndef LAB_BIGINT_H
#define LAB_BIGINT_H

#include <vector>
#include <cstdint>
#include <ostream>
#include <iostream>
#include <sstream>

static const uint64_t HIGH_MASK = 0xffffffff00000000;

class bigint {
    void trim() {
        while(!data.empty() && *data.rbegin() == 0) data.pop_back();
        if(data.empty()) sign = true;
    }

    /* Calculates abs(lhs) < abs(rhs) */
    [[nodiscard]] static bool unchecked_less(const bigint& lhs, const bigint& rhs) {
        if(lhs.data.size() < rhs.data.size()) return true;
        if(lhs.data.size() > rhs.data.size()) return false;

        int64_t i = lhs.data.size() - 1;

        while(i >= 0) {
            if(lhs.data[i] < rhs.data[i]) return true;
            if(lhs.data[i] > rhs.data[i]) return false;

            --i;
        }

        return false;
    }

    /* Calculates abs(lhs) - abs(rhs) */
    [[nodiscard]] static bigint unchecked_subtract(const bigint& lhs, const bigint& rhs) {
        bigint output;

        if(unchecked_less(lhs, rhs)) {
            return -(unchecked_subtract(rhs, lhs));
        }

        auto lhs_it = lhs.data.begin();
        auto rhs_it = rhs.data.begin();

        bool carry = false;
        while(lhs_it != lhs.data.end() && rhs_it != rhs.data.end()) {
            int64_t result = static_cast<int64_t>(*lhs_it) - static_cast<int64_t>(*rhs_it) - carry;

            if(result < 0) {
                result += 1LLU << 32U;
                carry = true;
            } else {
                carry = false;
            }

            output.data.push_back(static_cast<uint32_t>(result));

            ++lhs_it;
            ++rhs_it;
        }

        while(lhs_it != lhs.data.end()) {
            int64_t result = static_cast<int64_t>(*lhs_it) - carry;

            if(result < 0) {
                result += 1LLU << 32U;
                carry = true;
            } else {
                carry = false;
            }

            output.data.push_back(static_cast<uint32_t>(result));

            ++lhs_it;
        }

        output.trim();

        return output;
    }

    [[deprecated]] static bigint naive_division(const bigint& lhs, const bigint& rhs) {
        bigint result = 0;
        if(lhs.isPositive() ^ rhs.isPositive()) result.sign = false;

        bigint cp = lhs + 1;

        while (unchecked_less(rhs, cp)) {
            cp = unchecked_subtract(cp, rhs);
            result += 1;
        }

        result.trim();

        return result;
    }

public:
    /* TODO: Optimize */
    [[nodiscard]] bigint shift_left(std::size_t count) const {
        auto result = *this;

        result.data.reserve(data.size() + count);

        for(std::size_t i = 0; i < count; ++i) {
            result.data.push_back(0);
        }

        for(int64_t i = data.size() - 1; i >= 0; --i) {
            result.data[i + count] = result.data[i];
        }

        for(std::size_t i = 0; i < count; ++i) {
            result.data[i] = 0;
        }

        return result;
    }

public:
    bigint() = default;

    bigint(uint32_t a) {
        data = { a };
    }

    bigint(int32_t a) {
        data = { static_cast<uint32_t>(std::abs(a)) };
        if(a < 0) sign = false;
    }

    [[nodiscard]] bigint operator+() const {
        return *this;
    }

    [[nodiscard]] bigint operator-() const {
        auto cp = *this;
        cp.sign = -cp.sign;

        return cp;
    }

    /* O(N) algorithmic complexity */
    [[nodiscard]] bigint operator-(const bigint& rhs) const {
        if(!rhs.sign) return *this + (-rhs);
        if(!sign) return -(-(*this) + rhs);

        return unchecked_subtract(*this, rhs);
    }

    /* O(N) algorithmic complexity */
    [[nodiscard]] bigint operator+(const bigint& rhs) const {
        auto it = data.begin();
        auto rhs_it = rhs.data.begin();

        if(sign && !rhs.sign) {
            return unchecked_subtract(*this, rhs);
        }

        if(!sign && rhs.sign) {
            return unchecked_subtract(rhs, *this);
        }

        bigint output;
        if(!rhs.sign && !sign) {
            output.sign = false;
        }

        bool carry = false;
        while(it != data.end() && rhs_it != rhs.data.end()) {
            uint64_t result = static_cast<uint64_t>(*it) + static_cast<uint64_t>(*rhs_it) + carry;
            carry = result & HIGH_MASK;
            output.data.push_back(static_cast<uint32_t>(result));

            ++it;
            ++rhs_it;
        }

        while(it != data.end()) {
            uint64_t result = static_cast<uint64_t>(*it) + carry;
            carry = result & HIGH_MASK;
            output.data.push_back(static_cast<uint32_t>(result));

            ++it;
        }

        while(rhs_it != rhs.data.end()) {
            uint64_t result = static_cast<uint64_t>(*rhs_it) + carry;
            carry = result & HIGH_MASK;
            output.data.push_back(static_cast<uint32_t>(result));

            ++rhs_it;
        }

        if(carry) output.data.push_back(carry);

        return output;
    }

    [[nodiscard]] bigint& operator+=(const bigint& rhs) {
        return *this = *this + rhs;
    }

    [[nodiscard]] bigint& operator-=(const bigint& rhs) {
        return *this = *this - rhs;
    }

    friend std::ostream& operator<<(std::ostream& ss, const bigint& rhs) {
        if(!rhs.sign) ss << "-";

        auto cp = rhs;
        cp.sign = true;

        std::string output;

        while(!cp.data.empty()) {
            auto div = cp / 10;
            output.append(std::to_string((cp - div * 10).data[0]));
            output.append(" ");
            cp = div;
        }

        std::reverse(output.begin(), output.end());
        ss << output;
        return ss;
    }

    /* TODO: non-naive implementation. */
    [[nodiscard]] bigint operator/(const bigint& rhs) const {
        return naive_division(*this, rhs);
    }

    /* Linear time complexity, optimal. */
    [[nodiscard]] bigint operator/(uint32_t num) const {
        auto result = *this;

        uint64_t carry = 0;
        for(std::int64_t idx = data.size() - 1; idx >= 0; --idx) {
            result.data[idx] = (static_cast<uint64_t>(data[idx]) + carry) / num;
            carry = ((static_cast<uint64_t>(data[idx]) + carry) % num) << 32U;
        }

        result.trim();

        return result;
    }

    [[nodiscard]] bigint operator%(const bigint& rhs) const {
        return *this - (*this / rhs * rhs);
    }

    [[nodiscard]] bool isPositive() const {
        return sign;
    }

    [[nodiscard]] bigint operator*(const bigint& rhs) const {
        bigint result = 0;

        result.sign = !(sign ^ rhs.sign);

        result.data = std::vector<std::uint32_t>(data.size() + rhs.data.size());

        for(std::size_t i = 0; i < data.size(); ++i) {
            uint64_t carry = 0;
            for(std::size_t j = 0; j < rhs.data.size(); ++j) {
                uint64_t t = static_cast<std::uint64_t>(data[i]) * rhs.data[j] + result.data[i + j] + carry;
                carry = t >> 32U;
                result.data[i + j] += t;
            }
            result.data[i + rhs.data.size()] += carry;
        }

        result.trim();

        return result;
    }

    [[deprecated]] std::vector<std::uint32_t> getData() { return data; }

private:
    std::vector<std::uint32_t> data;
    bool sign = true;
};

#endif //LAB_BIGINT_H

//
// Created by fail on 2/18/22.
//

#ifndef LAB_HELPERS_H
#define LAB_HELPERS_H

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <limits>
#include <array>
#include <string>
#include <cstdint>
#include <regex>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <cmath>
#include <functional>
#include <numeric>

template <typename T>
[[maybe_unused]] void sort(T& a) {
    std::sort(a.begin(), a.end());
}
template <typename T>
[[maybe_unused]] void sortR(T& a) {
    std::sort(a.begin(), a.end(), std::greater<decltype(a[0])>());
}
template <typename T>
[[maybe_unused]] void reverse(T& a) {
    std::reverse(a.begin(), a.end());
}
template <typename T, typename U>
[[maybe_unused]] bool bSearch(T& a, U b) {
    return std::binary_search(a.begin(), a.end(), b);
}

/* UB */
template<typename T, typename S>
struct std::hash<std::pair<T, S>> {
    std::size_t operator()(const std::pair<T, S>& elem) const noexcept {
        return std::hash<T>{}(elem.first) ^ std::hash<S>{}(elem.second);
    }
};
template<typename T>
struct std::hash<std::vector<T>> {
    std::size_t operator()(const std::vector<T>& elem) const noexcept {
        std::size_t h = 0;
        for(const T& e : elem) h ^= std::hash<T>{}(e);
        return h;
    }
};

template<typename T, typename S>
[[maybe_unused]] std::ostream& operator <<(std::ostream& os, const std::pair<T, S>& f) {
    os << "{" << f.first << ", " << f.second << "}";
    return os;
}
template<typename T, typename S>
[[maybe_unused]] std::ostream& operator <<(std::ostream& os, const std::unordered_map<T, S>& f) {
    for(const auto& i : f) {
        os << "{" << i.first << ": " << i.second << "}\n";
    }

    return os;
}
template<typename T>
[[maybe_unused]] std::ostream& operator <<(std::ostream& os, const std::vector<T>& f) {
    if(f.empty()) {
        os << "{}";
        return os;
    }

    os << "{" << f[0];
    for(std::size_t i = 1; i < f.size(); ++i) os << ", " << f[i];
    os << "}";

    return os;
}
template<typename T>
[[maybe_unused]] std::ostream& operator <<(std::ostream& os, const std::priority_queue<T>& f) {
    std::priority_queue<T> cp = f;
    if(f.empty()) return os;
    os << "{" << cp.top();
    cp.pop();
    while(!cp.empty()) {
        os << ", "<< cp.top();
        cp.pop();
    }
    os << "}";
    return os;
}

template<typename T, typename S>
[[maybe_unused]] std::istream& operator >>(std::istream& is, std::pair<T, S>& f) {
    is >> f.first >> f.second;
    return is;
}

template <int64_t m>
struct [[maybe_unused]] mod {
    [[maybe_unused]] constexpr mod(int64_t v) noexcept : value(proper_mod(v)) {};
    constexpr mod() noexcept : value(0) {};
    [[maybe_unused]] explicit operator int64_t() const noexcept { return value; }
    constexpr mod operator+(const mod& other) const noexcept { return value + other.value; }
    constexpr mod operator-(const mod& other) const noexcept { return value - other.value; }
    constexpr mod operator*(const mod& other) const noexcept { return value * other.value; }
    constexpr mod& operator+=(const mod& other) noexcept { *this = *this + other; return *this; }
    constexpr mod& operator-=(const mod& other) noexcept { *this = *this - other; return *this; }
    constexpr mod& operator*=(const mod& other) noexcept { *this = *this * other; return *this; }
    constexpr mod operator+() const noexcept { return *this; }
    constexpr mod operator-() const noexcept { return mod<m>(-value); }
    template<int64_t T> //DELETE if instantiation with different m is required
    friend std::ostream& operator<<(std::ostream& ss, const mod<T>& mm) noexcept {
        ss << mm.value;
        return ss;
    }
    template<int64_t T> //DELETE if instantiation with different m is required
    friend std::istream& operator>>(std::istream& ss, mod<T>& mm) noexcept {
        ss >> mm.value;
        mm.value = mm.proper_mod(mm.value);
        return ss;
    }
private:
    [[nodiscard]] constexpr int64_t proper_mod(int64_t val) const noexcept { return (val % m >= 0) ? (val % m) : ((val % m) + m); }
    int64_t value = 0;
};
template <int64_t m> constexpr mod<m> operator*(const int64_t& a, const mod<m>& b) noexcept { return b * a; }
template <int64_t m> constexpr mod<m> operator+(const int64_t& a, const mod<m>& b) noexcept { return b + a; }
template <int64_t m> constexpr mod<m> operator-(const int64_t& a, const mod<m>& b) noexcept { return -b + a; }

template <typename T>
using V [[maybe_unused]] = std::vector<T>;
template <typename T>
using PQ [[maybe_unused]] = std::priority_queue<T>;
template <typename T>
using NL [[maybe_unused]] = std::numeric_limits<T>;
template <typename T, typename S>
using U [[maybe_unused]] = std::unordered_map<T, S>;
template <typename T, typename S>
using P [[maybe_unused]] = std::pair<T, S>;

using PI [[maybe_unused]] = std::pair<int64_t, int64_t>;
using VI [[maybe_unused]] = std::vector<int64_t>;
using VS [[maybe_unused]] = std::vector<std::string>;
using I [[maybe_unused]] = int64_t;
using S [[maybe_unused]] = std::string;

#define FI first
#define SE second
#define PB push_back

#define FEACH(A, B) for(const auto& A : ((B)))
#define REP(A, B, C) for(int64_t A = ((B)); A < ((C)); ++A)
#define REPR(A, B) for(int64_t A = ((B)); A >= 0; --A)
#define ALL(A) A.begin(), A.end()

#endif //LAB_HELPERS_H

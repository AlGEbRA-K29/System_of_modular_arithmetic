#pragma once
#include <iostream>
#include <algorithm>

class BigInt {
public:
    bool neg = false;
    std::string number = "0";

    BigInt() {}

    BigInt(const BigInt& other) {
        this->neg = other.neg;
        this->number = other.number;
    }

    BigInt(int number) {
        if (number < 0) {
            this->neg = true;
            number *= -1;
        }

        if (number == 0) {
            this->number = "0";
            return;
        }

        this->number = "";

        while (number > 0) {
            this->number += (number % 10) + '0';
            number /= 10;
        }
    }

    BigInt(long long int number) {
        if (number < 0) {
            this->neg = true;
            number *= -1;
        }

        if (number == 0) {
            this->number = "0";
            return;
        }

        this->number = "";

        while (number > 0) {
            this->number += (number % 10) + '0';
            number /= 10;
        }
    }

    BigInt(unsigned long long int number) {
        if (number < 0) {
            this->neg = true;
            number *= -1;
        }

        if (number == 0) {
            this->number = "0";
            return;
        }

        this->number = "";

        while (number > 0) {
            this->number += (number % 10) + '0';
            number /= 10;
        }
    }

    BigInt(const char* number) {
        std::string number_(number);
        *(this) = number_;
    }

    BigInt(std::string number) {
        while (number[0] == '-') {
            this->neg = !this->neg;
            number.erase(0, 1);
        }

        reverse(number.begin(), number.end());

        while (number.size() > 1 && number[number.size() - 1] == '0')
            number.erase(number.size() - 1, number.size());

        if (number == "")
            number = "0";

        this->number = number;

        if (number == "0")
            this->neg = false;
    }

    friend bool operator == (BigInt first, BigInt second) {
        return first.number == second.number && second.neg == first.neg;
    }

    friend bool operator != (BigInt first, BigInt second) {
        return !(first == second);
    }

    friend bool operator < (BigInt first, BigInt second) {
        if (first.neg && !second.neg) return true;
        if (!first.neg && second.neg) return false;

        if (first.neg && second.neg) {
            first.neg = false;
            second.neg = false;

            return first > second;
        }

        if ((first.number).size() < (second.number).size()) return true;
        if ((first.number).size() > (second.number).size()) return false;

        std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
        std::string temp2 = second.number; reverse(temp2.begin(), temp2.end());

        for (unsigned int i = 0; i < temp1.size(); i++)
            if (temp1[i] < temp2[i])
                return true;
            else if (temp1[i] > temp2[i])
                return false;

        return false;
    }

    friend bool operator <= (BigInt first, BigInt second) {
        return (first == second) || (first < second);
    }

    friend bool operator > (BigInt first, BigInt second) {
        if (!first.neg && second.neg) return true;
        if (first.neg && !second.neg) return false;

        if (first.neg && second.neg) {
            first.neg = false;
            second.neg = false;

            return first < second;
        }

        if ((first.number).size() > (second.number).size()) return true;
        if ((first.number).size() < (second.number).size()) return false;

        std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
        std::string temp2 = second.number; reverse(temp2.begin(), temp2.end());

        for (unsigned int i = 0; i < temp1.size(); i++)
            if (temp1[i] > temp2[i])
                return true;
            else if (temp1[i] < temp2[i])
                return false;

        return false;
    }

    friend bool operator >= (BigInt first, BigInt second) {
        return (first == second) || (first > second);
    }

    void operator = (unsigned long long int number) {
        if (number < 0) {
            this->neg = true;
            number *= -1;
        }

        this->number = "";

        while (number > 0) {
            this->number += (number % 10) + '0';
            number /= 10;
        }
    }

    friend std::istream& operator >> (std::istream& in, BigInt& BigInt) {
        std::string number; in >> number;

        BigInt.neg = false;

        while (number[0] == '-') {
            BigInt.neg = !BigInt.neg;
            number.erase(0, 1);
        }

        reverse(number.begin(), number.end());

        while (number.size() > 1 && number[number.size() - 1] == '0')
            number.erase(number.size() - 1, number.size());

        BigInt.number = number;

        if (number == "0")
            BigInt.neg = false;

        return in;
    }

    friend std::ostream& operator << (std::ostream& out, const BigInt& BigInt) {
        std::string number = BigInt.number;
        reverse(number.begin(), number.end());

        if (BigInt.neg)
            number = '-' + number;

        out << number;

        return out;
    }

    friend void swap(BigInt& first, BigInt& second) {
        BigInt temp(first);

        first = second;
        second = temp;
    }

    friend BigInt abs(BigInt BigInt) {
        BigInt.neg = false;

        return BigInt;
    }

    friend BigInt operator + (BigInt first, BigInt second) {
        bool neg = false;

        if (!first.neg && second.neg) {
            second.neg = false; return first - second;
        }

        if (first.neg && !second.neg) {
            first.neg = false; return second - first;
        }

        if (first.neg && second.neg) {
            neg = true;
            first.neg = second.neg = false;
        }

        int n = first.number.size();
        int m = second.number.size();

        int carry = 0;

        std::string result;

        for (int i = 0; i < std::max(n, m); i++) {
            int add = carry;

            if (i < n) add += first.number[i] - '0';
            if (i < m) add += second.number[i] - '0';

            carry = add / 10;

            result += add % 10 + '0';
        }

        if (carry != 0)
            result += carry + '0';

        reverse(result.begin(), result.end());

        BigInt result_(result);
        result_.neg = neg;

        return result_;
    }

    friend BigInt operator + (BigInt BigInt) {
        return BigInt;
    }

    friend BigInt operator - (BigInt first, BigInt second) {
        if (second.neg) {
            second.neg = false;
            return first + second;
        }

        if (first.neg) {
            second.neg = true;
            return first + second;
        }

        bool neg = false;

        if (first < abs(second)) {
            neg = true;

            swap(first, second);
            first = abs(first);
        }

        int n = first.number.size();
        int m = second.number.size();

        int carry = 0;

        std::string result;

        for (int i = 0; i < std::max(n, m); i++) {
            int add = carry;

            if (i < n) add += first.number[i] - '0';
            if (i < m) add -= second.number[i] - '0';

            if (add < 0) {
                carry = -1;
                result += add + 10 + '0';
            }

            else {
                carry = 0;
                result += add + '0';
            }
        }

        reverse(result.begin(), result.end());

        BigInt result_(result);

        result_.neg = neg;

        return result_;
    }

    friend BigInt operator - (BigInt second) {
        BigInt first("0"); return first - second;
    }

    friend BigInt operator * (BigInt first, BigInt second) {
        bool neg = first.neg != second.neg;

        first.neg = false;
        second.neg = false;

        int n = first.number.size();
        int m = second.number.size();

        BigInt result_;

        for (int i = 0; i < n; i++) {
            int carry = 0;

            std::string result;

            for (int j = 0; j < i; j++)
                result += '0';

            for (int j = 0; j < m; j++) {
                int add = carry + (first.number[i] - '0') * (second.number[j] - '0');

                carry = add / 10;

                result += add % 10 + '0';
            }

            if (carry != 0)
                result += carry + '0';

            reverse(result.begin(), result.end());

            BigInt current(result);

            result_ += current;
        }

        result_.neg = neg;

        return result_;
    }

    friend BigInt operator / (BigInt first, BigInt second) {
        if (second == "0")
            throw "?????????????? ???? 0";

        bool neg = first.neg != second.neg;

        first.neg = false;
        second.neg = false;

        BigInt quotient;

        int i = first.size() - 1;

        BigInt current(first.number[i] - '0');

        --i;

        while (true) {
            BigInt result = current;

            bool l = false;

            while (result < second && i >= 0) {
                result = result * 10 + (first.number[i--] - '0');

                if (l)
                    quotient *= 10;

                l = true;
            }

            int c = 0;

            BigInt result_(result);

            while (result_ >= second) {
                result_ -= second;
                c++;
            }

            quotient = quotient * 10 + c;

            current = result_;

            if (i < 0)
                break;
        }

        quotient.neg = neg;

        return quotient;
    }

    friend BigInt operator % (BigInt first, BigInt second) {
        if (second == "0")
            throw "???????????? ?????? 0";

        first.neg = false;
        second.neg = false;

        int i = first.size() - 1;

        BigInt current(first.number[i] - '0');

        --i;

        while (true) {
            BigInt result = current;

            while (result < second && i >= 0)
                result = result * 10 + (first.number[i--] - '0');

            int c = 0;

            BigInt result_(result);

            while (result_ >= second) {
                result_ -= second;
                c++;
            }

            current = result_;

            if (i < 0)
                break;
        }

        current.neg = second.neg;

        return current;
    }

    friend BigInt pow(BigInt x, BigInt y, BigInt mod) {
        if (mod != 0)
            x %= mod;

        BigInt res = 1;

        while (y != 0) {
            if (y % 2 == 1) {
                res *= x;

                if (mod != 0)
                    res %= mod;
            }

            x *= x;

            if (mod != 0)
                x %= mod;

            y /= 2;
        }

        return res;
    }

    friend BigInt operator & (BigInt first_, BigInt second_) {
        std::string first = first_.int_to_base(2);
        std::string second = second_.int_to_base(2);

        unsigned int n = std::min(first.size(), second.size());

        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        std::string result(n, '~');

        for (unsigned int i = 0; i < n; i++) {
            if (first[i] == '1' && second[i] == '1')
                result[i] = '1';
            else
                result[i] = '0';
        }

        reverse(result.begin(), result.end());

        return BigInt().base_to_int(result, 2);
    }

    friend BigInt operator | (BigInt first_, BigInt second_) {
        std::string first = first_.int_to_base(2);
        std::string second = second_.int_to_base(2);

        unsigned int n = std::max(first.size(), second.size());

        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        std::string result(n, '~');

        for (unsigned int i = 0; i < n; i++) {
            if (first.size() <= i || second.size() <= i) {
                if (first.size() > i) result[i] = first[i];
                if (second.size() > i) result[i] = second[i];

                continue;
            }

            if (first[i] == '1' || second[i] == '1')
                result[i] = '1';
            else
                result[i] = '0';
        }

        reverse(result.begin(), result.end());

        return BigInt().base_to_int(result, 2);
    }

    friend BigInt operator ^ (BigInt first_, BigInt second_) {
        std::string first = first_.int_to_base(2);
        std::string second = second_.int_to_base(2);

        unsigned int n = std::max(first.size(), second.size());

        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        std::string result(n, '~');

        for (unsigned int i = 0; i < n; i++) {
            if (first.size() <= i || second.size() <= i) {
                if (first.size() > i) {
                    if (first[i] == '0')
                        result[i] = '0';
                    else
                        result[i] = '1';
                }

                if (second.size() > i) {
                    if (second[i] == '0')
                        result[i] = '0';
                    else
                        result[i] = '1';
                }

                continue;
            }

            if (first[i] == second[i])
                result[i] = '0';
            else
                result[i] = '1';
        }

        reverse(result.begin(), result.end());

        return BigInt().base_to_int(result, 2);
    }

    friend BigInt operator << (BigInt first, BigInt second) {
        BigInt x = pow(2, second, 0);

        return first * x;
    }

    friend BigInt operator >> (BigInt first, BigInt second) {
        BigInt x = pow(2, second, 0);

        return first / x;
    }

    int to_int(BigInt BigInt) {
        int n = 0;

        for (int i = BigInt.number.size() - 1; i >= 0; i--)
            n = (n * 10) + (BigInt.number[i] - '0');

        return n;
    }

    std::string int_to_base(int base) {
        std::string result;

        BigInt BigInt_(*this);

        while (BigInt_ > 0) {
            BigInt r = BigInt_ % base;

            if (r >= 10)
                result += (char)(to_int(r / 10) + 'A');
            else
                result += (char)(to_int(r) + '0');

            BigInt_ /= base;
        }

        reverse(result.begin(), result.end());

        return result;
    }

    BigInt base_to_int(std::string str, int base) {
        BigInt result;

        for (unsigned int i = 0; i < str.size(); i++) {
            BigInt add;

            if ('0' <= str[i] && str[i] <= '9')
                add += str[i] - '0';
            else
                add += (str[i] - 'A') + 10;

            result = result * base + add;
        }

        return result;
    }

    int size() {
        return this->number.size();
    }

    void operator ++ () { *(this) = *(this) + 1; }
    void operator -- () { *(this) = *(this) - 1; }

    void operator += (BigInt BigInt) { *(this) = *(this) + BigInt; }
    void operator -= (BigInt BigInt) { *(this) = *(this) - BigInt; }

    void operator *= (BigInt BigInt) { *(this) = *(this) * BigInt; }
    void operator /= (BigInt BigInt) { *(this) = *(this) / BigInt; }
    void operator %= (BigInt BigInt) { *(this) = *(this) % BigInt; }

    void operator &= (BigInt BigInt) { *(this) = *(this) & BigInt; }
    void operator |= (BigInt BigInt) { *(this) = *(this) | BigInt; }
    void operator ^= (BigInt BigInt) { *(this) = *(this) ^ BigInt; }

    void operator <<= (BigInt BigInt) { *(this) = *(this) << BigInt; }
    void operator >>= (BigInt BigInt) { *(this) = *(this) >> BigInt; }
};

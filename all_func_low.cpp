#include <iostream>
#include "polynomial.h"
#include "polynomial_field.h"
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
#include "mod_sqrt.h"
#include <optional>
#include <vector>
#include "findingCircularPolynomial.h"

//Euler_and_Karmayr
bigint findLcm(vector<bigint> arr)
{
    bigint ans = arr[0];
    for (int i = 1; i < arr.size(); i++)
        ans = (((arr[i] * ans)) / (gcd_f(arr[i], ans)));

    return ans;
}

bigint funcL(bigint a, bigint b){
    if(a==2 && b>bigint(3)){
        return a.pow(b-2);
    }
    return a.pow(b-1)*(a-1);
}

bigint carmaicle(vector<bigint> arr, int n)
{
    if(n==0) return 1;
    vector<bigint> newV;
    for(int i =0;i<n;i=i+2){
        newV.push_back(funcL(arr[i], arr[i+1]));
    }
    bigint ans = findLcm(newV);
    return ans;
}

bigint eurel(bigint n)
{
    bigint result = n;
    for(bigint i=2; i*i<=n; i++)
    {
        if (n % i == 0)
        {
            result -= result/i;
            while(n % i == 0)
                n /= i;
        }
    }
    if (n != 1)
        result -= result/n;
    return result;
}


[[nodiscard]] std::vector<bigint> factorizeForEurelFunction(bigint n, std::vector<bigint> factors) {
    if (n == 1)
        return factors;
    if (isPrime(n)) {
        if( factors.size()!=0 &&  n == factors[factors.size()-2]){
            factors[factors.size()-1] = factors[factors.size()-1]+1;
         }
        else{
            factors.push_back(n);
            factors.push_back(1);
        }                                                    
        return factors;
    }
    bigint divisor = PollardRho(n);
    factors = factorizeForEurelFunction(divisor, factors);
    factors = factorizeForEurelFunction(n / divisor, factors);
    return factors;
}





//Factorization
[[nodiscard]] std::vector<bigint> naiveAlgorithm(bigint to_factorize) {
    if (to_factorize < 2_BI) {
        return {};
    }

    std::vector<bigint> result;

    while (to_factorize % 2_BI == 0_BI) {
        result.push_back(2_BI);
        to_factorize /= 2_BI;
    }

    bigint cur_divisor = 3_BI;

    while (cur_divisor * cur_divisor <= to_factorize) {
        if (to_factorize % cur_divisor == 0) {
            result.push_back(cur_divisor);
            to_factorize /= cur_divisor;
        }
        else {
            cur_divisor += 2_BI;
        }
    }

    if (to_factorize != 1_BI) {
        result.push_back(to_factorize);
    }

    return result;
}


bigint gcd_f(bigint a, bigint b) {
    while (a != b) {
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}

bigint PollardRho(bigint n)
{
    if (n == 1_BI) return n;

    if (n % 2 == 0_BI) return 2_BI;

    bigint d = n;
    bigint x;
    bigint y;
    bigint c;
    while (d == n) {
        srand(std::time(NULL));

        x = (bigint(rand() + 1) % (n - 2_BI)) + 2_BI;
        y = x;

        c = (bigint(rand() + 1) % (n - 1_BI)) + 1_BI;
        d = 1_BI;

        while (d == 1_BI)
        {
            x = (((x*x) % n) + c + n) % n;
            y = (((y*y) % n) + c + n) % n;
            y = (((y*y) % n) + c + n) % n;

            if ((x - y).abs() == 0_BI) {
                d = n;
            }
            else {
                d = gcd_f((x - y).abs(), n);
            }

            if (d == n) break;
            if (d != 1_BI) {
                return d;
            }
        }
    }

    return d;
}

bool isPrime(bigint n)
{
    if (n <= 1_BI)
        return false;
    if (n <= 3_BI) {
        return true;
    }

    if (n % 2 == 0_BI || n % 3 == 0_BI)
        return false;

    for (int i = 5; bigint(i * i) <= n; i = i + 6)
        if (n % i == 0_BI || n % (i + 2) == 0_BI)
            return false;
    return true;

}

void PrintFactors(bigint n, std::vector<bigint> factors) {
    bool is_first = true;
    std::cout << n << " = ";
    for (const bigint& factor : factors) {
        if (!is_first) {
            std::cout << " * ";
        }
        std::cout << factor;
        is_first = false;
    }
    std::cout << "\n";
}

[[nodiscard]] std::vector<bigint> factorize(bigint n, std::vector<bigint> factors)
{
    if (n == 1_BI)
        return factors;
    if (isPrime(n))
    {
        factors.push_back(n);
        return factors;
    }

    bigint divisor = PollardRho(n);
    factors = factorize(divisor, factors);
    factors = factorize(n / divisor, factors);
    return factors;
}

[[nodiscard]] std::vector<bigint> Factorization(bigint n, bool isToUsePollard) {
    if (n <= 1_BI) {
        std::vector<bigint> factors;
        factors.push_back(n);
        return factors;
    }
    if (isToUsePollard) {
        std::vector<bigint> factors;
        return factorize(n, factors);
    }
    else {
        return naiveAlgorithm(n);
    }
}

//finding_the_order
bool isPrimeCheck(bigint number) {
    if (number <= 1)  return false;
    if (number <= 3)  return true;
    for (bigint i = 5; i * i <= number; i++)
    {
        if ((number % i).isZero()) {
            return false;
        }
    }
    return true;
}

bigint my_gcd_for_finding_order(bigint a, bigint b) {
    if (b.isZero())
        return a;
    return my_gcd_for_finding_order(b, a % b);
}

bigint mod_power(const bigint& a, const bigint& b, const bigint& n) {
    bigint x = a;
    bigint y = b;
    bigint p = 1;
    while (y > bigint(0)) {

        while ((y % 2).isZero()) {
            y = y / 2;
            x = (x * x) % n;
            if (y.isZero())
            {
                break;
            }
        }
        y = y - 1;
        p = (p * x) % n;
        if (y.isZero())
        {
            break;
        }

    }
    return p;
}


bigint phi(const bigint& n0) {
    bigint n = bigint(n0);
    bigint result = bigint(n);
    for (bigint i = 2; i * i <= n; i++) {
        if ((n % i).isZero()) {
            while ((n % i).isZero()) {
                n /= i;
            }
            result -= (result / i);
            //std::cout << i << " " << " " << result << " t \n";

        }
    }
    //std::cout <<result<<" n = "<< n << " n \n";
    if (!(n.isZero() || n.isOne()))
        result -= (result / n);
    return result;
}

bigint find_order(bigint a, bigint n) {
  if (a == bigint(0) || a < bigint(0) || a >= n) {
    return bigint(0);
  }

  bigint phiN ;
  phiN = n-1;

  std::vector<bigint> dividers = Factorization(phiN, 1);
  std::map<bigint, int> powers;
  for (int i = 0; i < dividers.size(); i++)
  {
    powers[dividers[i]]++;
  }
  bigint t = phiN;
  bigint a1 = 1;
  for (const auto& p : powers) {
    t = t / p.first.pow(p.second);
    a1 = mod_power(a, t, n);
    while (a1 != 1) {
      a1 = mod_power(a1, p.first, n);
      t = (t * p.first);

    }
  }
  return t;
}

bool isGenerator(bigint a, bigint n) {
  if (a == bigint(0) || a < bigint(0) || a >= n) {
    return false;
  }
  bigint phiN;
  phiN = n - 1;

  std::vector<bigint> dividers = Factorization(phiN, 1);
  std::map<bigint, int> powers;
  for (int i = 0; i < dividers.size(); i++)
  {
    powers[dividers[i]]++;
  }
  bigint t1;
  bigint a1;
  for (const auto& p : powers) {
    t1 = phiN / p.first;
    a1 = mod_power(a, t1, n);

    if (a1 == 1)
    {
      return false;
    }
  }

  return true;
}

//findingCircularPolynomial
vector<int> findDividers(int n) {
    vector<int> dividers;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            dividers.push_back(i);
        }
    }
    return dividers;
}

bool prime(int n) {
    if (n == 1) { return false; }
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}

bool checkForFreeFromSquares(int a) {
    for (int i = 2; i < a; i++) {
        if (prime(i)) {
            int k = i * i;
            if (a % k == 0) { return false; }
        }
    }

    return true;
}

int countPrimeDividers(int n) {
    int k=0;
    for (int i = 1; i <= n; i++) {
        if (prime(i) && n % i == 0) {
            k++;
        }
    }
    return k;
}

int Mobiusfunction(int d) {
    int mobiusfunction;
    if (d == 1) { return 1; }
    if (!checkForFreeFromSquares(d)) {
        mobiusfunction = 0;
    }
    if (checkForFreeFromSquares(d)) {
        mobiusfunction = pow(-1, countPrimeDividers(d));
    }

    return mobiusfunction;
}


polynomial_ring CircularPolynom(int n, int primeCP) {
    if (!prime(primeCP)) { return polynomial_ring("0", primeCP); }

        // if n is prime
        if (prime(n)) { return polynomial_ring(vector<bigint>(n, 1), primeCP); }

        //if the n - power of two
        int test_n = n;
        int deg = 0;
        while (test_n % 2 == 0) {
            deg++;
            test_n = test_n / 2;
            if (test_n == 2) {
                deg++;
                int power = pow(2, deg - 1);
                auto str = "x^" + to_string(power) + "+1";
                return polynomial_ring(str, primeCP);
                break;
            }
        }
        // general case
        vector<int> dividers = findDividers(n);
        polynomial_ring res("1", primeCP);
        polynomial_ring denominatorCP("1", primeCP);
        polynomial_ring numeratorCP("1", primeCP);
        for (auto d : dividers) {
            auto str = "x^" + to_string(n / d) + "-1";
            polynomial_ring curr(str, primeCP);
            if (Mobiusfunction(d) == 1) {
                numeratorCP = numeratorCP * curr;

            }

            if (Mobiusfunction(d) == -1) {
                denominatorCP = denominatorCP * curr;
            }
        }

        res = numeratorCP.divide(numeratorCP, denominatorCP);
        return res;
   }
//inverse

bigint inverse(bigint a, bigint m) {
    if (a % m == 0_BI || m % a == 0_BI) { cout << "There is no modular multiplicative inverse for this integer" << endl; return -1_BI; }
    if (a == 1_BI) { return a; }
    a = a % m;
    bigint x = 1_BI;
    while (x<m)
    {
        if((a * x) % m == 1_BI){ return x; }
        x += 1_BI;
    }

    //return 0_BI;
}

bigint power(bigint x,  bigint y,  bigint m)
{
    if (y == 0)
        return 1;
    bigint p = power(x, y / 2, m) % m;
    p = (p * p) % m;

    return (y % 2 == 0) ? p : (x * p) % m;
}


bigint gcd_bl(bigint a, bigint b)
{
    if (a == 0)
        return b;
    return gcd_bl(b % a, a);
}

bigint modInverse(bigint a, bigint m)
{
    bigint g = gcd_bl(a, m);
    if (g != 1) {
        cout << "Inverse doesn't exist";
        return -1_BI;
    }
    else
    {
        return power(a, m - 2, m);
    }
}

//MillerRabinTest
bool MillerRabin_Test(BigInt t, BigInt n) {
    //choose a random integer a in the interval[2, n - 2]
    BigInt a = 2 + rand() % (n - 2);


    //x ? a^ t mod n
    //the function was additionally written for the class
    BigInt x = pow(a, t, n);
    if (x == 1 || x == n - 1)
        return true;

    //keep squaring x while one of the following doesn't
     // happen
     // t does not reach n-1
     // (x^2) % n is not 1
     // (x^2) % n is not n-1
    while (t != n - 1) {
        x = (x * x) % n;
        t = t * 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    return false;
}

bool isPrime(BigInt n, int k) {
    //corner cases
    if (n == 2 || n == 3)
        return true;
    //if n<2 or n is even - return false
    if (n < 2 || n % 2 == 0)
        return false;


    // represent n - 1 as (2^s) t, where t is odd, this can be done by successively dividing n - 1 by 2
    BigInt t = n - 1;
    while (t % 2 == 0)
        t = t / 2;

    //Since the test does not give an exact understanding of whether a number is prime, we use a k times loop. (recomended to use log_2(n))

    for (int i = 0; i < k; i++)
        if (!MillerRabin_Test(t, n))
            return false;

    return true;

}

//bigint
[[nodiscard]] bigint operator "" _BI(const char* str) {
    std::stringstream ss(str);
    bigint out;
    ss >> out;

    return out;
}

//mod_bigint
[[maybe_unused]] [[nodiscard]] bigint modular_add(const bigint& lhs, const bigint& rhs, const bigint& modulo) {
    return (lhs + rhs) % modulo;
}

[[maybe_unused]] [[nodiscard]] bigint modular_subtract(const bigint& lhs, const bigint& rhs, const bigint& modulo) {
    return (lhs - rhs) % modulo;
}

[[maybe_unused]] [[nodiscard]] bigint modular_product(const bigint& lhs, const bigint& rhs, const bigint& modulo) {
    return (lhs * rhs) % modulo;
}
//pylypenko ilchuk
bigint pow_mnt(const bigint& n, const bigint& power, const bigint& p) {
    montgomery to_pow(n, p);
    bigint res_of_pow = 1_BI;
    to_pow = to_pow ^ power;
    res_of_pow = to_pow.convertToStandartForm(to_pow.getmontgform());
    return res_of_pow;
}

std::optional<pair<bigint, bigint>> sqrt(const bigint& n, const bigint& p)
{
    // NOTE: Names of variables are taken directly from Wikipedia for better understanding
    /// If it doesn't satisfy Fermat's little theorem than we can't find result
    if (pow_mnt(n, (p - 1_BI) / 2_BI, p) != 1_BI) {
        return {};
    }
    /// Attempt to find trivial solution
    const auto& [q, s] = [&] {
        auto q = p - 1_BI;
        auto s = 0_BI;
        while (q % 2_BI == 0_BI) {
            q = q / 2_BI;
            s = s + 1_BI;
        }
        return std::pair{ q, s };
    }();
    /// If p = 3 (mod 4) than solutions are trivial
    if (s == 1_BI) {
        const auto x = pow_mnt(n, (p + 1_BI) / 4_BI, p);
        return std::pair{ x, p - x };
    }
    /// Select a quadric non-residue (mod p)
    const auto z = [&] {
        for (bigint i = bigint("1"); i < p; i = i + 1_BI) {
            if (pow_mnt(i, (p - 1_BI) / 2_BI, p) != 1_BI) {
                return i;
            }
        }

        return 0_BI;
    }();
    auto c = pow_mnt(z, q, p);
    auto r = pow_mnt(n, (q + 1_BI) / 2_BI, p);
    auto t = pow_mnt(n, q, p);
    auto m = s;

    while (t != 1_BI) {
        const auto& [i, x] = [&] {
            auto i = 1_BI;
            auto x = t * t % p;
            while (x != 1_BI) {
                x = x * x % p;
                i = i + 1_BI;
            }

            return std::pair(i, x);
        }();

        const auto b = pow_mnt(c,pow_mnt(2_BI, m - i - 1_BI, p), p);

        r = (r * b) % p;
        c = (b * b) % p;
        t = (t * c) % p;
        m = i;
    }

    return std::pair{ r, p - r };
}

#include <iostream>
#include "polynomial.h"
#include "polynomial_field.h"
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
#include <vector>
#include "findingCircularPolynomial.h"


bigint phi (bigint n) {
    bigint result = n;
    for (bigint i=2; i*i<=n; i=i+1)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    if (n > 1)
        result  -= result / n;
    return result;

}


bigint gcd( bigint a, bigint b ) {
    bigint t;
  while( b>0 ) {
    t = b;
    b = a%b;
    a = t;
  }
  return a;
}
bigint pw(bigint a,int b,bigint c){
    bigint t=1;
  for( int e=0; e<b; e++ ) {
    t=(t*a)%c;
  }
  return t;
}
int carmichael(bigint n) {
  int k = 1;
  for( ;; ) {
    int done = 1;
    for( bigint x=1; x<n; x++ ) {
      if( gcd(x,n)==1 && pw(x,k,n) != 1 ) {
        done = 0;
        k++;
      }
    }
    if( done ) break;
  }
  return k;
}


[[nodiscard]] std::vector<bigint> naiveAlgorithm(bigint to_factorize) {
    if (to_factorize < 2_BI) {
        return {};
    }

    std::vector<bigint> result;
    bigint cur_divisor = 2_BI;

    while (to_factorize != 1_BI) {
        if (to_factorize % cur_divisor == 0_BI) {
            result.push_back(cur_divisor);
            to_factorize /= cur_divisor;
        }
        else {
            ++cur_divisor;
        }
    }

    return result;
}

bigint fact_gcd(bigint a, bigint b) {
    if (a == 0_BI)
        return b;
    if (b == 0_BI)
        return a;

    if (a == b)
        return a;

    if (a > b)
        return fact_gcd(a - b, b);
    return fact_gcd(a, b - a);
}


bigint PollardRho(bigint n)
{
    srand(std::time(NULL));

    if (n == 1_BI) return n;

    if (n % 2 == 0_BI) return 2_BI;


    bigint x = (bigint(rand()) % (n - 2_BI)) + 2_BI;
    bigint y = x;

    bigint c = (bigint(rand()) % (n - 1_BI)) + 1_BI;

    bigint d = 1_BI;


    while (d == 1_BI)
    {
        if (x == 0_BI) {
            x = (c + n) % n;
        }
        else {
            x = (((x*x) % n) + c + n) % n;
        }

        if (y == 0_BI) {
            y = (c + n) % n;
        }
        else {
            y = (((y*y) % n) + c + n) % n;
        }


        if (y == 0_BI) {
            y = (c + n) % n;
        }
        else {
            y = (((y*y) % n) + c + n) % n;
        }

        if (x == 0_BI && y == 0_BI) {
            d = n;
        }
        else {
            d = fact_gcd((x - y).abs(), n);
        }


        if (d == n) return PollardRho(n);
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

[[maybe_unused]] [[nodiscard]] bigint modular_add(const bigint& lhs, const bigint& rhs, const bigint& modulo) {
    return (lhs + rhs) % modulo;
}

[[maybe_unused]] [[nodiscard]] bigint modular_subtract(const bigint& lhs, const bigint& rhs, const bigint& modulo) {
    return (lhs - rhs) % modulo;
}

[[maybe_unused]] [[nodiscard]] bigint modular_product(const bigint& lhs, const bigint& rhs, const bigint& modulo) {
    return (lhs * rhs) % modulo;
}

[[nodiscard]] bigint operator "" _BI(const char* str) {
    std::stringstream ss(str);
    bigint out;
    ss >> out;

    return out;
}

bigint order_gcd(bigint a, bigint b) {
    if (a + 1 == 1)
        return b;
    if (b + 1 == 1)
        return a;

    if (a == b)
        return a;

    if (a > b)
        return order_gcd(a - b, b);
    return order_gcd(a, b - a);
}

bigint find_order(const bigint& n, const bigint& a)  {
    bigint zero = 0;
    bigint one = 1;

    if (!(order_gcd(a, n) == one)) {
        return zero;
    }
    bigint res = 1;
    bigint k = 1;
    while (n > k) {

        res = modular_product(res, a, n);;
        if (res == one) {
            return k;
        }
        k = modular_add(k, one, n);
    }

    return zero;

}

bool MillerRabin_Test(BigInt t, BigInt n)  {
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


bigint inverse_gcd(bigint a, bigint b)
{
    if (a == 0)
        return b;
    return inverse_gcd(b % a, a);
}

bigint modInverse(bigint a, bigint m)
{
    bigint g = inverse_gcd(a, m);
    if (g != 1) {
        cout << "Inverse doesn't exist";
        return -1_BI;
    }
    else
    {
        return power(a, m - 2, m);
    }
}


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


polynomial findCircularPolynomial(int n) {
    vector<int> dividers = findDividers(n);
    polynomial numeratorCP("1");
    polynomial denominatorCP("1");
    for (auto value : dividers)
    {
        auto str = "x^" + to_string(n/value) + "-1";
        polynomial p(str);
        int mobiusfunction = Mobiusfunction(value);

        if(mobiusfunction==1){  numeratorCP = numeratorCP * p;
        }
        if(mobiusfunction==-1){denominatorCP = denominatorCP * p;
        }

    }
    polynomial output = denominatorCP / numeratorCP;
    return output;
}


Polynom::Polynom(int newDegree) {
    degree = newDegree;
    coef = new bigint[degree];
    for (int i = 0; i < degree; i++) {
        coef[i] = 0.0;
    }
}

Polynom::Polynom(int newDegree, bigint newCoef[]) {
    degree = newDegree;
    coef = new bigint[degree];
    for (int i = 0; i < degree; i++) {
        coef[i] = newCoef[i];
    }
}

Polynom::Polynom(const Polynom& polinom) {
    degree = polinom.degree;
    coef = new bigint[degree];
    for (int i = 0; i < degree; i++) {
        coef[i] = polinom.coef[i];
    }
}

void Polynom::reduce(void) {
    int recducedDeg = degree;
    for (int i = degree - 1; i >= 0; i--) {
        if (coef[i] == 0)
            recducedDeg--;
        else
            break;

    }
    degree = recducedDeg;
}

Polynom operator / (const Polynom& polinom1, const Polynom& polinom2) {
    Polynom temp = polinom1;
    int resultDeg = temp.degree - polinom2.degree + 1;
    if (resultDeg < 0) {
        return Polynom(0);
    }
    Polynom res(resultDeg);

    for (int i = 0; i < resultDeg; i++) {
        //Use * inverse number instead of /
        res.coef[resultDeg - i - 1] = temp.coef[temp.degree - i - 1] / polinom2.coef[polinom2.degree - 1];

        for (int j = 0; j < polinom2.degree; j++) {
            temp.coef[temp.degree - j - i - 1] -= polinom2.coef[polinom2.degree - j - 1] * res.coef[resultDeg - i - 1];
        }
    }

    return res;
}

Polynom operator % (const Polynom& polinom1, const Polynom& polinom2) {
    Polynom temp = polinom1;
    int rdeg = temp.degree - polinom2.degree + 1;
    if (rdeg < 0) {
        return Polynom(0);
    }
    Polynom res(rdeg);
    for (int i = 0; i < rdeg; i++) {
        //Use * inverse number instead of /
        res.coef[rdeg - i - 1] = temp.coef[temp.degree - i - 1] / polinom2.coef[polinom2.degree - 1];
        for (int j = 0; j < polinom2.degree; j++) {
            temp.coef[temp.degree - j - i - 1] -= polinom2.coef[polinom2.degree - j - 1] * res.coef[rdeg - i - 1];
        }
    }

    temp.reduce();
    return temp;
}

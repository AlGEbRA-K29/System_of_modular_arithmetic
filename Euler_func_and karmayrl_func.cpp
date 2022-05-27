#include <iostream>
#include <vector>
#include <cmath>
#include "big_int.hpp"


using namespace std;

bool isPrime(bigint n)
{
    if (n <= 1)
        return false;
    if (n <= 3) {
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; bigint(i * i) <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;

}



bigint gcd(bigint a, bigint b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    if (a == b)
        return a;

    if (a > b)
        return gcd(a - b, b);
    return gcd(a, b - a);
}



bigint carmaicle(vector<bigint> arr, int n)
{
    bigint ans = arr[0];
 
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));
 
    return ans;
}



bigint eurel(vector<bigint> arr, int n)
{
    bigint ans = arr[0];
 
    for (int i = 1; i < n; i++)
        ans = ((arr[i] * ans));
 
    return ans;
}






bigint PollardRho(bigint n)
{
    srand(std::time(NULL));

    if (n == 1) return n;

    if (n % 2 == 0) return 2;


    bigint x = (bigint(rand()) % (n - 2)) + 2;
    bigint y = x;

    bigint c = (bigint(rand()) % (n - 1)) + 1;

    bigint d = 1;


    while (d == 1)
    {
        if (x == 0) {
            x = (c + n) % n;
        }
        else {
            x = (((x*x) % n) + c + n) % n;
        }

        if (y == 0) {
            y = (c + n) % n;
        }
        else {
            y = (((y*y) % n) + c + n) % n;
        }


        if (y == 0) {
            y = (c + n) % n;
        }
        else {
            y = (((y*y) % n) + c + n) % n;
        }

        if (x == 0 && y == 0) {
            d = n;
        }
        else {
            d = gcd((x - y).abs(), n);
        }


        if (d == n) return PollardRho(n);
    }
    return d;
}


[[nodiscard]] std::vector<bigint> factorize(bigint n, std::vector<bigint> factors)
{
    if (n == 1)
        return factors;
    if (isPrime(n))
    {

            factors.push_back(n-1);
        
        
        return factors;
    }

    bigint divisor = PollardRho(n);
    factors = factorize(divisor, factors);
    factors = factorize(n / divisor, factors);
    return factors;
}



int main() {

    bigint n("234523452345234");

    vector<bigint> vec;
    vec=factorize(n,vec);
    cout<<"Carmaicle: "<<carmaicle(vec,vec.size())<<endl;

    cout<<"Eylera : "<<eurel(vec,vec.size())<<endl;

    
    return 0;
}




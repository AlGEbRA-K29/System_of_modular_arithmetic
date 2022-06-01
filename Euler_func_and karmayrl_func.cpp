#include <iostream>
#include <vector>
#include <cmath>
#include "Factorization.h"


using namespace std;


bigint carmaicle(vector<bigint> arr, int n)
{
    bigint ans = arr[0];
    
    if(arr.size()==1) return ans;
    
    for (int i = 1; i < n; i++){
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));
    }
 
    return ans;
}


bigint eurel(vector<bigint> arr, int n)
{
    bigint ans = arr[0];
 
    if(arr.size()==1) return ans;
    
    for (int i = 1; i < n; i++)
        ans = ((arr[i] * ans));
 
    return ans;
}


[[nodiscard]] std::vector<bigint> factorizeForEurelFunction(bigint n, std::vector<bigint> factors)
{
    if (n == 1)
        return factors;
    if (isPrime(n))
    {
            factors.push_back(n-1);
        return factors;
    }

    bigint divisor = PollardRho(n);
    factors = factorizeForEurelFunction(divisor, factors);
    factors = factorizeForEurelFunction(n / divisor, factors);
    return factors;
}







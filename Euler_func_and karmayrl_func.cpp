#include <iostream>
#include <vector>
#include <cmath>
#include "Factorization.h"


using namespace std;


bigint carmaicle(vector<bigint> arr, int n)
{
    bigint ans = arr[0];
 
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
                (fact_gcd(arr[i], ans)));
 
    return ans;
}


bigint eurel(vector<bigint> arr, int n)
{
    bigint ans = arr[0];
 
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



int main() {

    bigint n("23452342345234");

    vector<bigint> vec;
    vec=factorizeForEurelFunction(n,vec);
 
    cout<<"Carmaicle: "<<carmaicle(vec,vec.size())<<endl;

    cout<<"Eylera : "<<eurel(vec,vec.size())<<endl;

    
    return 0;
}






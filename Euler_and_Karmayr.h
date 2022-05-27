//
//  main.cpp
//  Euler_func_and karmayrl_func
//
//  Created by Blotenko on 06.05.2022.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "big_integers/bigint.h"


using namespace std;


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


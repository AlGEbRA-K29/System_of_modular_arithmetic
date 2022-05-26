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


bigint phi (bigint n) {
    bigint result = n;
    for (bigint i=2; i*i<=n; i=i+1)
        if ((n % i )== 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    if (n > 1)
        result  -= result / n;
    return result;
    
}



bigint restOfPot(bigint a,int b,const  bigint& T)
{
    a=a%T;
    bigint R=1;
    while(b)
    {
        if(b&1) R=(R*a)%T;
        a=(a*a)%T;
        b>>=1;
    }
    return (R);
}

//a lot of copy, bad
bigint gcd_d(const bigint& a,const bigint& b)
{
    if (a==0)
        return b;
    return gcd_d(b % a, a);
}


int carmichael(const bigint& n) {
    int k = 1;
  for( ;; ) {
    int done = 1;
    for( bigint x=1; x<n; x++ ) {
      if( gcd_d(x,n)==1 && restOfPot(x, k, n)!= 1 ) {
        done = 0;
        k++;
      }
    }
    if( done ) break;
  }
  return k;
}


/*
int main() {

    bigint n = 99999999;
    cout<<"Eylera : "<<phi(n)<<endl;
    cout<<"Carmichael : "<<carmichael(9999)<<endl;
    return 0;
}*/

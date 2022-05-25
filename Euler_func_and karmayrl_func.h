#pragma once
//
//  main.cpp
//  Euler_func_and karmayrl_func
//
//  Created by Blotenko on 06.05.2022.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "big_int.hpp"
using namespace std;


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

/*int main() {

    bigint n = 0;

    cout<<"n: ";cin>>n;

    cout<<"Eylera : "<<phi(n)<<endl;
    cout<<"Carmichael : "<<carmichael(n)<<endl;
    return 0;
}*/


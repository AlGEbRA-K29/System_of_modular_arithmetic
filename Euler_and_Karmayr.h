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


bigint phi (bigint n);



bigint restOfPot(bigint a,int b,const  bigint& T);


bigint gcd_d(const bigint& a,const bigint& b);


int carmichael(const bigint& n);

#include <vector>
 #include <iostream>
#include "polynomial_ring.h"

using namespace std;




void extended_Euclidean_algorithm(polynomial_ring a, polynomial_ring b, polynomial_ring &u, polynomial_ring &v, polynomial_ring &w, polynomial_ring &x, polynomial_ring &y, polynomial_ring &z){
    
       w = a;
       z = b;
    
    polynomial_ring q;
    
    polynomial_ring one("1",a.getModulus());
    while( !z.getData().empty()){
        
        q=w.divide(w,z);
        
        u -= q*x;
        v -= q*y;
        w -= q*z;
        
        std::swap( u, x );
        std::swap( v, y );
        std::swap( w, z );
    }
}




int main(){
    
//    bigint modulus = 35107;
//    std::vector<bigint> coeffs1 = {1,0,2530945095092509802,12499494,654,1,1234345252552248,1,1231,62,4561,634,12,111,1};
//        std::vector<bigint> coeffs2 = {654, 123994 ,654,144942,2};
    
//    bigint modulus = 577;
//    std::vector<bigint> coeffs1 = {1,0,25509802,12499494,654840924098409,1,1234345252552248,1,1231,4561,63444444,12,111,1};
//        std::vector<bigint> coeffs2 = {6040400454, 123994 ,654,144944040040442,2};
    
    bigint modulus = 12373;
    std::vector<bigint> coeffs1 = {1,28340923482,25509802,12499494,654840924098409,29384092341,1234345252552248,1,1230983509250231,4561,63444444,12,1923509853011,1};
        std::vector<bigint> coeffs2 = {6040400454, 123994 ,6592835092835094,144944040040442,2};
    
    

    polynomial_ring b1(coeffs1,modulus);
    polynomial_ring b2(coeffs2, modulus);
   
    polynomial_ring  u("1",modulus), v("0",modulus), w("0",modulus), x("0",modulus), y("1",modulus), z("0",modulus);
    
    extended_Euclidean_algorithm(b1, b2, u, v, w, x, y, z);
    
    printf( "Results:\n" );
    cout<<"A mod B : "<<u<<endl;
    cout<<"B mod A : "<<v<<endl;
    cout<<endl;
    
    return 0;
}



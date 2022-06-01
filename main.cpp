#include <vector>
 #include <iostream>
#include "polynomial_ring.h"

using namespace std;




// function returns u = inverse polunom a by mod polynom b
polynomial_ring extended_Euclidean_algorithm(polynomial_ring &a, polynomial_ring &b,  bigint modulus)
{
    polynomial_ring u("1",modulus), v("0",modulus), x("0",modulus), y("1",modulus),q;
        
    while( !b.getData().empty()){
        
        q=a.divide(a,b);
        
        u -= q*x;
        v -= q*y;
        a -= q*b;
        
        std::swap( u, x );
        std::swap( v, y );
        std::swap( a, b );
    }
    return u;
}




int main(){
    
    // test one
    bigint modulus = 12373;
    std::vector<bigint> coeffs1 = {1,28340923482,255099899802,12499899494,654840924098409,29384092341,1234345252552248,1,1230983509250231,45624242341,63444444,1234243232,1923509853011,12423424244};
        std::vector<bigint> coeffs2 = {6040400454, 123994 ,6592835092835094,144944040040442,2};
    
    polynomial_ring b1(coeffs1,modulus);
    polynomial_ring b2(coeffs2, modulus);
    polynomial_ring polyn_A_mod_polyn_B = extended_Euclidean_algorithm(b1, b2,modulus);

    printf( "Results:\n" );
    cout<<"A mod B : "<<polyn_A_mod_polyn_B<<endl;
    cout<<endl;
    
    
    // так как расширенний алгоритм евклида записывает в b1  gcd двух многочленнов
    //то проверку алгоритма можно сделать с помощью сравнения с обычной polynom_gcd()
    //b1.polynom_gcd(polynomial_ring(coeffs1,modulus),polynomial_ring(coeffs2,modulus)) - polynom_gcd(b1,b2)
    cout<<(b1.polynom_gcd(polynomial_ring(coeffs1,modulus),polynomial_ring(coeffs2,modulus)) == b1 )<<endl;
   
    
    // test two
     modulus = 3;
     coeffs1 = {12,28340923482,5,12499899494,0,29384092341,1234345252552248,45624242341,23,1234243232,5,12423424244};
         coeffs2 = {6040403530454, 123533535363994 ,6592835092835094,144944040040442,2};
    
    polynomial_ring b3(coeffs1,modulus);
    polynomial_ring b4(coeffs2, modulus);
    polynomial_ring polyn_A_mod_polyn_B2 = extended_Euclidean_algorithm(b3, b4,modulus);

    // так как расширенний алгоритм евклида записывает в b3  - gcd двух многочленнов
    //то проверку алгоритма можно сделать с помощью сравнения с обычной polynom_gcd()
    //b1.polynom_gcd(polynomial_ring(coeffs1,modulus),polynomial_ring(coeffs2,modulus)) - polynom_gcd(b3,b4)
    cout<<(b1.polynom_gcd(polynomial_ring(coeffs1,modulus), polynomial_ring(coeffs2,modulus)) == b3 )<<endl;
    
    
    
    
    // test three
     modulus = 7237;
    coeffs1 = {1,28340923482,255099899802,12499899494};
    coeffs2 = {6040400454, 12392342525294 ,6592835092242835094,144944040040442,2253525252252526};
    
    polynomial_ring b5(coeffs1,modulus);
    polynomial_ring b6(coeffs2, modulus);
    polynomial_ring polyn_A_mod_polyn_B3 = extended_Euclidean_algorithm(b5, b6,modulus);

    // так как расширенний алгоритм евклида записывает в b5 - gcd двух многочленнов
    //то проверку алгоритма можно сделать с помощью сравнения с обычной polynom_gcd()
    //b1.polynom_gcd(polynomial_ring(coeffs1,modulus),polynomial_ring(coeffs2,modulus)) - polynom_gcd(b5,b6)
    cout<<(b1.polynom_gcd(polynomial_ring(coeffs1,modulus), polynomial_ring(coeffs2,modulus)) == b5 )<<endl;

    
    return 0;
}




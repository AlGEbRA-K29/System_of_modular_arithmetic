#include "bigint.h"
#include "montgomery_form.h"



int main() {
    //montgomery_form is a class for storing, multiplying and exponentiating big integers (bigint.h is required)  in Montgomery form

    
    //Initializing big integers 
    bigint bint1("10");
    bigint bint2("12");

    
   // Converting bigint to Montgomery form
    montgomery mont1(bint1, bigint("59"),bigint("64"));
    montgomery mont2(bint2, bigint("59"), bigint("64"));
    montgomery mont3;

    // Multiplication
    mont3 = mont1 * mont2;

   // Exponentiation  
    mont3 = mont1 ^ bint2;
    //or
    mont3 = mont1 ^ mont2;

    //Conversion to standart form (mod)
    bint2 = mont3.convertToStandartForm(mont3.getmontgform());








    return 0;
}

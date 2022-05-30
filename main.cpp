#include "bigint.h"
#include "montgomery_form.h"



int main() {
    //montgomery_form is a class for storing, multiplying and exponentiating big integers (bigint.h is required)  in Montgomery form

    
    //Initializing big integers 
    bigint bint1("10");
    bigint bint2("200");
    bigint bint3("1234500");
    bigint bint4("-12354");
    
   // Converting bigint to Montgomery form
    montgomery mont1(bint1, bigint("59"));
    montgomery mont2(bint2, bigint("59"), bigint("64"));
    montgomery mont3;

    
    mont3 = mont1 * montgomery(bigint("0"),bigint("59"));
    std::cout << mont3.getmontgform() << std::endl;
    //0
    mont3 = montgomery(bigint("-123"), bigint("59"));
    std::cout << mont3.getmontgform() << std::endl;
    //34
    try
    {
        mont3 = montgomery(bigint("-123"), bigint("0"));
    }
    catch (const std::exception&e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        mont3 = montgomery(bigint("-123"), bigint("-12354"));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        mont3 = montgomery(bigint("-123"), bigint("12"),bigint("24"));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    try
    {
        mont3 = montgomery(bigint("-123"), bigint("13"),bigint("4"));
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    // Multiplication
    mont3 = mont1 * mont2;
    std::cout << mont3.getmontgform() << std::endl;
    //29
   // Exponentiation  
    mont3 = mont1 ^ bint2;
    std::cout << mont3.getmontgform() << std::endl;
    //41
    //or
    mont3 = mont1 ^ mont2;
    std::cout << mont3.getmontgform() << std::endl;
    //3
    //Conversion to standart form (mod)
    bint2 = mont3.convertToStandartForm(mont3.getmontgform());
    std::cout << bint2 << std::endl;
    //36
    mont3 = mont1 ^ bint3;
    std::cout << mont3.getmontgform() << std::endl;
    //29
    mont3 = mont1 ^ bint4;
    std::cout << mont3.getmontgform() << std::endl;
    //5




    return 0;
}

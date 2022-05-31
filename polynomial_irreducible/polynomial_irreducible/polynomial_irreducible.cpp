#include <iostream>
#include "polynomial_field.h"

int main()
{
    polynomial_ring f1({ 1_BI,0_BI,0_BI,0_BI,0_BI,0_BI,0_BI,1_BI,0_BI,0_BI,1_BI }, 2_BI);
    std::cout << f1.isIrreducible();
	polynomial_ring f2({1_BI,0_BI,0_BI,1_BI,0_BI,0_BI,1_BI,1_BI,0_BI,0_BI,1_BI}, 2_BI);
	std::cout << f2.isIrreducible();
	polynomial_ring f3({ 3_BI,2_BI,0_BI,0_BI,1_BI }, 5_BI);
	std::cout << f3.isIrreducible();
	polynomial_ring f4({ 1_BI,1_BI,1_BI}, 2_BI);
	std::cout << f4.isIrreducible();
	polynomial_ring f7({ 0_BI, 2_BI ,3_BI ,0_BI ,0_BI ,0_BI ,1_BI }, 7_BI);
	std::cout << f7.isIrreducible();
	polynomial_ring f9({ 1_BI, 2_BI ,1_BI ,2_BI ,1_BI ,2_BI ,1_BI,2_BI, 3_BI, 4_BI, 10_BI, 15_BI,0_BI,23_BI,1_BI, 1_BI ,2_BI ,18_BI ,1_BI ,1_BI}, 19_BI);
	std::cout << f9.isIrreducible();
}
																																						
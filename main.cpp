#include "bigint.h"
#include "PolyField.h"
#include "polynomial_ring.h"
int main()
{
	//(1 + 25x^2 + 12x^3 + 654x^4 +x^5 +12342x^6 + x^7+1231x^8+62x^9 + 12312445x^10 + 4561x^11+123x^12 + 634x^13+ 12x^14+111x^15+x^16)
	// ((1 + 25x^2 + 12x^3 + 654x^4 +x^5 +12342x^6 + x^7+1231x^8+62x^9 + 12312445x^10 + 4561x^11+123x^12 + 634x^13+ 12x^14+111x^15+x^16) +(654 + 123x + 654x^2 + 12x^3 + 2x^4))%5
	//std::vector<bigint> coeffs00 = {5,-1,-1,0,1};
	//std::vector<bigint> coeffs01 = {-2,0,1};
	//polynomial_ring aa(coeffs00, 5);
	//polynomial_ring ab(coeffs01, 5);
	//std::cout<<aa.divide(aa,ab)<<std::endl;
	//std::cout << aa.remainder(aa, ab) << std::endl;
	//(x^4 + 2)
	bigint modulus = 5;





	std::vector<bigint> coeffs1 = { 0,3,0,1,1,1,0,3,1 };
	std::vector<bigint> coeffs2 = { 2,0,0,0,1 };
	std::vector<bigint> coeffs3 = { 3,2,0,0,1 };


	//valid irreducible
	polynomial_ring irreducible(coeffs2, modulus);
	
	PolynomialField pf(irreducible);


	//invalid irreducible CHECK PLEASE!!! (For Stepan)
	polynomial_ring invalidIrreducible(coeffs3, modulus);
	std::cout << invalidIrreducible.isIrreducible() << std::endl;
	//shows true while it's supposed to be false
	PolynomialField invalidField(invalidIrreducible);
	// as a result, the field above doesnt throw exception during it's initialization
	//


	std::vector<bigint> coeffs4 = {1,0,25,12,654,1,12342,1,1231,62,12312445,4561,123,634,12,111,1};
	std::vector<bigint> coeffs5 = {654, 123 ,654,12,2};

	polynomial_ring b1(coeffs4,modulus);
	polynomial_ring b2(coeffs5, modulus);
	
	std::cout <<"addition"<< pf.add(b1, b2) << std::endl;
	//3*x^3 + 4*x^2 + 2*x + 4
	std::cout << "subtraction" << pf.subtract(b1, b2) << std::endl;
	//4*x^3 + x^2 + x + 4
	std::cout << "multiplication" << pf.multiply(b1, b2) << std::endl;
	//4*x^3 + 4*x^2 + 4*x + 3
	std::cout << "quickPow" << pf.quickPow(b2, bigint("6")) << std::endl;
	//4*x^3 + x^2 + 4*x + 2



	return 0;
}
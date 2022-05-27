#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include"polynomial.h"
#include "doctest.h"


TEST_CASE("polynomial derivative") {
	
	polynomial p1("115478*x^654+5147854*x^257");
	polynomial derivate_p1 = p1.derivate();
	polynomial p1_check("75522612*x^653+1322998478*x^256");
	CHECK(derivate_p1 == p1_check);


	polynomial p2("1000x^1000 + 6000x^-1000 + 1000x^1 + 1");
	polynomial derivate_p2 = p2.derivate();
	polynomial p2_check("1000000x^999 + 1000 - 6000000x^-1001");
	CHECK(derivate_p2 == p2_check);


	polynomial p3("1000000000x^1000000000 - 1000000000x^-1000000000 + 5");
	polynomial derivate_p3 = p3.derivate();
	polynomial p3_check("1000000000000000000x^999999999 + 1000000000000000000x^-1000000001");
	CHECK(derivate_p3 == p3_check);


	polynomial p4("1000000000x^1000000000 - 0x^-10101010101010 + 1");
	polynomial derivate_p4 = p4.derivate();
	polynomial p4_check("1000000000000000000*x^999999999");
	CHECK(derivate_p4 == p4_check);

	polynomial p5("12345678981x^2 - 0x^3 + 5");
	polynomial derivate_p5 = p5.derivate();
	polynomial p5_check("24691357962*x^1");
	CHECK(derivate_p5 == p5_check);

	polynomial p6("100000000000000000000000000000000000000000000000000000000000000000000000000000000x^1 + 5");
	polynomial derivate_p6 = p6.derivate();
	polynomial p6_check("100000000000000000000000000000000000000000000000000000000000000000000000000000000");
	CHECK(derivate_p6 == p6_check);		

}




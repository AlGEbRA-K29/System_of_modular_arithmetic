#pragma once
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include"polynomial_ring.h"
#include "doctest.h"



TEST_CASE("polynomial derivative") {

	polynomial_ring p1("115478*x^654+5147854*x^257", bigint(11));
	polynomial_ring derivate_p1 = p1.derivative();
	polynomial_ring p1_check("75522612*x^653+1322998478*x^256", bigint(11));
	CHECK(derivate_p1 == p1_check);


	polynomial_ring p2("1000x^1000 + 6000x^-1000 + 1000x^1 + 1", bigint(11));
	polynomial_ring derivate_p2 = p2.derivative();
	polynomial_ring p2_check("1000000x^999 + 1000 - 6000000x^-1001", bigint(11));
	CHECK(derivate_p2 == p2_check);


	polynomial_ring p3("1000000000x^1000000000 - 1000000000x^-1000000000 + 5", bigint(11));
	polynomial_ring derivate_p3 = p3.derivative();
	polynomial_ring p3_check("1000000000000000000x^999999999 + 1000000000000000000x^-1000000001", bigint(11));
	CHECK(derivate_p3 == p3_check);


	polynomial_ring p4("1000000000x^1000000000 - 0x^-10101010101010 + 1", bigint(11));
	polynomial_ring derivate_p4 = p4.derivative();
	polynomial_ring p4_check("1000000000000000000*x^999999999", bigint(11));
	CHECK(derivate_p4 == p4_check);

	polynomial_ring p5("12345678981x^2 - 0x^3 + 5", bigint(11));
	polynomial_ring derivate_p5 = p5.derivative();
	polynomial_ring p5_check("24691357962*x^1", bigint(11));
	CHECK(derivate_p5 == p5_check);

	polynomial_ring p6("100000000000000000000000000000000000000000000000000000000000000000000000000000000x^1 + 5", bigint(11));
	polynomial_ring derivate_p6 = p6.derivative();
	polynomial_ring p6_check("100000000000000000000000000000000000000000000000000000000000000000000000000000000", bigint(11));
	CHECK(derivate_p6 == p6_check);

}


TEST_CASE("polynomial value at point") {
	polynomial_ring p1("115478*x^654+5147854*x^257", bigint(11));
	CHECK(p1.get_value(bigint(1)) == bigint(5263332) % 11);

	polynomial_ring p2("1000x^10+6000x^-10+1000x^1+125", bigint(11));
	CHECK(p2.get_value(bigint(0)) == bigint(125)%11);

	polynomial_ring p3("3x^2+x^3+25", bigint(11));
	CHECK(p3.get_value(bigint(-1)) == bigint(27) % 11);

	polynomial_ring p4("100000000000000000000000000000000000000000000000000000000000000000000000000000000x^1+5", bigint(11));
	CHECK(p4.get_value(bigint(0)) == bigint(5) % 11);

}
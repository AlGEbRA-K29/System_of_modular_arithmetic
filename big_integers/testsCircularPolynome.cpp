#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include"doctest.h"
#include"polynomial_ring.h"
#include"findingCircularPolynomial.h"

TEST_CASE("Test 1") {
	polynomial_ring test1 = CircularPolynom(36, 2);
	polynomial_ring checkTest1("x^42+x^36+x^6+1",2);
	CHECK_EQ(test1, checkTest1);
}

TEST_CASE("Test 2") {
	polynomial_ring test2 = CircularPolynom(18, 3);
	polynomial_ring checkTest2("x^21+2*x^18+2*x^3+1", 3);
	CHECK_EQ(test2, checkTest2);
}

TEST_CASE("Test 3") {
	polynomial_ring test3 = CircularPolynom(5, 5);
	polynomial_ring checkTest3("x^4+x^3+x^2+x^1+1", 5);
	CHECK_EQ(test3, checkTest3);
}

TEST_CASE("Test 4") {
	polynomial_ring test4 = CircularPolynom(15, 7);
	polynomial_ring checkTest4("x^16+6*x^15+6*x^1+1", 7);
	CHECK_EQ(test4, checkTest4);
}

TEST_CASE("Test 5") {
	polynomial_ring test5 = CircularPolynom(68, 12);
	polynomial_ring checkTest5("0",12);
	CHECK_EQ(test5, checkTest5);
}
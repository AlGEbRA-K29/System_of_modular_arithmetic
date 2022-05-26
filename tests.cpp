#include <iostream>
#include <numeric>
#include <math.h>
#include <ctime>
#include <vector>

#include "doctest.h"
#include "polynomial_field.h"


TEST_CASE("Polynomials field") {
    polynomial_field a("2x^4+3x^2-1x^1", 7_BI);
    polynomial_field b("5x^5+15x^2-2x^1", 7_BI);

    SUBCASE("Construct") {
        polynomial_field expected_a("2x^4+3x^2+6x^1", 7_BI);
        polynomial_field expected_b("5x^5+x^2+5x^1", 7_BI);
        
        CHECK(a == expected_a);
        CHECK(b == expected_b);
    }

    SUBCASE("Add, substract, multiply") {
        polynomial_field expected_add("5x^5+2x^4+4x^2+4x^1", 7_BI);
        polynomial_field expected_substract_1("2x^5+2x^4+2x^2+x^1", 7_BI); //a - b
        polynomial_field expected_substract_2("5x^5+5x^4+5x^2+6x^1", 7_BI); //b - a
        polynomial_field expected_multiply("3x^9+x^7+4x^6+3x^5+3x^4+2x^2", 7_BI);

        CHECK(a + b == expected_add);
        CHECK(a - b == expected_substract_1);
        CHECK(b - a == expected_substract_2);
        CHECK(a * b == expected_multiply);

    }

    SUBCASE("Normalize") {
        polynomial_field expected_a("x^4+5x^2+3x^1", 7_BI);
        polynomial_field expected_b("x^5+3x^2+1x^1", 7_BI);

        a.normalize();
        b.normalize();

        CHECK(a == expected_a);
        CHECK(b == expected_b);
    }

    SUBCASE("Quick pow") {
        polynomial_field to_pow("x^1+1", 3_BI);

        polynomial_field expected_pow_2("x^2+2x^1+1", 3_BI);
        polynomial_field expected_pow_3("x^3+1", 3_BI);
        polynomial_field expected_pow_4("x^4+x^3+x^1+1", 3_BI);
        polynomial_field expected_pow_5("x^5+2x^4+x^3+x^2+2x^1+1", 3_BI);
        polynomial_field expected_pow_6("x^6+2x^3+1", 3_BI);
        polynomial_field expected_pow_7("x^7+x^6+2x^4+2x^3+x^1+1", 3_BI);
        polynomial_field expected_pow_8("x^8+2x^7+x^6+2x^5+x^4+2x^3+x^2+2x^1+1", 3_BI);

        CHECK(to_pow.quickPow(2_BI) == expected_pow_2);
        CHECK(to_pow.quickPow(3_BI) == expected_pow_3);
        CHECK(to_pow.quickPow(4_BI) == expected_pow_4);
        CHECK(to_pow.quickPow(5_BI) == expected_pow_5);
        CHECK(to_pow.quickPow(6_BI) == expected_pow_6);
        CHECK(to_pow.quickPow(7_BI) == expected_pow_7);
        CHECK(to_pow.quickPow(8_BI) == expected_pow_8);
    } 
}

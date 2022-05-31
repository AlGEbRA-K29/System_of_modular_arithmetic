#include "doctest.h"
#include "PolyField.h"

TEST_CASE("Add, substract, multiply, normalize, quick pow") {
	polynomial_ring irreducible_1("x^5+2x^1+2", 3_BI);
	polynomial_ring irreducible_2("x^5+x^2+2x^1+4", 5_BI);
	polynomial_ring irreducible_3("x^4+x^3+x^2+x^1+1", 7_BI);
	polynomial_ring reducible("x^4+x^3+x^2+1", 2_BI);

	PolynomialField f1(irreducible_1);
	PolynomialField f2(irreducible_2);
	PolynomialField f3(irreducible_3);

	SUBCASE("Add, subtract, multiply") {
		polynomial_ring lhs_1("x^5+1", 3_BI), rhs_1("x^5+x^4+1", 3_BI);
		polynomial_ring lhs_2("x^5+3x^4+2x^2", 5_BI), rhs_2("x^5+4x^2+1", 5_BI);
		polynomial_ring lhs_3("x^4+5x^3+2x^2+x^1+1", 7_BI), rhs_3("x^4+1", 7_BI);

		SUBCASE("Add") {
			polynomial_ring expected_1("x^4+2x^1+1", 3_BI);
			polynomial_ring expected_2("3x^4+4x^2+x^1+3", 5_BI);
			polynomial_ring expected_3("3x^3+6x^1", 7_BI);

			auto res_1 = f1.add(lhs_1, rhs_1);
			auto res_2 = f2.add(lhs_2, rhs_2);
			auto res_3 = f3.add(lhs_3, rhs_3);

			CHECK(res_1 == expected_1);
			CHECK(res_2 == expected_2);
			CHECK(res_3 == expected_3);
		}

		SUBCASE("Subtract") {
			polynomial_ring expected_1("2x^4", 3_BI); //a - b
			polynomial_ring expected_2("3x^4+3x^2+4", 5_BI);
			polynomial_ring expected_3("5x^3+2x^2+x^1", 7_BI);

			polynomial_ring expected_4("x^4", 3_BI); //b - a
			polynomial_ring expected_5("2x^4+2x^2+1", 5_BI);
			polynomial_ring expected_6("2x^3+5x^2+6x^1", 7_BI);
			

			auto res_1 = f1.subtract(lhs_1, rhs_1);
			auto res_2 = f2.subtract(lhs_2, rhs_2);
			auto res_3 = f3.subtract(lhs_3, rhs_3);

			auto res_4 = f1.subtract(rhs_1, lhs_1);
			auto res_5 = f2.subtract(rhs_2, lhs_2);
			auto res_6 = f3.subtract(rhs_3, lhs_3);

			CHECK(res_1 == expected_1);
			CHECK(res_2 == expected_2);
			CHECK(res_3 == expected_3);
			CHECK(res_4 == expected_4);
			CHECK(res_5 == expected_5);
			CHECK(res_6 == expected_6);
		}

		SUBCASE("Multiply & normalize") {
			polynomial_ring expected_1("2x^4+x^2+2x^1+2", 3_BI);
			polynomial_ring expected_2("4x^4+3x^3+2x^2+1", 5_BI);
			polynomial_ring expected_3("4x^3+5x^2+x^1", 7_BI);

			auto res_1 = f1.multiply(lhs_1, rhs_1);
			auto res_2 = f2.multiply(lhs_2, rhs_2);
			auto res_3 = f3.multiply(lhs_3, rhs_3);

			CHECK(res_1 == expected_1);
			CHECK(res_2 == expected_2);
			CHECK(res_3 == expected_3);

			expected_1 = polynomial_ring("x^4+2x^2+x^1+1", 3_BI);
			expected_2 = polynomial_ring("x^4+2x^3+3x^2+4", 5_BI);
			expected_3 = polynomial_ring("x^3+3x^2+2x^1", 7_BI);

			res_1.normalize();
			res_2.normalize();
			res_3.normalize();

			CHECK(res_1 == expected_1);
			CHECK(res_2 == expected_2);
			CHECK(res_3 == expected_3);
		}

		SUBCASE("Quick pow") {
			polynomial_ring to_pow("x^5+1", 3_BI);

			std::map<bigint, polynomial_ring> expected = {
				{2_BI, polynomial_ring("x^2+x^1+1", 3_BI)},
				{3_BI, polynomial_ring("x^3+2", 3_BI)},
				{4_BI, polynomial_ring("x^4+2x^3+2x^1+1", 3_BI)},
				{5_BI, polynomial_ring("x^4+x^3+2x^2", 3_BI)},
				{6_BI, polynomial_ring("x^3+x^2+x^1+1", 3_BI)},
				{7_BI, polynomial_ring("x^4+2", 3_BI)},
				{8_BI, polynomial_ring("2x^4+2", 3_BI)},
			};

			for (const auto& p : expected) {
				auto cur_res = f1.quickPow(to_pow, p.first);
				CHECK(cur_res == p.second);
			}
		}
	}
}
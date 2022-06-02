#include "doctest.h"
#include "../polynomial_ring.h"
#include "../polynomial_field.h"
#include "../Euler_and_Karmayr.h"
#include "../Factorization.h"
#include "../finding_the_order.h"
#include "../MillerRabinTest.h"
#include "../montgomery_form.h"
#include "../inverse.h"
#include "../findingCircularPolynomial.h" 
#include "../main_test.h" 
#include "../big_integers/mod_bigint.h"
#include "../big_integers/bigint.h"
#include <vector>
//first block

TEST_CASE("Big integer constructors") {
	CHECK_EQ(bigint(0), 0);
	CHECK_EQ(bigint(-1), -1);
	CHECK_EQ(2_BI, 2);

	CHECK_LE(bigint(1), 2);
	CHECK_GE(bigint(2), 2_BI);

	CHECK_EQ(4294967296_BI, bigint("4294967296"));
	CHECK_EQ(4294967295_BI, bigint("4294967295"));

	CHECK_EQ(-10000000000000000000000_BI, bigint("-10000000000000000000000"));

	CHECK_EQ(bigint("0"), -0_BI);
}

TEST_CASE("Big integer operators") {
	CHECK_EQ(bigint(1) + bigint(2), 3);
	CHECK_EQ(bigint(1) - bigint(2), -1);
	CHECK_EQ(bigint(1) * bigint(2), 2);

	CHECK_EQ(10000000000000000000000_BI + 10000000000000000000000_BI, 20000000000000000000000_BI);
	CHECK_EQ(10000000000000000000000_BI - 10000000000000000000000_BI, 0_BI);
	CHECK_EQ(10000000000000000000000_BI * 10000000000000000000000_BI, 100000000000000000000000000000000000000000000_BI);
	CHECK_EQ(10000000000000000000000_BI / 10000000000000000000000_BI, 1_BI);
	CHECK_EQ(10000000000000000000000_BI % 10000000000000000000000_BI, 0_BI);

	CHECK_EQ(10000000000000000000000_BI * -10000000000000000000000_BI, -100000000000000000000000000000000000000000000_BI);

	CHECK_EQ(4294967296_BI * 4294967296_BI, bigint("18446744073709551616"));

	std::stringstream str;
	str << -10000005000000_BI;
	CHECK_EQ(str.str(), "-10000005000000");

	CHECK_EQ(bigint(1) / bigint(2), 0);
	CHECK_EQ(0_BI % -1_BI, 0);

	CHECK_EQ(0_BI * 1234567912346789123456789132456798_BI, 0_BI);
}

TEST_CASE("Modular big integers") {
	CHECK_EQ(modular_add(2_BI, 5_BI, 3_BI), 1_BI);
	CHECK_EQ(modular_add(510000000000000000000000_BI, 10000000000000000000000_BI, 123_BI), 34_BI);
	CHECK_EQ(modular_product(2_BI, 5_BI, 3_BI), 1_BI);
	CHECK_EQ(modular_product(510000000000000000000000_BI, 10000000000000000000000_BI, 10_BI), 0_BI);

	CHECK_EQ(modular_subtract(2_BI, 6_BI, 3_BI), -1_BI);
	CHECK_EQ(modular_subtract(510000000000000000000000_BI, 10000000000000000000000_BI, 7_BI), 4_BI);

}

TEST_CASE("Add, substract, multiply, inverse, divide, fastPow, factorization(2v), sqrt, order, isGenerate, Euler, Carmaicle, Prime") {
	SUBCASE("Factorization") {
		auto sort_vector = [](std::vector<bigint>& v) {
			std::sort(v.begin(), v.end());
		};
		std::vector<bigint> tests = {
		  12547_BI,
		  963252_BI,
		  2435346_BI,
		  434525252_BI,
		};
		std::vector<std::vector<bigint>> expected = {
		  {12547_BI},
		  {2_BI, 2_BI, 3_BI, 3_BI, 3_BI, 3_BI, 3_BI, 991_BI},
		  {2_BI, 3_BI, 3_BI, 3_BI, 3_BI, 3_BI, 5011_BI},
		  {2_BI, 2_BI, 7_BI, 83_BI, 181_BI, 1033_BI},
		};
		for (size_t i = 0; i < tests.size(); ++i) {
			auto naive = Factorization(tests[i], false);
			//auto pollard = Factorization(tests[i], true);

			//sort_vector(pollard);

			CHECK(naive == expected[i]);
			//CHECK(naive == pollard);
		}
	}
	//func use polard algo, crush
	/*SUBCASE("eurel and carmaicle") {
		bigint n("23452342345234");
		std::vector<bigint> vec;
		vec = factorizeForEurelFunction(n, vec);
		bigint tmp1("93636270");
		bigint tmp2("10618353018000");
		CHECK(tmp1 == carmaicle(vec, vec.size()));
		CHECK(tmp2 == eurel(vec, vec.size()));

		bigint n2("12547");
		std::vector<bigint> vec2;
		vec2 = factorizeForEurelFunction(n2, vec2);
		bigint tmp3("12546");
		bigint tmp4("12546");

		CHECK(tmp3 == carmaicle(vec2, vec2.size()));
		CHECK(tmp4 == eurel(vec2, vec2.size()));

		bigint n3("963252");
		std::vector<bigint> vec3;
		vec3 = factorizeForEurelFunction(n3, vec3);
		bigint tmp5("990");
		bigint tmp6("31680");

		CHECK(tmp5 == carmaicle(vec3, vec3.size()));
		CHECK(tmp6 == eurel(vec3, vec3.size()));


		bigint n4("2435346");
		std::vector<bigint> vec4;
		vec4 = factorizeForEurelFunction(n4, vec4);
		bigint tmp7("5010");
		bigint tmp8("160320");

		CHECK(tmp7 == carmaicle(vec4, vec4.size()));
		CHECK(tmp8 == eurel(vec4, vec4.size()));


		bigint n5("434525252");
		std::vector<bigint> vec5;
		vec5 = factorizeForEurelFunction(n5, vec5);
		bigint tmp9("634680");
		bigint tmp10("91393920");

		CHECK(tmp9 == carmaicle(vec5, vec5.size()));
		CHECK(tmp10 == eurel(vec5, vec5.size()));
	}*/
	//crush
	/*SUBCASE("Finding the order and ch") {
		CHECK(find_order(2, 5) == 4);
		CHECK(find_order(3, 100) == 20);
		CHECK(find_order(2, 4) == 0);
		CHECK(find_order(3, 12344) == 514);
		CHECK(find_order(5, 101204) == 6325);
		CHECK(find_order(3, 101203) == 33734);
		CHECK(isGenerator(3, 101) == 1);
		CHECK(isGenerator(5, 109) == 0);
	}*/
	SUBCASE("primality check") {
		CHECK(isPrime(1709, 2) == true);
		CHECK(isPrime(2539, 2) == true);
		CHECK(isPrime(2833, 2) == true);
		CHECK(isPrime(2834, 2) == false);
		CHECK(isPrime(7057, 2) == true);
		CHECK(isPrime(22189, 2) == true);
		CHECK(isPrime(4398042316799, 2) == true);
		CHECK(isPrime(18014398241046527, 2) == true);
		CHECK(isPrime(4398042316799, 2) == true);
		CHECK(isPrime(99194853094755497, 2) == true);
	}

    
}
TEST_CASE("Add, substract, multiply, derivative, valueInPoint, divide, remainder, gcd, cyclPol") {

	SUBCASE("Derivative") {
		polynomial_ring a = polRingDerivative("3x^4+2x^2-3x^1+1", "11");
		polynomial_ring b("12x^3+4x^1-3", bigint("11"));
		CHECK(a == b);
	
		a = polRingDerivative("30000000x^4+20000000000000x^2-300000000000000x^1+1", "11");
		polynomial_ring c("120000000x^3+40000000000000x^1-300000000000000", bigint("11"));
		CHECK(a == c);
	
		a = polRingDerivative("30000000x^400+20000000000000x^200000-300000000000000x^1+1", "11");
		polynomial_ring d("12000000000x^399+4000000000000000000x^199999-300000000000000", bigint("11"));
		CHECK(a == d);

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
	
	SUBCASE("GetValueInPoint(v1)") {
	    bigint a = polRingValueInPoint("3x^4+2x^2-3x^1+1", "1", "11");
		bigint b("3");
		CHECK(a == b);
	
		a = polRingValueInPoint("300x^400-200x^-200-3x^1+4", "1", "11");
		bigint c("101");
		c = c % 11;
		CHECK(a == c);

	
		a = polRingValueInPoint("20000000000x^400+20000000000x^200000-30000000000x^1+1", "1", "11");
		bigint d("10000000001");
		d = d % 11;
		CHECK(a == d);

		polynomial_ring p1("115478*x^654+5147854*x^257", bigint(11));
		CHECK(p1.get_value(bigint(1)) == bigint(5263332) % 11);

		polynomial_ring p2("1000x^10+6000x^-10+1000x^1+125", bigint(11));
		CHECK(p2.get_value(bigint(0)) == bigint(125) % 11);

		polynomial_ring p3("3x^2+x^3+25", bigint(11));
		CHECK(p3.get_value(bigint(-1)) == bigint(27) % 11);
    }
    SUBCASE("Finding the fraction and reminder") {
		polynomial_ring a1("x^4+3*x^3+2*x^1+4", 5);
		polynomial_ring b1("2*x^1+4", 5);
		polynomial_ring division1("3*x^3+3*x^2+4*x^1+3", 5);
		polynomial_ring remainder1("2", 5);
		CHECK(a1.divide(a1, b1).getData() == division1.getData());
		CHECK(a1.remainder(a1, b1).getData() == remainder1.getData());
		
		polynomial_ring a2("2*x^4+3*x^3+2*x^1", 5);
		polynomial_ring b2("x^1+4", 5);
		polynomial_ring division2("2*x^3+2", 5);
		polynomial_ring remainder2("2", 5);
		CHECK(a1.divide(a2, b2).getData() == division2.getData());
		CHECK(a1.remainder(a2, b2).getData() == remainder2.getData());
	
		polynomial_ring a3("x^2+x^1", 5);
		polynomial_ring b3("1*x^1+1", 5);
		polynomial_ring gcd3("x^1+1", 5);
		CHECK(a1.polynom_gcd(a3, b3).getData() == gcd3.getData());
    }
    //pylypenko ilyin
	SUBCASE("Circular polynomial") {
		polynomial_ring test1 = CircularPolynom(36, 2);
		polynomial_ring checkTest1("x^42+x^36+x^6+1", 2);
		CHECK_EQ(test1, checkTest1);

		polynomial_ring test2 = CircularPolynom(18, 3);
		polynomial_ring checkTest2("x^21+2*x^18+2*x^3+1", 3);
		CHECK_EQ(test2, checkTest2);

		polynomial_ring test3 = CircularPolynom(5, 5);
		polynomial_ring checkTest3("x^4+x^3+x^2+x^1+1", 5);
		CHECK_EQ(test3, checkTest3);

		polynomial_ring test4 = CircularPolynom(15, 7);
		polynomial_ring checkTest4("x^16+6*x^15+6*x^1+1", 7);
		CHECK_EQ(test4, checkTest4);
	}
    
}
//polynomial field
TEST_CASE("Add, substract, multiply, normalize, quick pow") {
	polynomial_ring irreducible_1("x^5+2x^1+2", 3_BI);
	polynomial_ring irreducible_2("x^5+x^2+2x^1+4", 5_BI);
	polynomial_ring irreducible_3("x^4+x^3+x^2+x^1+1", 7_BI);

	PolynomialField f1(irreducible_1);
	PolynomialField f2(irreducible_2);
	PolynomialField f3(irreducible_3);

	polynomial_ring lhs_1("x^5+1", 3_BI), rhs_1("x^5+x^4+1", 3_BI);
	polynomial_ring lhs_2("x^5+3x^4+2x^2", 5_BI), rhs_2("x^5+4x^2+1", 5_BI);
	polynomial_ring lhs_3("x^4+5x^3+2x^2+x^1+1", 7_BI), rhs_3("x^4+1", 7_BI);

	SUBCASE("Add") {
		polynomial_ring expected_1("x^4+2x^1+1", 3_BI);
		polynomial_ring expected_2("3x^4+4x^2+x^1+3", 5_BI);
		polynomial_ring expected_3("3x^3+6x^1", 7_BI);

		auto res_1 = f1.addition(lhs_1, rhs_1);
		auto res_2 = f2.addition(lhs_2, rhs_2);
		auto res_3 = f3.addition(lhs_3, rhs_3);

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
	//bloshenko code
	SUBCASE("inverse Polynom") {
        
		polynomial_ring expected_1("x^1+x", 3_BI);
		polynomial_ring expected_2("2*x^3+3*x^2+x^1", 5_BI);
		polynomial_ring expected_3("2*x^3+3*x^2+5", 7_BI);

		polynomial_ring expected_4("2x^1", 3_BI);
		polynomial_ring expected_5("3*x^3+x^2+1", 5_BI);
		polynomial_ring expected_6("5*x^3+x^2+2*x^1+x", 7_BI);

		auto res_1 = f1.extended_Euclidean_algorithm(lhs_1, rhs_1,3_BI);
		auto res_2 = f2.extended_Euclidean_algorithm(lhs_2, rhs_2,5_BI);
		auto res_3 = f3.extended_Euclidean_algorithm(lhs_3, rhs_3,7_BI);

		auto res_4 = f1.extended_Euclidean_algorithm(rhs_1, lhs_1,3_BI);
		auto res_5 = f2.extended_Euclidean_algorithm(rhs_2, lhs_2,5_BI);
		auto res_6 = f3.extended_Euclidean_algorithm(rhs_3, lhs_3,7_BI);

		CHECK(res_1 == expected_1);
		CHECK(res_2 == expected_2);
		CHECK(res_3 == expected_3);
		CHECK(res_4 == expected_4);
		CHECK(res_5 == expected_5);
		CHECK(res_6 == expected_6);

    }
}
int main() {
	doctest::Context runner;
	runner.run();
	int a;
	std::cin >> a;
	return 0;
}
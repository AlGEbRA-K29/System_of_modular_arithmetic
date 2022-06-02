#include <iostream>
#include "find_the_order_and_check_generator.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Finding the order and ch") {


	CHECK(find_order(2, 5) == 4);
	CHECK(find_order(3, 100) == 20);
	CHECK(find_order(2, 4) == 0);
	CHECK(find_order(3, 12344) == 514);
	CHECK(find_order(5, 101204) == 6325);
	CHECK(find_order(3, 101203) == 33734);
	CHECK(isGenerator(3, 101) == 1);
	CHECK(isGenerator(5, 109) == 0);
}
//
//int main() {
//	std::cout <<  << std::endl;//4
//	std::cout << find_order(3, 100) << std::endl;//20
//	std::cout << find_order(2, 4) << std::endl;//0
//	std::cout << find_order(7, 80) << std::endl;//4
//	std::cout << find_order(3, 12344) << std::endl;//514
//	std::cout << find_order(5, 101204) << std::endl;//6325
//	std::cout << find_order(3, 101203) << std::endl;//33734
//	std::cout << isGenerator(3, 101) << std::endl;//1
//	std::cout << isGenerator(5, 109) << std::endl;//0
//}
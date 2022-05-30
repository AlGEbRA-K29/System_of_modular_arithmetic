#include "pch.h"
#include "../main_test.h"
/*block 1*/
TEST(finFieldAddition, CheckForOtherDataAdditional) {
	bigint  a = finFieldAddition("10", "20");
	bigint b("30");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldAddition("100000000000000", "200000000000000");
	bigint c("300000000000000");
	EXPECT_EQ(a, c);
}
TEST(finFieldSubstraction, CheckForOtherDataSubstraction) {
	bigint  a = finFieldSubstraction("10", "20");
	bigint b("-10");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldSubstraction("100000000000000", "200000000000000");
	bigint c("-100000000000000");
	EXPECT_EQ(a, c);
}

TEST(finFieldMultiplication, CheckForOtherDataMultiplication) {
	bigint  a = finFieldMultiplication("10", "20");
	bigint b("200");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldMultiplication("100000000000000", "200000000000000");
	bigint c("20000000000000000000000000000");
	EXPECT_EQ(a, c);
}
/*task for ilyin
TEST(finFieldInverse, CheckForOtherDataFindInverse) {
	bigint  a = finFieldInverse("10", "20");
	bigint b("200");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldInverse("100000000000000", "200000000000000");
	bigint c("20000000000000000000000000000");
	EXPECT_EQ(a, c);
}*/
TEST(finFieldDivision, CheckForOtherDataDivision) {
	bigint  a = finFieldDivision("100", "20");
	bigint b("5");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldDivision("200000000000000", "200000000000000");
	bigint c("1");
	EXPECT_EQ(a, c);
}
/*task for polishuk
TEST(finFieldPow, CheckForOtherDataPow) {
	bigint  a = finFieldPow("100", "20");
	bigint b("5");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldPow("200000000000000", "200000000000000");
	bigint c("1");
	EXPECT_EQ(a, c);
}*/
/*task for prokopchuk
TEST(finFieldFacrorizationNaive, CheckForOtherDataFacrorizationN) {
	bigint  a = finFieldFacrorizationNaive("100");
	bigint b("5");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldFacrorizationNaive("200000000000000");
	bigint c("1");
	EXPECT_EQ(a, c);
}
TEST(finFieldFacrorizationPolard, CheckForOtherDataFacrorizationP) {
	bigint  a = finFieldFacrorizationNaive("100");
	bigint b("5");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldFacrorizationNaive("200000000000000");
	bigint c("1");
	EXPECT_EQ(a, c);
}*/
TEST(finFieldSqrt, CheckForOtherDataDivision) {
	bigint  a = finFieldSqrt("100");
	bigint b("10");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldSqrt("100000000000000000000");
	bigint c("10000000000");
	EXPECT_EQ(a, c);
}
/*task for khlopyuk
TEST(finFieldOrder, CheckForOtherDataOrder) {
	bigint  a = finFieldOrder("100");
	bigint b("10");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldOrder("100000000000000000000");
	bigint c("10000000000");
	EXPECT_EQ(a, c);
}
TEST(finFieldIsGenerator, CheckForOtherDataOrder) {
	bigint  a = finFieldIsGenerator("100");
	bigint b("10");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldIsGenerator("100000000000000000000");
	bigint c("10000000000");
	EXPECT_EQ(a, c);
}*/
/*task for bloshenko hrishenko
 TEST(finFieldEuler, CheckForOtherDataEuler) {
	bigint  a = finFieldEuler("100");
	bigint b("10");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldEuler("100000000000000000000");
	bigint c("10000000000");
	EXPECT_EQ(a, c);
}
TEST(finFieldCarmaicle, CheckForOtherDataEuler) {
	bigint  a = finFieldEuler("100");
	bigint b("10");
	EXPECT_EQ(a, b);
	//EXPECT_TRUE(true);
	a = finFieldEuler("100000000000000000000");
	bigint c("10000000000");
	EXPECT_EQ(a, c);
}*/
TEST(finFieldPrime, CheckForOtherDataPrime) {
	bool  a = finFieldPrime("11");
	EXPECT_TRUE(a);
	a = finFieldPrime("11111111111111111111111");
	EXPECT_TRUE(a);
}
/*block 2*/
TEST(polRingAddition, CheckForOtherDataAdditionInPolRing) {
	polynomial_ring a = polRingAddition("x^2+1", "2x^2+5", "11");
	polynomial_ring b("3x^2+6", bigint("11"));
	EXPECT_EQ(a, b);
}
TEST(polRingSubtraction, CheckForOtherDataSubtrInPolRing) {
	polynomial_ring a = polRingSubtraction("3x^2+1", "2x^2+5", "11");
	polynomial_ring b("x^2+7", bigint("11"));
	EXPECT_EQ(a, b);
}
TEST(polRingMultiply, CheckForOtherDataMultInPolRing) {
	polynomial_ring a = polRingMultiply("x^1+1", "2x^1+5", "11");
	polynomial_ring b("2x^2+7x^1+5", bigint("11"));
	EXPECT_EQ(a, b);
}
/*problem with equality, data not same, but after trim() yeap*/
TEST(polRingDerivative, CheckForOtherDataSubtrInPolRingFalse) {
	polynomial_ring a = polRingDerivative("3x^4+2x^2-3x^1+1", "11");
	polynomial_ring b("x^3+4x^1-3", bigint("11"));
	EXPECT_EQ(a, b);

	a = polRingDerivative("30000000x^4+20000000000000x^2-300000000000000x^1+1", "11");
	polynomial_ring ñ("120000000x^3+40000000000000x^1-300000000000000", bigint("11"));
	EXPECT_EQ(a, ñ);

	a = polRingDerivative("30000000x^400+20000000000000x^200000-300000000000000x^1+1", "11");
	polynomial_ring d("12000000000x^399+4000000000000000000x^199999-300000000000000", bigint("11"));
	EXPECT_EQ(a, d);
}
TEST(polRingValueInPoint, CheckForOtherDataValueInPoint) {
	bigint a = polRingValueInPoint("3x^4+2x^2-3x^1+1", "1", "11");
	bigint b("3");
	EXPECT_EQ(a, b);

	a = polRingValueInPoint("300x^400-200x^-200-3x^1+4", "1", "11");
	bigint c("101");
	c = c % 11;
	EXPECT_EQ(a, c);

	a = polRingValueInPoint("20000000000x^400+20000000000x^200000-30000000000x^1+1", "1", "11");
	bigint d("10000000001");
	d = d % 11;
	EXPECT_EQ(a, d);
}
/*mykola
TEST(polRingDivide, CheckForOtherDataDivide) {
	polynomial_ring a = polRingDivide("x^1+1", "2x^1+5", "11");
	polynomial_ring b("2x^2+7x^1+5", bigint("11"));
	EXPECT_EQ(a, b);
}

TEST(polRingRemainder, CheckForOtherDataRemainder) {
	polynomial_ring a = polRingRemainder("x^1+1", "2x^1+5", "11");
	polynomial_ring b("2x^2+7x^1+5", bigint("11"));
	EXPECT_EQ(a, b);
}

TEST(polRingGCD, CheckForOtherDataMultInPolRing) {
	polynomial_ring a = polRingGCD("x^1+1", "2x^1+5", "11");
	polynomial_ring b("2x^2+7x^1+5", bigint("11"));
	EXPECT_EQ(a, b);
}*/

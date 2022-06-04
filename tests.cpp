#include "polynomial_ring.h"
#include "polynomial_field.h"
#include "Euler_and_Karmayr.h"
#include "Factorization.h"
#include "finding_the_order.h"
#include "MillerRabinTest.h"
#include "montgomery_form.h"
#include "inverse.h"
#include "findingCircularPolynomial.h"
#include "all_func_call.h"
#include "big_integers/mod_bigint.h"
#include "big_integers/bigint.h"
#include <vector>
#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include "tests.h"

using namespace std;


template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& info = "")
{
  if (t != u) {
    ostringstream os;
    os << "Тест провалено: "<< info << " Значення: " << t << " != " << u;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b) {
  AssertEqual(b, true);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (runtime_error& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void TestFunc1() {
    AssertEqual(bigint(0), 0);
    AssertEqual(bigint(-1), -1);
    AssertEqual(2_BI, 2);

    AssertEqual(bigint(2), 2);
    AssertEqual(bigint(2), 2_BI);

    AssertEqual(4294967296_BI, bigint("4294967296"));
    AssertEqual(4294967295_BI, bigint("4294967295"));

    AssertEqual(-10000000000000000000000_BI, bigint("-10000000000000000000000"));

    AssertEqual(bigint("0"), -0_BI);
}

void TestFunc2() {

    AssertEqual(bigint(1) + bigint(2), 3);
    AssertEqual(bigint(1) - bigint(2), -1);
    AssertEqual(bigint(1) * bigint(2), 2);

    AssertEqual(10000000000000000000000_BI + 10000000000000000000000_BI, 20000000000000000000000_BI);
    AssertEqual(10000000000000000000000_BI - 10000000000000000000000_BI, 0_BI);
    AssertEqual(10000000000000000000000_BI * 10000000000000000000000_BI, 100000000000000000000000000000000000000000000_BI);
    AssertEqual(10000000000000000000000_BI / 10000000000000000000000_BI, 1_BI);
    AssertEqual(10000000000000000000000_BI % 10000000000000000000000_BI, 0_BI);

    AssertEqual(10000000000000000000000_BI * -10000000000000000000000_BI, -100000000000000000000000000000000000000000000_BI);

    AssertEqual(4294967296_BI * 4294967296_BI, bigint("18446744073709551616"));

    std::stringstream str;
    str << -10000005000000_BI;
    AssertEqual(str.str(), "-10000005000000");

    AssertEqual(bigint(1) / bigint(2), 0);
    AssertEqual(0_BI % -1_BI, 0);

    AssertEqual(0_BI * 1234567912346789123456789132456798_BI, 0_BI);
}

void TestFunc3() {
    AssertEqual(modular_add(2_BI, 5_BI, 3_BI), 1_BI);
    AssertEqual(modular_add(510000000000000000000000_BI, 10000000000000000000000_BI, 123_BI), 34_BI);
    AssertEqual(modular_product(2_BI, 5_BI, 3_BI), 1_BI);
    AssertEqual(modular_product(510000000000000000000000_BI, 10000000000000000000000_BI, 10_BI), 0_BI);

    AssertEqual(modular_subtract(2_BI, 6_BI, 3_BI), -1_BI);
    AssertEqual(modular_subtract(510000000000000000000000_BI, 10000000000000000000000_BI, 7_BI), 4_BI);

}

void TestFunc4() {
        std::cerr << "Factorization" << std::endl;
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

            AssertEqual(naive, expected[i]);
            //AssertEqual(naive, pollard);
        }
       std::cerr << "montgomery_form" << std::endl;
            //Initializing big integers
            bigint bint1("10");
            bigint bint2("200");
            bigint bint3("1234500");
            bigint bint4("-12354");
           // Converting bigint to Montgomery form
            montgomery mont1(bint1, bigint("59"));
            montgomery mont2(bint2, bigint("59"), bigint("64"));
            montgomery mont3;

            mont3 = mont1 * montgomery(bigint("0"),bigint("59"));
            AssertEqual(mont3.getmontgform(),0);
            //0
            mont3 = montgomery(bigint("-123"), bigint("59"));
             AssertEqual(mont3.getmontgform(),34);
            //34
            // Multiplication
            mont3 = mont1 * mont2;
             AssertEqual(mont3.getmontgform(),29);
            //29
           // Exponentiation
            mont3 = mont1 ^ bint2;
            AssertEqual(mont3.getmontgform(),41);
            //41
            //or
            mont3 = mont1 ^ mont2;
            AssertEqual(mont3.getmontgform(),3);
            //3
            //Conversion to standart form (mod)
            bint2 = mont3.convertToStandartForm(mont3.getmontgform());
             AssertEqual(bint2,36);
            //36
            mont3 = mont1 ^ bint3;
            AssertEqual(mont3.getmontgform(),29);
            //29
            mont3 = mont1 ^ bint4;
            AssertEqual(mont3.getmontgform(),5);
            //5
        std::cerr << "Primality" << std::endl;
        AssertEqual(isPrime(1709, 2), 1);
        AssertEqual(isPrime(2539, 2), 1);
        AssertEqual(isPrime(2833, 2), 1);
        AssertEqual(isPrime(7057, 2), 1);
        AssertEqual(isPrime(22189, 2), 1);
        AssertEqual(isPrime(4398042316799, 2), 1);
        AssertEqual(isPrime(18014398241046527, 2), 1);
        AssertEqual(isPrime(4398042316799, 2), 1);
        AssertEqual(isPrime(99194853094755497, 2), 1);

}
void TestFunc5() {

    std::cerr << "Derivative" << std::endl;
        polynomial_ring a = polRingDerivative("3x^4+2x^2-3x^1+1", "11");
        polynomial_ring b("12x^3+4x^1-3", bigint("11"));
        AssertEqual(a, b);

        a = polRingDerivative("30000000x^4+20000000000000x^2-300000000000000x^1+1", "11");
        polynomial_ring c("120000000x^3+40000000000000x^1-300000000000000", bigint("11"));
        AssertEqual(a, c);

        a = polRingDerivative("30000000x^400+20000000000000x^200000-300000000000000x^1+1", "11");
        polynomial_ring d("12000000000x^399+4000000000000000000x^199999-300000000000000", bigint("11"));
        AssertEqual(a, d);

        polynomial_ring p1("115478*x^654+5147854*x^257", bigint(11));
        polynomial_ring derivate_p1 = p1.derivative();
        polynomial_ring pr1("75522612*x^653+1322998478*x^256", bigint(11));
        AssertEqual(derivate_p1, pr1);


        polynomial_ring p2("1000x^1000 + 6000x^-1000 + 1000x^1 + 1", bigint(11));
        polynomial_ring derivate_p2 = p2.derivative();
        polynomial_ring pr2("1000000x^999 + 1000 - 6000000x^-1001", bigint(11));
        AssertEqual(derivate_p2, pr2);


        polynomial_ring p3("1000000000x^1000000000 - 1000000000x^-1000000000 + 5", bigint(11));
        polynomial_ring derivate_p3 = p3.derivative();
        polynomial_ring pr3("1000000000000000000x^999999999 + 1000000000000000000x^-1000000001", bigint(11));
        AssertEqual(derivate_p3, pr3);


        polynomial_ring p4("1000000000x^1000000000 - 0x^-10101010101010 + 1", bigint(11));
        polynomial_ring derivate_p4 = p4.derivative();
        polynomial_ring pr4("1000000000000000000*x^999999999", bigint(11));
        AssertEqual(derivate_p4, pr4);

        polynomial_ring p5("12345678981x^2 - 0x^3 + 5", bigint(11));
        polynomial_ring derivate_p5 = p5.derivative();
        polynomial_ring pr5("24691357962*x^1", bigint(11));
        AssertEqual(derivate_p5, pr5);

        polynomial_ring p6("100000000000000000000000000000000000000000000000000000000000000000000000000000000x^1 + 5", bigint(11));
        polynomial_ring derivate_p6 = p6.derivative();
        polynomial_ring pr6("100000000000000000000000000000000000000000000000000000000000000000000000000000000", bigint(11));
        AssertEqual(derivate_p6, pr6);

        std::cerr << "GetValueInPoint(v1)" << std::endl;
    {
        bigint a = polRingValueInPoint("3x^4+2x^2-3x^1+1", "1", "11");
        bigint b("3");
        AssertEqual(a, b);

        a = polRingValueInPoint("300x^400-200x^-200-3x^1+4", "1", "11");
        bigint c("101");
        c = c % 11;
        AssertEqual(a, c);


        a = polRingValueInPoint("20000000000x^400+20000000000x^200000-30000000000x^1+1", "1", "11");
        bigint d("10000000001");
        d = d % 11;
        AssertEqual(a, d);

        polynomial_ring p1("115478*x^654+5147854*x^257", bigint(11));
        AssertEqual(p1.get_value(bigint(1)), bigint(5263332) % 11);

        polynomial_ring p2("1000x^10+6000x^-10+1000x^1+125", bigint(11));
        AssertEqual(p2.get_value(bigint(0)), bigint(125) % 11);

        polynomial_ring p3("3x^2+x^3+25", bigint(11));
        AssertEqual(p3.get_value(bigint(-1)), bigint(27) % 11);

        std::cerr << "Finding the fraction and reminder" << std::endl;
        polynomial_ring a1("x^4+3*x^3+2*x^1+4", 5);
        polynomial_ring b1("2*x^1+4", 5);
        polynomial_ring division1("3*x^3+3*x^2+4*x^1+3", 5);
        polynomial_ring remainder1("2", 5);
        AssertEqual(a1.divide(a1, b1).getData(), division1.getData());
        AssertEqual(a1.remainder(a1, b1).getData(), remainder1.getData());

        polynomial_ring a2("2*x^4+3*x^3+2*x^1", 5);
        polynomial_ring b2("x^1+4", 5);
        polynomial_ring division2("2*x^3+2", 5);
        polynomial_ring remainder2("2", 5);
        AssertEqual(a1.divide(a2, b2).getData(), division2.getData());
        AssertEqual(a1.remainder(a2, b2).getData(), remainder2.getData());

        polynomial_ring a3("x^2+x^1", 5);
        polynomial_ring b3("1*x^1+1", 5);
        polynomial_ring gcd3("x^1+1", 5);
        AssertEqual(a1.polynom_gcd(a3, b3).getData(), gcd3.getData());
}
    //pylypenko ilyin

        std::cerr << "Circular polynomial" << std::endl;
        polynomial_ring test1 = CircularPolynom(36, 2);
        polynomial_ring AssertEqualTest1("x^42+x^36+x^6+1", 2);
        AssertEqual(test1, AssertEqualTest1);

        polynomial_ring test2 = CircularPolynom(18, 3);
        polynomial_ring AssertEqualTest2("x^21+2*x^18+2*x^3+1", 3);
        AssertEqual(test2, AssertEqualTest2);

        polynomial_ring test3 = CircularPolynom(5, 5);
        polynomial_ring AssertEqualTest3("x^4+x^3+x^2+x^1+1", 5);
        AssertEqual(test3, AssertEqualTest3);

        polynomial_ring test4 = CircularPolynom(15, 7);
        polynomial_ring AssertEqualTest4("x^16+6*x^15+6*x^1+1", 7);
        AssertEqual(test4, AssertEqualTest4);


}
//polynomial field
void TestFunc6() {
    polynomial_ring irreducible_1("x^5+2x^1+2", 3_BI);
    polynomial_ring irreducible_2("x^5+x^2+2x^1+4", 5_BI);
    polynomial_ring irreducible_3("x^4+x^3+x^2+x^1+1", 7_BI);

    PolynomialField f1(irreducible_1);
    PolynomialField f2(irreducible_2);
    PolynomialField f3(irreducible_3);

    polynomial_ring lhs_1("x^5+1", 3_BI), rhs_1("x^5+x^4+1", 3_BI);
    polynomial_ring lhs_2("x^5+3x^4+2x^2", 5_BI), rhs_2("x^5+4x^2+1", 5_BI);
    polynomial_ring lhs_3("x^4+5x^3+2x^2+x^1+1", 7_BI), rhs_3("x^4+1", 7_BI);


        std::cerr << "Addition" << std::endl;
        polynomial_ring expected_1("x^4+2x^1+1", 3_BI);
        polynomial_ring expected_2("3x^4+4x^2+x^1+3", 5_BI);
        polynomial_ring expected_3("3x^3+6x^1", 7_BI);

        auto res_1 = f1.addition(lhs_1, rhs_1);
        auto res_2 = f2.addition(lhs_2, rhs_2);
        auto res_3 = f3.addition(lhs_3, rhs_3);

        AssertEqual(res_1, expected_1);
        AssertEqual(res_2, expected_2);
        AssertEqual(res_3, expected_3);


    {
        std::cerr << "Subtraction" << std::endl;
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

        AssertEqual(res_1, expected_1);
        AssertEqual(res_2, expected_2);
        AssertEqual(res_3, expected_3);
        AssertEqual(res_4, expected_4);
        AssertEqual(res_5, expected_5);
        AssertEqual(res_6, expected_6);
    }
{

        std::cerr << "Multiply & normalize" << std::endl;
        polynomial_ring expected_1("2x^4+x^2+2x^1+2", 3_BI);
        polynomial_ring expected_2("4x^4+3x^3+2x^2+1", 5_BI);
        polynomial_ring expected_3("4x^3+5x^2+x^1", 7_BI);

        auto res_1 = f1.multiply(lhs_1, rhs_1);
        auto res_2 = f2.multiply(lhs_2, rhs_2);
        auto res_3 = f3.multiply(lhs_3, rhs_3);

        AssertEqual(res_1, expected_1);
        AssertEqual(res_2, expected_2);
        AssertEqual(res_3, expected_3);

        expected_1 = polynomial_ring("x^4+2x^2+x^1+1", 3_BI);
        expected_2 = polynomial_ring("x^4+2x^3+3x^2+4", 5_BI);
        expected_3 = polynomial_ring("x^3+3x^2+2x^1", 7_BI);

        res_1.normalize();
        res_2.normalize();
        res_3.normalize();

        AssertEqual(res_1, expected_1);
        AssertEqual(res_2, expected_2);
        AssertEqual(res_3, expected_3);

}

        std::cerr << "Quick pow" << std::endl;
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
            AssertEqual(cur_res, p.second);
        }

    //bloshenko code
    {
        std::cerr << "Inverse polynom" << std::endl;

        auto inverse = f1.extended_Euclidean_algorithm(lhs_1, irreducible_1);
        auto res = f1.multiply(inverse,lhs_1);
        
        auto inverse2 = f2.extended_Euclidean_algorithm(lhs_2, irreducible_2);
        auto res2 = f2.multiply(inverse2,lhs_2);
        
        auto inverse3 = f3.extended_Euclidean_algorithm(lhs_3, irreducible_3);
        auto res3 = f3.multiply(inverse3,lhs_3);
        
        polynomial_ring one("1",lhs_1.getModulus());
        polynomial_ring one2("1",lhs_2.getModulus());
        polynomial_ring one3("1",lhs_3.getModulus());
       
       
        AssertEqual(res  == one );
        AssertEqual(res2 == one2);
        AssertEqual(res3 == one3);

    }
}

void TestRunner(){
    class TestRunner tr;
    tr.RunTest(TestFunc1, "Big integer constructors");
    tr.RunTest(TestFunc2, "Big integer operators");
    tr.RunTest(TestFunc3, "Modular big integers");
    tr.RunTest(TestFunc4, "Add, substract, multiply, inverse, divide, fastPow, factorization(2v), sqrt, order, isGenerate, Euler, Carmaicle, Prime");
    tr.RunTest(TestFunc5, "Add, substract, multiply, derivative, valueInPoint, divide, remainder, gcd, cyclPol");
    tr.RunTest(TestFunc6, "Add, substract, multiply, normalize, quick pow");
}

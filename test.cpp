#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Euler_func_and karmayrl_func.h"
#include "doctest.h"


TEST_CASE("eurel and carmaicle") {
    
    bigint n("23452342345234");
    
    std::vector<bigint> vec;
    vec=factorizeForEurelFunction(n,vec);
    bigint tmp1("93636270");
    bigint tmp2("10618353018000");

    CHECK(tmp1 == carmaicle(vec,vec.size()));
    CHECK(tmp2 == eurel(vec,vec.size()));

    
    bigint n2("12547");
    std::vector<bigint> vec2;
    vec2=factorizeForEurelFunction(n2,vec2);
    bigint tmp3("12546");
    bigint tmp4("12546");

    CHECK(tmp3 == carmaicle(vec2,vec2.size()));
    CHECK(tmp4 == eurel(vec2,vec2.size()));
    
    bigint n3("963252");
    std::vector<bigint> vec3;
    vec3=factorizeForEurelFunction(n3,vec3);
    bigint tmp5("990");
    bigint tmp6("31680");

    CHECK(tmp5 == carmaicle(vec3,vec3.size()));
    CHECK(tmp6 == eurel(vec3,vec3.size()));
    
    
    bigint n4("2435346");
    std::vector<bigint> vec4;
    vec4=factorizeForEurelFunction(n4,vec4);
    bigint tmp7("5010");
    bigint tmp8("160320");

    CHECK(tmp7 == carmaicle(vec4,vec4.size()));
    CHECK(tmp8 == eurel(vec4,vec4.size()));
    
    
    bigint n5("434525252");
    std::vector<bigint> vec5;
    vec5=factorizeForEurelFunction(n5,vec5);
    bigint tmp9("634680");
    bigint tmp10("91393920");

    CHECK(tmp9 == carmaicle(vec5,vec5.size()));
    CHECK(tmp10 == eurel(vec5,vec5.size()));
    




}


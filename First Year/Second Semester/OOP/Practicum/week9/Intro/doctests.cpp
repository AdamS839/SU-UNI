
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../libraries/doctest/doctest/doctest.h"
#include <iostream>
#include <cstring>
#include "MathOperations.cpp"

TEST_CASE("Testing"){
    char a[] = "1000";
    char b[] = "21";
    char* result = MathOperations::plus(a, b);
    CHECK(strcmp(result, "1021") == 0);
}

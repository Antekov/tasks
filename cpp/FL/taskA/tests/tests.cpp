#define CATCH_CONFIG_MAIN

#include "../src/catch.hpp"

#include "../src/taskA.hpp"

TEST_CASE("Example 1", "Example 1") {
    INFO( "TEST_CASE: acb..bab.c.*.ab.ba.+.+*a. | acbac");

    Solution solution;

    int res = solution.solve("acb..bab.c.*.ab.ba.+.+*a.", "acbac");
    
    REQUIRE(res == 5);
}


TEST_CASE("Example 2", "Example 2") {
    INFO( "TEST_CASE: ab+c.aba.*.bac.+.+* | abacb");

    Solution solution;

    int res = solution.solve("ab+c.aba.*.bac.+.+*", "abacb");
    
    REQUIRE(res == 5);
}

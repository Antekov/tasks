#include "../src/taskA.hpp"

int main() {

    {
        std::cout << ( "TEST_CASE: acb..bab.c.*.ab.ba.+.+*a. | acbac");

        Solution solution;

        int res = solution.solve("acb..bab.c.*.ab.ba.+.+*a.", "acbac");
        
        assert(res == 5);
    }


    {
        std::cout << ( "TEST_CASE: ab+c.aba.*.bac.+.+* | abacb");

        Solution solution;

        int res = solution.solve("ab+c.aba.*.bac.+.+*", "abacb");
        
        assert(res == 5);
    }
    return 0;
}
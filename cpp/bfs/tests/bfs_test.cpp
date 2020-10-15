#define CATCH_CONFIG_MAIN
#include "catch2\catch.hpp"
#include <iostream>
#include "../src/bfs.hpp"

/*
Пример 1
Ввод	Вывод
3 14 15 9 9
0
Пример 2
Ввод	Вывод
6 1 5 2 3
6
Пример 3
Ввод	Вывод
6 1 5 2 1
2
*/

TEST_CASE("Example 1", "Example 1") {
    INFO( "TEST_CASE:Example 1: 3 14 15 9 9");
    BFS_Task t1(3, 14, 15, 9, 9);

    REQUIRE(t1.run() == 0);
}

TEST_CASE("Example 2", "Example 2") {
    INFO( "TEST_CASE:Example 2: 6 1 5 2 3");
    BFS_Task t2(6, 1, 5, 2, 3);
    
    REQUIRE(t2.run() == 6);
}

TEST_CASE("Example 3", "Example 3") {
    INFO( "TEST_CASE:Example 3: 6 1 5 2 1");
    BFS_Task t3(6, 1, 5, 2, 1);
    
    REQUIRE(t3.run() == 2);
}
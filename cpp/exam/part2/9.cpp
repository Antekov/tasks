#include <map>
#include <iostream>
#include <algorithm>

int main() {
    std::map<int, int> m;
    m[0] = 1;
    m.insert({1, 2});
    m[2] = 3;

    auto start = m.lower_bound(0);
    auto finish = m.upper_bound(2);

    std::reverse(start, finish);

    for (auto item: m) {
        std::cout << item.first << item.second;
    }
}
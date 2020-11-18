#include "task5n1.hpp"

int main() {
    freopen("input.txt", "r", stdin);
    std::pair<int, int> numbers;
    

    numbers = n1::solve();

    if (numbers.first >= -10000) {
        std::cout << "YES" << std::endl;
        if (numbers.first < numbers.second) {
            std::cout << numbers.first + 1 << " " << numbers.second + 1 << std::endl;
        } else {
            std::cout << numbers.second + 1 << " " << numbers.first + 1 << std::endl;
        }
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
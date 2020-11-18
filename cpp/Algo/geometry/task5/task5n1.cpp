#include "task5n1.hpp"

int main() {
    freopen("input.txt", "r", stdin);
    std::pair<int, int> numbers;
    
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> seg(n, std::vector<int>(4,0));
    for (int i = 0; i < n; i++) {
        std::cin >> seg[i][0] >> seg[i][1] >> seg[i][2] >> seg[i][3];
    }

    numbers = n1::solve(seg);
    
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
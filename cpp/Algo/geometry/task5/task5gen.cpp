#include "task5n1.hpp"
#include "task5n3.hpp"
#include <cmath>

int rnd(int a, int b) {
    return rand() % (abs(b - a) + 1) + std::min(a, b);
}

std::vector<std::vector<int>> generate_seg() {
    int n = rnd(4, 12);
    std::vector<std::vector<int>> seg(n, std::vector<int>(4,0));

    for (int i = 0; i < n; i++) {
        seg[i][0] = rnd(-10, 10);
        seg[i][1] = rnd(-10, 10);
        seg[i][2] = rnd(-5, 20);
        seg[i][3] = rnd(-20, 20);
    }
    return seg;
}

template <class T>
std::ostream& operator<<(std::ostream &out, std::vector<std::vector<T>> v) {
    if (v.size() > 0) {
        out << v.size() << std::endl;
        for (auto p : v) { 
            for (auto a : p) {
                out << a << " ";
            }
            out << std::endl; 
        }
    } else {
        out << 0 << std::endl;
    }
    return out;
}

int main() {
    std::pair<int, int> numbers, numbers1, numbers2;
    
    int t = 1;

    while (t < 20) {

        auto seg = generate_seg();
        std::cerr << "Test: " << t << std::endl;
        std::cerr << seg << std::endl;

        std::cerr << "n1::solve(seg):" << std::endl;
        numbers1 = n1::solve(seg);
        std::cerr << "n3::solve(seg):" << std::endl;
        numbers2 = n3::solve(seg);
        
        

        if (numbers1 == numbers2) {
            numbers = numbers1;
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
        } else {
            std::cout << "ERROR" << std::endl;
            std::cout << numbers1.first + 1 << " " << numbers1.second + 1 << std::endl;
            std::cout << numbers2.first + 1 << " " << numbers2.second + 1 << std::endl;
            break;
        }
        t++;
    }
    return 0;
}
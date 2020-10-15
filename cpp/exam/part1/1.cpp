#include <iostream>
int main() {
    int x = 0;
    int y = 1;
    int z = 2;
    std::cout << (
        25 ? (x = 3, y++ || z++) : (++x || 1)
    );
    std::cout << x << y << z;
}
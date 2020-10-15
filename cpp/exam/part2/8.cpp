#include <vector>
#include <iostream>

int main() {
    std::cout << 0;
    throw int;
    std::cout << 1;
}
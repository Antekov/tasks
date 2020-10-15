#include <iostream>
int main() {
    int x = 5;
    int& rx = x;
    int* px = &x;
    int* prx = &rx;
    std::cout << (px == prx);
    ++*px;
    std::cout << (*px == *prx);
}
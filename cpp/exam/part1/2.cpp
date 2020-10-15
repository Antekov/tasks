#include <iostream>
int main() {
    int x = 1;
    const int &y = x;
    int &z = y;
    ++x;
    ++z;

    std::cout << x << y << z;
}
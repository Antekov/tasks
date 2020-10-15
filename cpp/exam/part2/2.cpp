#include <iostream>
int main() {
    int x = 1;
    const int &cx = 2;
    int y = 3;
    (y > 0 ? x : cx) = y;

    std::cout << x << cx << y;
}
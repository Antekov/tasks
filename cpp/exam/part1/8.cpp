#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};
    try {
        for (int i = 0; i < 5; ++i) {
            std::cout << *(v + i);
        }

    } catch (std::out_of_range& ex) {
        std::cout << "AAA";

    } catch (...) {
        std::cout << "BBB";
    }
}
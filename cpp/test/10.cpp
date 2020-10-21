#include <iostream>
#include <cstring>
#define N 20

using namespace std;

int main() {
    int n = 1;
    float m = 0;
    while (m > 0.1) {
        m = 1 / (float)n;
        n++;
    }
    cout << n;

    return 0;
}

int t() {

    return 6;
}

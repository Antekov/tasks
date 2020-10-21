#include <iostream>
#include <cstring>
#define N 20

using namespace std;

int main() {
    char s1[80] = "abcdefgh";
    char s2[80] = {};

    cout << strncpy(s2, (s1 + 2), 3);

    return 0;
}

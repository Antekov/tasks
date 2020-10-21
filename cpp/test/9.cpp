#include <iostream>
#include <cstring>
#define N 20

using namespace std;

int main() {
    char *s = "abcd";
    char * sb = new char[80];

    strcpy(sb, s);
    strcat(sb, "2");
    cout << sb;

    return 0;
}

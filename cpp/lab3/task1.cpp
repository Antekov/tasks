#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

int main() {
    const int N = 20;
    const int K = 2;
    int a[N], t;

    // [-4; 10]

    // rand() % 14 -> [0; 13] -> [-4; 9]
    // rand() % 15 -> [0; 14] -> [-4; 10]
    // 20 % 15 == 1*15 + 5 == 5
    // 33 % 15 == 2*15 + 3 == 3
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        a[i] = rand() % (5*K + 2*K + 1) - 2*K;
    }

    cout << "Input array:" << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(5) << a[i];
    }

    cout << endl;

    for (int i = 0; i < N; i += 2) {
        t = a[i + 1];
        a[i + 1] = a[i];
        a[i] = t;
    }

    cout << "Output array:" << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(5) << a[i];
    }

    cout << endl;

    return 0;    
}
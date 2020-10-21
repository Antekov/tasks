#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

int main() {
    const int N = 20;
    const int K = 2;
    int a[N], t, summ;

    cout << "Input array:" << endl;

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

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

    cout << a[10000000];

    return 0;    
}
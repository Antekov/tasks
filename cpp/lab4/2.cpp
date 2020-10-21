#include <iostream>
using namespace std;

int main() {
    int N, m;
    int *a;

    cin >> N >> m;

    a = new int[N];

    for (int i = 0; i < N; i++) { 
        *(a+i) = rand() % 41 - 20; 
    }

    cout << "Elements of A:" << endl;
    for (int i = 0; i < N; i++) {
        cout << *(a + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            //cout << i << "," << j << ": ";
            if (*(a+i) + *(a+j) == m) {
                cout << *(a+i) << " + " << *(a+j) << " = " << m << endl;
            } else {
                //cout << "!=" << m << endl;
            }
        }
    }

    cout << "Addresses of zero elements:" << endl;
    for (int i = 0; i < N; i++) {
        if (*(a+i) == 0) {
            cout << (a + i) << endl;
        }
    }

    delete[] a;

    return 0;
}
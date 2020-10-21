#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int b = 10;
    int* pN = &a;
    long long *pC, *pD;

    long long c[4] = {100, 200, 300, 400};
    pC = &c[0];
    pC = c;

    cout << pC+0 << ' ' << *(pC+0) << endl;
    cout << pC+1 << ' ' << *(pC+1) << endl;
    cout << pC+2 << ' ' << *(pC+2) << endl;
    cout << pC+3 << ' ' << *(pC+3) << endl;

    for (int i = 0; i <= 3; i++) {
        cout << c+i << ' ' << *(c+i) << endl;
    }

    pC = &c[3];
    pD = &c[1];

    cout << pC << ' ' << *pC << endl;
    cout << pC-1 << ' ' << *(pC-1) << endl;
    cout << pC-2 << ' ' << *(pC-2) << endl;
    cout << pC-3 << ' ' << *(pC-3) << endl;
    cout << pD - pC << endl;

    pC++; // pC = pC + 1

    pN = &b;

    if (pD > pC) {

    }

    cout << *pN << endl;

    cout << &a << endl
         << &pN << " " << pN << endl;

    cin >> a;
    
    pN = new int[a];

    for (int i = 0; i < 20; i++) { 
        *(pN+i) = rand() % 101 - 50; 
        pN[i] = rand() % 101 - 50;
    }
    delete[] pN;

    return 0;
}
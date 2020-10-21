#include <iostream>
#define N 20

using namespace std;

int main() {
    // Статические массивы

    int a[54]; // Массив целых чисел на 54 элемента

    double d[10]; // Массив вещественных чисел на 10 элементов

    char ch[N]; // Массив символов на N элементов (N = 20)

    const int M = 15;

    bool b[M]; // Массив логических значений на M элементов (M = 15)

    int a1[100000];

    int x;

    cout << "Address of x: " << &x << endl;
    x = 10;
    cout << "Value   of x: " << x << endl;

    int* y = &x;

    cout << "Value   of y: " << y << endl;

    cout << "Value   of *y == x: " << *y << endl;

    // Динамические массивы
    int *ar;

    ar = new int[100];

    for (int i = 0; i < 100; i++) {
        ar[i] = 2 * i + 1;
    }

    int n;

    cin >> n;

    int* a2 = new int[n];

    for (int i = 0; i < n; i++) {
        ar[i] = 2 * i + 1;
    }



    delete[] ar;
    delete[] a2;

    return 0;
}

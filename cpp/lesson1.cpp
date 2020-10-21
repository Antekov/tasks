#include <iostream>
using namespace std;

int main() {
    int a;
    int b;
    int c;

    a = 13;
    b = 5;

    c = a + b;
    c = a - b;
    c = a * b;
    c = a / b;
    c = a % b;

    c = (a + 7) / (b - 2);

    c = c + 1;
    c++;

    c += 20;
    c -= 2;
    c *= 2;
    c /= 3;
    c %= 7;

    cin >> a;

    std::cout << c << " " << a << " | " << (a + b - c) << "\n";
    cout << " " << 54 << "54" << "dfgvdhfie eihei" << endl;
  

    if (a > 10) 
    {
        cout << "a > 10" << endl;
    } 
    else 
    {
        cout << "a <= 10" << endl;
    }

    a = 0;

    while (a < 10) {
        cout << a << " ";
        a++;
    }
    cout << endl;
    
    a = 0;
    do {
        cout << a << " ";
        a++;
    } while (a < 10);

    int sum = 0;

    for (int i = 1; i <= 10; i++)
    {
        cout << "Input " << i << " number: ";
        cin >> a;
        sum = sum + a;
    }

    cin >> a >> b >> c;

    return 0;
}
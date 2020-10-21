#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    double a,b,dx,x, f, pi;
    pi = 3.1415926;
    pi = atan(1)*4;

    cout << "Input a, b, dx: ";
    cin >> a >> b >> dx;

    if (a <= b && dx > 0) {
        cout << endl << setw(15) << "Results" << endl << endl;
        cout << left << setw(15) << "x" << setw(15) << "F(x)" << endl << setprecision(9);

        x = a;
        do {
            if (x >= -4) {
                f = 5;
            } else if (x > -6) {
                f = 4*tan(pi*x/10) - pow((abs(5*x*x + x) + 3), 1/3.0);
            } else {
                f = pow(abs(x*x*x-4*x-1), 3/4.0);
            }
            cout << setw(15) << x << setw(15) << f << endl;
            x = x + dx;
        } while (x <= b);
    } else {
        cout << "Incorrect data" << endl;
    }
    
    return 0;    
}
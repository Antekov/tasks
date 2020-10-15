#include <iostream>

using namespace std;

class A {
public:
    A(){cout<<0;}
    A(A& a){cout << 1;}
    ~A(){cout<<2;}
};
 int main() {
     A a;
     {
         A a;
     }
    A b = a;     
}

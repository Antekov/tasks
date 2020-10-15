#include <iostream>
 void f();
 void g() {f();}

void f() {
    g();
}
 int main() {
     f();
     std::cout << 0;
 }

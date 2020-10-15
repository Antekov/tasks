#include <iostream>

struct Base {
    virtual void f() {std::cout << 1;}
};

struct Derived: public Base {
    void f() override {std::cout << 2;}
};

int main() {
Derived d;
Base& b = d;
Derived& dd = b;
d.f(), b.f(), dd.f();
}
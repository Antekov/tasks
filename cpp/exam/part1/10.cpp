#include <memory>
#include <iostream>

struct A {
    int x;
    A(int x) : x(x) { std::cout << x;  }
    ~A() { std::cout << x; }
};

int main() {
    std::shared_ptr<A> p(new A(1));
    std::shared_ptr<A> pp(new A(2));
    p = std::move(pp);
    std::cout << p.use_count() << pp.use_count();
}
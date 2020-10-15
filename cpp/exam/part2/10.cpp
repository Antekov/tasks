#include <memory>
#include <iostream>
int main() {
  int* p = new int(0);
  std::shared_ptr<int> sp(p);
  std::shared_ptr<int> ssp(p);
  *sp = *ssp;
  ssp = sp;
  std::cout << sp.use_count() << ssp.use_count();
}

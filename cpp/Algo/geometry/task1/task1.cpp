#include "task1.hpp"


int main() {
    freopen("input.txt", "r", stdin);

    double x1, y1, z1, x2, y2, z2;
    double x3, y3, z3, x4, y4, z4;

    freopen("input.txt", "r", stdin);
    
    std::cin >> x1 >> y1 >> z1;
    std::cin >> x2 >> y2 >> z2;
    std::cin >> x3 >> y3 >> z3;
    std::cin >> x4 >> y4 >> z4;

    double d = solve(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    
    std::cout << std::fixed << std::setprecision(7) << d << endl;
    
    return 0;
}
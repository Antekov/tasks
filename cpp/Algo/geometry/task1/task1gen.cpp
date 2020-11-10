#include "task1.hpp"
#include "task1source.hpp"

int main() {
    int N = 2;
    double ans, ans1;
    double x1, y1, z1, x2, y2, z2;
    double x3, y3, z3, x4, y4, z4;
    /*
    freopen("input.txt", "r", stdin);
    
    std::cin >> x1 >> y1 >> z1;
    std::cin >> x2 >> y2 >> z2;
    std::cin >> x3 >> y3 >> z3;
    std::cin >> x4 >> y4 >> z4;
    */

    double a[4]{0,1,3,7};
    double b[4]{2,5,1,4};
    double c[4]{-2, -1, 0, 3};

    z3 = 0; x4 = 2; y4 = 3; z4 = 5;

    for (int ix1 = 0; ix1 < N; ix1++) {
        for (int ix2 = 0; ix2 < N; ix2++) {
            for (int ix3 = 0; ix3 < N; ix3++) {
                for (int iy1 = 0; iy1 < N; iy1++) {
                    for (int iy2 = 0; iy2 < N; iy2++) {
                        for (int iy3 = 0; iy3 < N; iy3++) {
                            for (int iz1 = 0; iz1 < N; iz1++) {
                                for (int iz2 = 0; iz2 < N; iz2++) {
                                    x1 = a[ix1];
                                    x2 = b[ix2];
                                    x3 = a[ix3];
                                    y1 = a[iy1];
                                    y2 = b[iy2];
                                    y3 = c[iy3];
                                    z1 = c[iz1];
                                    z2 = b[iz2];
                                    
                                    ans = solve(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
                                    ans1 = solve1(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);

                                    if (abs(ans1 - ans) > 0.0000001) {
                                        std::cout << x1 << ' ' << y1 << ' ' << z1 << std::endl;
                                        std::cout << x2 << ' ' << y2 << ' ' << z2 << std::endl;
                                        std::cout << x3 << ' ' << y3 << ' ' << z3 << std::endl;
                                        std::cout << x4 << ' ' << y4 << ' ' << z4 << std::endl;
                                        std::cout << ans << " != " << ans1 << std::endl;
                                    } else {
                                        std::cout << ans << " == " << ans1 << std::endl;
                                    }
                                }    
                            }
                        }
                    }    
                }
            }
        }    
    }
    

    return 0;
}
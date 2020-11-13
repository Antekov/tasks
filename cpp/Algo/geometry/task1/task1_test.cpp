#include "task1.hpp"

int main() {
    freopen("input_test.txt", "r", stdin);

    double x, y, z, ans;
    string comment;
    int t;

    cin >> t;

    while (t--) {
        cin >> comment;
        cin >> x >> y >> z;
        Point3D A{x, y, z};

        cin >> x >> y >> z;
        Point3D B{x, y, z};

        cin >> x >> y >> z;
        Point3D C{x, y, z};

        cin >> x >> y >> z;
        Point3D D{x, y, z};

        cin >> ans;

        Vector3D AB(A, B);
        Vector3D CD(C, D);
        
        if (AB.cosPhi(CD) > 0) {
            std::swap(C, D);
        }

        Vector3D u(A, B);
        Vector3D v(C, D);

        double d = dist(u, v);
        
        std::cerr << comment << std::endl;
        std::cout << std::fixed << std::setprecision(7) << d << endl;
        assert(abs(d - ans) < 0.000001);
    }
    return 0;
}
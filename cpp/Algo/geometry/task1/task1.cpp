#include <iostream>
#include <iomanip>
#include <cmath>
#define DBL_EPSILON 2.2204460492503131e-016

using namespace std;

class Vector3D;

struct Point3D {
    double x = 0;
    double y = 0;
    double z = 0;

    Point3D(const double x=0, const double y=0, const double z=0) : x(x), y(y), z(z) {}
    Point3D(const Point3D& ) = default;
    Point3D(const Vector3D& v);
};

class Vector3D {
    friend class Point3D;

public:
    double x, y, z;
    Point3D start;

    Vector3D(double x=0, double y=0, double z=0, Point3D start={0,0,0}) : x(x), y(y), z(z), start(start) {}
    Vector3D(const Point3D &A) 
        : x(A.x), y(A.y), z(A.z) {}
    Vector3D(const Point3D &A, const Point3D &B) 
        : x(B.x - A.x), y(B.y - A.y), z(B.z - A.z), start(A) {}

    Vector3D operator*(const double a) {
        return Vector3D(x*a, y*a, z*a, start);
    }

    double norm() {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3D operator+(const Vector3D &other) {
        return Vector3D(x + other.x, y + other.y, z + other.z, start);
    }

    double operator*(const Vector3D &v) {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3D operator^(const Vector3D &v) {
        return Vector3D(y*v.z - z*v.y, x*v.z - z*v.x, x*v.y - y*v.x, start);
    }

    friend ostream& operator<<(ostream &out, Vector3D &v) {
        out << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ") from (" 
            << v.start.x << ", " << v.start.y << ", " << v.start.z << ")";
        return out;
    }
};

Point3D::Point3D(const Vector3D& v) :
    Point3D(v.x + v.start.x, v.y + v.start.y, v.z + v.start.z) {}

int main() {
    freopen("input.txt", "r", stdin);

    double x, y, z;

    cin >> x >> y >> z;
    Point3D A{x, y, z};

    cin >> x >> y >> z;
    Point3D B{x, y, z};

    cin >> x >> y >> z;
    Point3D C{x, y, z};

    cin >> x >> y >> z;
    Point3D D{x, y, z};

    Vector3D AB(A, B);
    Vector3D CD(C, D);
    Vector3D AC(A, C);

    std::cerr << AB << endl;
    std::cerr << CD << endl;

    Vector3D u = AB;
    Vector3D v = CD;

    Vector3D w = AC;

    double u2 = u * u;
    double v2 = v * v;
    double uv = u * v;
    double wu = w * u;
    double wv = w * v;

    std::cerr << "(u2 * v2 - u2 * uv * uv)=" << (u2 * v2 - u2 * uv * uv) << endl;

    double b = (wu * uv - wv * u2) / (u2 * v2 - u2 * uv * uv);
    double a = (wu + b * uv) / u2;

    std::cerr << "a, b = "<< a << ", " << b << endl;

    Vector3D au = u*a;
    Vector3D bv = v*b;

    std::cerr << "au: " << au << endl;
    std::cerr << "bv: " << bv << endl;

    Point3D M, N;

    if (a <= DBL_EPSILON) {
        std::cerr << "Point A" << std::endl;
        M = A;
    } else if (a < 1) {
        std::cerr << "Point M" << std::endl;
        M = au;
    } else {
        std::cerr << "Point B" << std::endl;
        M = B;
    }

    if (b <= DBL_EPSILON) {
        std::cerr << "Point C" << std::endl;
        N = C;
    } else if (b < 1) {
        std::cerr << "Point N" << std::endl;
        N = bv;
    } else {
        std::cerr << "Point D" << std::endl;
        N = D;
    }


    //Point3D M{au.x + au.start.x, au.y + au.start.y, au.z + au.start.z};
    //Point3D M = au;
    //Point3D N{bv.x + bv.start.x, bv.y + bv.start.y, bv.z + bv.start.z};
    //Point3D N(bv);

    //Vector3D n(M, N);
    Vector3D n(M, N);

    std::cerr << "MN: " << n << endl;

    std::cerr << "d(MN) = " << n.norm() << endl;

    std::cout << std::fixed << std::setprecision(6) << n.norm() << endl;



    return 0;
}
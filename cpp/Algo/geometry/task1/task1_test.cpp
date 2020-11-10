#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
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

    friend ostream& operator<<(ostream &out, const Point3D &v) {
        out << "Point3D(" << v.x << ", " << v.y << ", " << v.z << ")";
        return out;
    }
};

class Vector3D {
    friend class Point3D;

public:
    double x, y, z;
    Point3D start;

    Vector3D(const double x=0, const double y=0, const double z=0, Point3D start={0,0,0}) : x(x), y(y), z(z), start(start) {}
    Vector3D(const Point3D &A) 
        : x(A.x), y(A.y), z(A.z) {}
    Vector3D(const Point3D &A, const Point3D &B) 
        : x(B.x - A.x), y(B.y - A.y), z(B.z - A.z), start(A) {}

    Vector3D operator*(const double a) const {
        return Vector3D(x*a, y*a, z*a, start);
    }

    double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3D operator+(const Vector3D &other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z, start);
    }

    Vector3D operator-(const Vector3D &other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z, start);
    }

    double operator*(const Vector3D &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3D operator^(const Vector3D &v) const {
        return Vector3D(y*v.z - z*v.y, x*v.z - z*v.x, x*v.y - y*v.x, start);
    }

    double mix(const Vector3D &a, const Vector3D &b) {
        return x * (a.y*b.z - a.z*b.y) - y * (a.x*b.z - a.z * b.x) + z * (a.x*b.y - a.y*b.x);
    }

    bool isCoplanar(const Vector3D &a) const {
        double mix = Vector3D(this->start, a.start).mix(*this, a);

        return abs(mix) < DBL_EPSILON;
    }

    double cosPhi(const Vector3D &a) const {
        if (this->norm() * a.norm() <= DBL_EPSILON) {
            return 1;
        }
    
        return *this * a / (this->norm() * a.norm());
    }

    bool isCollinear(const Vector3D &a) const{
        return (abs(abs(this->cosPhi(a)) - 1) < DBL_EPSILON);
    }

    friend ostream& operator<<(ostream &out, const Vector3D &v) {
        out << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ") from (" 
            << v.start.x << ", " << v.start.y << ", " << v.start.z << ")";
        return out;
    }
};

Point3D::Point3D(const Vector3D& v) :
    Point3D(v.x + v.start.x, v.y + v.start.y, v.z + v.start.z) {}

double dist(Vector3D u, Vector3D v) {
    Point3D A, B, C, D, M, N;
    A = u.start;
    B = u;
    C = v.start;
    D = v;

    Vector3D w(u.start, v.start);

    std::cerr << "u: " << u << endl;
    std::cerr << "v: " << v << endl;
    std::cerr << "w: " << w << endl;

    if (u.isCollinear(v)) {
        std::cerr << "AB collinear to CD" << std::endl;
        M = v.start;
        
        if (u.cosPhi(w) > 0) {
            N = u * (1/u.norm()) * w.norm() * u.cosPhi(w);
        } else {
            N = u.start;
        }
    } else if (u.isCoplanar(v)) {
        std::cerr << "AB coplanar to CD" << std::endl;
        double Det1 = -u.x * v.y + v.x * u.y;
        double Det2 = -u.x * v.z + v.x * u.z;
        double Det3 = -u.y * v.z + v.y * u.z;
        double Deta = 0, Detb = 0, a, b;

        std::cerr << " " << Det1 << " " << Det2 << " " << Det3 << std::endl;

        if (abs(Det1) > DBL_EPSILON) {
            Deta = -w.x * v.y + w.y * v.x;
            Detb = u.x * w.y - u.y * w.x;
            a = Deta / Det1;
            b = Detb / Det1;
        } else if (abs(Det2) > DBL_EPSILON) {
            Deta = -w.x * v.z + w.z * v.x;
            Detb = u.x * w.z - u.z * w.x;
            a = Deta / Det2;
            b = Detb / Det2;
        } else if (abs(Det3) > DBL_EPSILON) {
            Deta = -w.y * v.z + w.z * v.y;
            Detb = u.y * w.z - u.z * w.y;
            a = Deta / Det3;
            b = Detb / Det3;
        }

        std::cerr << "a, b = "<< a << ", " << b << endl;

        Vector3D au = u * a;
        Vector3D bv = v * b;


        Point3D P1, P2, P, E, O = au;
        if (a <= DBL_EPSILON) {
            std::cerr << "Point A" << std::endl;
            M = A;
            P1 = B;
        } else if (a < 1) {
            std::cerr << "Point M" << std::endl;
            M = au;
            P1 = A;
        } else {
            std::cerr << "Point B" << std::endl;
            M = B;
            P1 = A;
        }

        if (b <= DBL_EPSILON) {
            std::cerr << "Point C" << std::endl;
            N = C;
            P2 = D;
        } else if (b < 1) {
            std::cerr << "Point N" << std::endl;
            N = bv;
            P2 = C;
        } else {
            std::cerr << "Point D" << std::endl;
            N = D;
            P2 = C;
        }
        std::cerr << "M: " << M << std::endl;
        std::cerr << "N: " << N << std::endl;

        if (Vector3D(M, O).norm() < Vector3D(N, O).norm()) {
            std::swap(M, N);
            P = P1;
        } else {
            P = P2;
        }

        double cos_phi = abs(u * v / (sqrt(u * u)*sqrt(v * v)));
        double sin_phi = sqrt(1 - cos_phi * cos_phi);

        Vector3D MO(M, O);
        Vector3D PN(P, N);
        Vector3D OP(O, P);
        Vector3D ON(O, N);

        Vector3D OE = OP * (1/OP.norm()) * MO.norm() * cos_phi;

        if (OE.norm() > OP.norm()) {
            N = P;    
        } else if (OE.norm() > ON.norm()){
            N = Point3D(OE);
        }

        std::cerr << "A: " << A << std::endl;
        std::cerr << "B: " << B << std::endl;
        std::cerr << "C: " << C << std::endl;
        std::cerr << "D: " << D << std::endl;
        std::cerr << "P: " << P << std::endl;
        std::cerr << "M: " << M << std::endl;
        std::cerr << "N: " << N << std::endl;

        
    } else {
        std::cerr << "AB not coplanar to CD" << std::endl;

        double u2 = u * u;
        double v2 = v * v;
        double uv = u * v;
        double wu = w * u;
        double wv = w * v;

        double a = (-wu * v2 + wv * uv) / (uv * uv - u2 * v2);
        double b = (u2 * wv - wu * uv) / (uv * uv - u2 * v2);

        std::cerr << "cos(phi) = " << uv / (sqrt(u2)*sqrt(v2)) << std::endl;

        std::cerr << "(wu) = " << (wu) << endl;
        std::cerr << "(wv) = " << (wv) << endl;
        std::cerr << "(uv - u2) = " << (uv - u2) << endl;
        std::cerr << "(uv - v2) = " << (uv - v2) << endl;
        std::cerr << "(uv*uv - u2*v2) = " << (uv*uv - u2*v2) << endl;

        std::cerr << u2 << " " << -uv << std::endl;
        std::cerr << uv << " " << -v2 << std::endl;
        std::cerr << wu << std::endl;
        std::cerr << wv << std::endl;

            
        

        std::cerr << "a, b = "<< a << ", " << b << endl;
       

        Vector3D au = u*a;
        Vector3D bv = v*b;

        std::cerr << "au: " << au << endl;
        std::cerr << "bv: " << bv << endl;

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

        Vector3D n(au, bv);
        std::cerr << "n: " << n << std::endl;
        std::cerr << au + n << " == " << w + bv << std::endl;

        std::cerr << "(n * u): " << n * u << std::endl;
        std::cerr << "(n * u) = w * u + b*uv - a*u2: " << w * u + b*uv - a*u2 << std::endl;
        std::cerr << "(n * v): " << n * v << std::endl;

        std::cerr << "(n * v) = w * v + b*v2 - a*uv: " << w * v + b*v2 - a*uv << std::endl;

        
    }

    Vector3D n(M, N);
        
    std::cerr << "MN: " << n << endl;
    std::cerr << "d(MN) = " << n.norm() << endl;

    return n.norm();
}

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
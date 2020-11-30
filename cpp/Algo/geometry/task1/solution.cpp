#include <iostream>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include <algorithm>
using namespace std;

class Vector3D;

struct Point3D {
    double x = 0;
    double y = 0;
    double z = 0;

    Point3D(const double x=0, const double y=0, const double z=0) : x(x), y(y), z(z) {}
    Point3D(const Point3D& ) = default;
    Point3D(const Vector3D& v);

    double dist_to(const Vector3D &u) const;

    friend std::ostream& operator<<(std::ostream &out, const Point3D &v) {
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

    Point3D end() {
        return Point3D(*this);
    }

    bool is_inside(double a) const {
        return (0 <= a && a <= 1.0);
    }

    bool is_longer(double a) const {
        return (a > 1.0);
    }

    bool is_opposite(double a) const {
        return (a < 0);
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

    bool isCollinear(const Vector3D &a) const {
        //std::cerr << "isCollinear: " << this->cosPhi(a) << " " << abs(abs(this->cosPhi(a)) - 1) << endl;
        return (abs(abs(this->cosPhi(a)) - 1) <= DBL_EPSILON);
    }

    friend std::ostream& operator<<(std::ostream &out, const Vector3D &v) {
        out << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ") from (" 
            << v.start.x << ", " << v.start.y << ", " << v.start.z << ")";
        return out;
    }
};

Point3D::Point3D(const Vector3D& v) :
    Point3D(v.x + v.start.x, v.y + v.start.y, v.z + v.start.z) {}

double Point3D::dist_to(const Vector3D &u) const {
    Vector3D w(u.start, *this);
    
    Point3D N;
    if (u.cosPhi(w) > 0) {
        N = u * std::min(1.0, (1/u.norm()) * w.norm() * u.cosPhi(w));
    } else {
        N = u.start;
    }
    
    return Vector3D(*this, N).norm();
}

double dist_collinear(Vector3D u, Vector3D v) {
    return std::min(
            std::min(v.start.dist_to(u), v.end().dist_to(u)),
            std::min(u.start.dist_to(v), u.end().dist_to(v))
        );
}

double dist_coplanar(Vector3D u, Vector3D v) {
    Point3D A, B, C, D, M, N;
    A = u.start;
    B = u.end();
    C = v.start;
    D = v.end();
    Vector3D w(u.start, v.start);

    double Det1 = -u.x * v.y + v.x * u.y;
    double Det2 = -u.x * v.z + v.x * u.z;
    double Det3 = -u.y * v.z + v.y * u.z;
    double Deta = 0, Detb = 0, a, b;

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

    Vector3D au = u * a;
    Vector3D bv = v * b;
    Point3D P1, P2, P, E, O = au.end();

    if (au.is_opposite(a)) {
        M = A;
        P1 = B;
    } else if (au.is_inside(a)) {
        M = au;
        P1 = A;
    } else {
        //std::cerr << "Point B" << std::endl;
        M = B;
        P1 = A;
    }

    if (bv.is_opposite(b)) {
        //std::cerr << "Point C" << std::endl;
        N = C;
        P2 = D;
    } else if (bv.is_inside(b)) {
        //std::cerr << "Point N" << std::endl;
        N = bv;
        P2 = C;
    } else {
        //std::cerr << "Point D" << std::endl;
        N = D;
        P2 = C;
    }
    
    if (Vector3D(M, O).norm() < Vector3D(N, O).norm()) {
        std::swap(M, N);
        P = P1;
    } else {
        P = P2;
    }
    
    Vector3D MO(M, O);
    Vector3D PN(P, N);
    Vector3D OP(O, P);
    Vector3D ON(O, N);

    Vector3D OE = OP * (1/OP.norm()) * MO.norm() * abs(u.cosPhi(v));

    if (OE.norm() > OP.norm()) {
        N = P;    
    } else if (OE.norm() > ON.norm()){
        N = Point3D(OE);
    }

    return Vector3D(M, N).norm();
}

double dist_not_coplanar(Vector3D u, Vector3D v) {
    Point3D A, B, C, D, M, N;
    A = u.start;
    B = u.end();
    C = v.start;
    D = v.end();
    Vector3D w(u.start, v.start);

    double u2 = u * u;
    double v2 = v * v;
    double uv = u * v;
    double wu = w * u;
    double wv = w * v;

    double a = (-wu * v2 + wv * uv) / (uv * uv - u2 * v2);
    double b = (u2 * wv - wu * uv) / (uv * uv - u2 * v2);

    Vector3D au = u*a;
    Vector3D bv = v*b;

    M = au.end();
    N = bv.end();

    if (au.is_inside(a) && !bv.is_inside(b)) {
        //std::cerr << "M: Point au" << std::endl;
        if (bv.is_opposite(b)) {
            //std::cerr << "N: Point C" << std::endl;
            N = C;
        } else if (bv.is_longer(b)) {
            //std::cerr << "N: Point D" << std::endl;
            N = D;
        }
        return N.dist_to(u);        
    } else if (!au.is_inside(a) && bv.is_inside(b)) {
        //std::cerr << "N: Point bv" << std::endl;
        if (au.is_opposite(a)) {
            //std::cerr << "M: Point A" << std::endl;
            M = A;
        } else if (au.is_longer(a)) {
            //std::cerr << "M: Point B" << std::endl;
            M = B;
        }
        return M.dist_to(v);
    } else if (au.is_opposite(a) && bv.is_opposite(b)) {
        if (Vector3D(M, A).norm() < Vector3D(N, C).norm()) {
            //std::cerr << "a < 0, b < 0, MA < NC" << endl;
            return C.dist_to(u); 
        } else {
            //std::cerr << "a < 0, b < 0, MA >= NC: " << Vector3D(M, A).norm() << " >= " << Vector3D(N, C).norm() << endl;
            return A.dist_to(v);
        }
    } else if (au.is_longer(a) && bv.is_longer(b)) {
        if (Vector3D(M, B).norm() < Vector3D(N, D).norm()) {
            //std::cerr << "a > 1, b > 1, MB < ND" << endl;
            return D.dist_to(u); 
        } else {
            //std::cerr << "a > 1, b > 1, MB >= ND: " << Vector3D(M, B).norm() << " >= " << Vector3D(N, D).norm() << endl;
            return B.dist_to(v);
        }

    } else if (au.is_opposite(a) && bv.is_longer(b)) {
        if (Vector3D(M, A).norm() < Vector3D(N, D).norm()) {
            //std::cerr << "a < 0, b > 1, MA < ND" << endl;
            return D.dist_to(u); 
        } else {
            //std::cerr << "a < 0, b > 1, MA >= ND: " << Vector3D(M, A).norm() << " >= " << Vector3D(N, D).norm() << endl;
            return A.dist_to(v);
        }
    } else if (au.is_longer(a) && bv.is_opposite(b)) {
        if (Vector3D(M, B).norm() < Vector3D(N, C).norm()) {
            //std::cerr << "a > 1, b < 0, MB < NC" << endl;
            return C.dist_to(u); 
        } else {
            //std::cerr << "a > 1, b < 0, MB >= NC: " << Vector3D(M, B).norm() << " >= " << Vector3D(N, C).norm() << endl;
            return B.dist_to(v);
        }
    } else {
        return Vector3D(M, N).norm();
    }
}

double dist(Vector3D u, Vector3D v) {
    if (u.isCollinear(v)) {
        //std::cerr << "AB collinear to CD" << std::endl;
        return dist_collinear(u, v);
    } else if (u.isCoplanar(v)) {
        //std::cerr << "AB coplanar to CD" << std::endl;
        return dist_coplanar(u, v);
    } else {
        //std::cerr << "AB not coplanar to CD" << std::endl;
        return dist_not_coplanar(u, v);
    }
}

double solve(double x1, double y1, double z1,
    double x2, double y2, double z2,
    double x3, double y3, double z3,
    double x4, double y4, double z4) {
    
    return dist(
        Vector3D({x1, y1, z1}, {x2, y2, z2}), 
        Vector3D({x3, y3, z3}, {x4, y4, z4})
    );
}

int main() {
    double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> x4 >> y4 >> z4;

    double d = solve(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    
    std::cout << std::fixed << std::setprecision(7) << d << std::endl;
    
    return 0;
}
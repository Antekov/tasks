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
        //std::cerr << "u1: " << u << endl;
        //std::cerr << "C1: " << C << endl; 
        Vector3D w(u.start, *this);
        //std::cerr << "w1: " << w << endl;
        Point3D N;
        if (u.cosPhi(w) > 0) {
            N = u * std::min(1.0, (1/u.norm()) * w.norm() * u.cosPhi(w));
        } else {
            //std::cerr << "N = u.start" << endl; 
            N = u.start;
        }
        //std::cerr << "M: " << M << std::endl;
        //std::cerr << "N: " << N << std::endl;
        return Vector3D(*this, N).norm();
    }

double dist1(Vector3D u, Point3D C) {
    //std::cerr << "u1: " << u << endl;
    //std::cerr << "C1: " << C << endl; 
    Vector3D w(u.start, C);
    //std::cerr << "w1: " << w << endl;
    Point3D M = C, N;
    if (u.cosPhi(w) > 0) {
        N = u * std::min(1.0, (1/u.norm()) * w.norm() * u.cosPhi(w));
    } else {
        //std::cerr << "N = u.start" << endl; 
        N = u.start;
    }
    //std::cerr << "M: " << M << std::endl;
    //std::cerr << "N: " << N << std::endl;
    return Vector3D(M, N).norm();
}

double dist(Vector3D u, Vector3D v) {
    Point3D A, B, C, D, M, N;
    A = u.start;
    B = u.end();
    C = v.start;
    D = v.end();

    Vector3D w(u.start, v.start);

    if (u.isCollinear(v)) {
        //std::cerr << "AB collinear to CD" << std::endl;
        return std::min(
            std::min(v.start.dist_to(u), v.end().dist_to(u)),
            std::min(u.start.dist_to(v), u.end().dist_to(v))
        );
    } else if (u.isCoplanar(v)) {
        //std::cerr << "AB coplanar to CD" << std::endl;
        double Det1 = -u.x * v.y + v.x * u.y;
        double Det2 = -u.x * v.z + v.x * u.z;
        double Det3 = -u.y * v.z + v.y * u.z;
        double Deta = 0, Detb = 0, a, b;

        //std::cerr << " " << Det1 << " " << Det2 << " " << Det3 << std::endl;

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

        //std::cerr << "a, b = "<< a << ", " << b << endl;

        Vector3D au = u * a;
        Vector3D bv = v * b;


        Point3D P1, P2, P, E, O = au;
        if (a <= DBL_EPSILON) {
            //std::cerr << "Point A" << std::endl;
            M = A;
            P1 = B;
        } else if (a < 1.0) {
            //std::cerr << "Point M" << std::endl;
            M = au;
            P1 = A;
        } else {
            //std::cerr << "Point B" << std::endl;
            M = B;
            P1 = A;
        }

        if (b <= DBL_EPSILON) {
            //std::cerr << "Point C" << std::endl;
            N = C;
            P2 = D;
        } else if (b < 1.0) {
            //std::cerr << "Point N" << std::endl;
            N = bv;
            P2 = C;
        } else {
            //std::cerr << "Point D" << std::endl;
            N = D;
            P2 = C;
        }
        //std::cerr << "M: " << M << std::endl;
        //std::cerr << "N: " << N << std::endl;

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

        //std::cerr << "A: " << A << std::endl;
        //std::cerr << "B: " << B << std::endl;
        //std::cerr << "C: " << C << std::endl;
        //std::cerr << "D: " << D << std::endl;
        //std::cerr << "P: " << P << std::endl;
        //std::cerr << "M: " << M << std::endl;
        //std::cerr << "N: " << N << std::endl;
        return Vector3D(M, N).norm();
        
    } else {
        std::cerr << "AB not coplanar to CD" << std::endl;

        double u2 = u * u;
        double v2 = v * v;
        double uv = u * v;
        double wu = w * u;
        double wv = w * v;

        double a = (-wu * v2 + wv * uv) / (uv * uv - u2 * v2);
        double b = (u2 * wv - wu * uv) / (uv * uv - u2 * v2);

        //std::cerr << "cos(phi) = " << uv / (sqrt(u2)*sqrt(v2)) << std::endl;

        //std::cerr << "(wu) = " << (wu) << endl;
        //std::cerr << "(wv) = " << (wv) << endl;
        //std::cerr << "(uv - u2) = " << (uv - u2) << endl;
        //std::cerr << "(uv - v2) = " << (uv - v2) << endl;
        //std::cerr << "(uv*uv - u2*v2) = " << (uv*uv - u2*v2) << endl;

        //std::cerr << u2 << " " << -uv << std::endl;
        //std::cerr << uv << " " << -v2 << std::endl;
        //std::cerr << wu << std::endl;
        //std::cerr << wv << std::endl;

            
        

        //std::cerr << "a, b = "<< a << ", " << b << endl;
       

        Vector3D au = u*a;
        Vector3D bv = v*b;

        //std::cerr << "au: " << au << endl;
        //std::cerr << "bv: " << bv << endl;
        M = au;
        N = bv;

        if ((0 <= a && a <= 1.0) && !(0 <=b && b <= 1.0)) {
            //std::cerr << "M: Point au" << std::endl;

            if (b <= DBL_EPSILON) {
                //std::cerr << "N: Point C" << std::endl;
                N = C;
            } else if (b > 1.0) {
                //std::cerr << "N: Point D" << std::endl;
                N = D;
            }
            return dist1(u, N);
            
        } else if (!(0 <= a && a <= 1.0) && (0 <= b && b <= 1.0)) {
            //std::cerr << "N: Point bv" << std::endl;
            
            if (a <= DBL_EPSILON) {
                //std::cerr << "M: Point A" << std::endl;
                M = A;
            } else if (a > 1.0) {
                //std::cerr << "M: Point B" << std::endl;
                M = B;
            }
            return dist1(v, M);
        } else if (a < 0 && b < 0) {
            if (Vector3D(M, A).norm() < Vector3D(N, C).norm()) {
                //std::cerr << "a < 0, b < 0, MA < NC" << endl;
                return dist1(u, C); 
            } else {
                //std::cerr << "a < 0, b < 0, MA >= NC: " << Vector3D(M, A).norm() << " >= " << Vector3D(N, C).norm() << endl;
                return dist1(v, A);
            }
        } else if (a > 1.0 && b > 1.0) {
            if (Vector3D(M, B).norm() < Vector3D(N, D).norm()) {
                //std::cerr << "a > 1, b > 1, MB < ND" << endl;
                return dist1(u, D); 
            } else {
                //std::cerr << "a > 1, b > 1, MB >= ND: " << Vector3D(M, B).norm() << " >= " << Vector3D(N, D).norm() << endl;
                return dist1(v, B);
            }

        } else if (a < 0 && b > 1) {
            if (Vector3D(M, A).norm() < Vector3D(N, D).norm()) {
                //std::cerr << "a < 0, b > 1, MA < ND" << endl;
                return dist1(u, D); 
            } else {
                //std::cerr << "a < 0, b > 1, MA >= ND: " << Vector3D(M, A).norm() << " >= " << Vector3D(N, D).norm() << endl;
                return dist1(v, A);
            }
        } else if (a > 1 && b < 0) {
            if (Vector3D(M, B).norm() < Vector3D(N, C).norm()) {
                //std::cerr << "a > 1, b < 0, MB < NC" << endl;
                return dist1(u, C); 
            } else {
                //std::cerr << "a > 1, b < 0, MB >= NC: " << Vector3D(M, B).norm() << " >= " << Vector3D(N, C).norm() << endl;
                return dist1(v, B);
            }
        } else {
            return Vector3D(M, N).norm();
        }
      
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
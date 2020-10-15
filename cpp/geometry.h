#include <initializer_list>
#include <utility>
#include <typeinfo>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

const double eps = 0.0000000001;
const double pi = 4*atan(1);

struct Point {
    // static const double eps;
    double x, y;
    
    Point() : x(0), y (0) {}
    Point(double x) : x(x), y(x) {}
    Point(double x, double y) : x(x), y(y) {}

    bool is_infinity() const { return (x == INFINITY || y == INFINITY); }

    bool operator!=(const Point &other) const { 
        return (abs(this->x - other.x) > eps || abs(this->y - other.y) > eps);
    }
    bool operator==(const Point &other) const {
        return !(*this != other);
    }

    Point & rotate(Point center, double angle) {
        //cerr << "rotate(" << center << angle << ")"<< endl;
        angle = angle / 180 * pi;

        //cerr << angle << endl;

        double x1 = cos(angle)*(x - center.x) - sin(angle) * (y - center.y) + center.x;
        double y1 = sin(angle)*(x - center.x) + cos(angle) * (y - center.y) + center.y;
        x = x1;
        y = y1;
        return *this;
    }

    Point & reflex(Point center) {
        x = center.x - (x - center.x);
        y = center.y - (y - center.y);
        return *this;
    }

    Point & operator-() const {
        return *new Point(-x, -y);
    }

    Point & operator+(const Point &another) const {
        return *new Point(x + another.x, y + another.y);
    }

    Point & operator*(double k) const {
        return *new Point(k*x, k*y);
    }

    Point & scale(Point center, double coefficient) {
        x = (x - center.x) * coefficient + center.x;
        y = (y - center.y) * coefficient + center.y;
        return *this;
    }

    Point & move(Point vector) {
        x += vector.x;
        y += vector.y;
        return *this;
    }

    double distanceTo(const Point & another) const {
        return sqrt((x - another.x) * (x - another.x) + (y - another.y) * (y - another.y));
    }

    friend ostream &operator<<(ostream &stream, const Point &o);
};

class Line {
    // static const double eps;
    double k, b, x;
    bool is_vertical;
    pair<Point, Point> points;

public:
    Line() : k(1), b(0), is_vertical(false) {}
    Line(double k, double b) : k(k), b(b), is_vertical(k == INFINITY) {}
    Line(const Point p, double k) : k(k), b(-k*p.x + p.y), is_vertical(k == INFINITY) {}
    Line(const Point &a, const Point &c) {
        points.first = a;
        points.second = c;

        if (abs(a.x - c.x) > eps) {
            x = 0;
            k = (a.y - c.y) / (a.x - c.x);
            b = a.y - k * a.x;

            is_vertical = false;
        } else {
            k = 0;
            b = 0;
            x = a.x;
            is_vertical = true;
        }
    }

    double a() const { return k; }
    double c() const { return b; }

    bool operator!=(const Line &other) const { 
        return (abs(this->k - other.k) > eps || abs(this->b - other.b) > eps
            || abs(this->x - other.x) > eps);
    }
    bool operator==(const Line &other) const {
        return !(*this != other);
    }
    bool operator<(const Line &other) const { 
        return this->k < other.k ? true : 
            (this->b < other.b ? true : 
                (this->x < other.x ? true : false));
    }

    Line & perpendicular(const Point &p) const {
        if (is_vertical) {
            Point p2 = Point(x, p.y);

            if (p != p2) {
                return *new Line(p, p2);
            } else {
                return *new Line(p, Point(x-1, p.y));
            }
        }
        // cout << "perpendicular to "; 
        // cout << *new Line(*this) << endl;
        // cout << "Ort: k = " << -1/k << ", b = " << p.y + p.x/k << endl;
        if (k == 0) {
            // cout << "P! = " << p << endl;

            return *new Line(p, Point(p.x, p.y+1));
        }

        return *new Line(-1/k, p.y + p.x/k);
    }

    Point & cross(const Line &another) const {
        if (is_vertical && another.is_vertical) {
            return *new Point(INFINITY, INFINITY);
        }

        if (is_vertical) {
            // cout << "111111" << endl;
            return *new Point(x, another.k * x + another.b);
        }

        if (another.is_vertical) {
            // cout << "222222" << endl;
            // cout << *this << endl;
            // cout << another << endl;
            return *new Point(another.x, k * another.x + b);
        }

        if (abs(k - another.k) < eps) {
            return *new Point(INFINITY, INFINITY);
        }

        double x, y;
        x = (another.b - b) / (k - another.k);
        y = k * x + b;
        return *new Point(x, y);
    }

    friend ostream &operator<<(ostream &stream, Line &o);
    friend ostream &operator<<(ostream &stream, const Line &o);
};

struct PointLine : public Point {
    PointLine(const Point & p) : Point(p) {}
    Point &projection(const Line & line) {
        return line.cross(line.perpendicular(*this));
    }

    Point & reflex(const Line &axis) {
        Point c = projection(axis);
        // cerr << c << endl;
        // cerr << Point(x, y) << endl;
        c = Point(x, y).reflex(c);
        // cerr << c << endl;
        return *new Point(c);
    }
};

class Shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const Shape &another) const = 0;
    virtual bool operator!=(const Shape &another) const { return !(*this == another); }
    virtual bool isCongruentTo(const Shape &another) const = 0;
    virtual bool isSimilarTo(const Shape &another) const = 0;
    virtual bool containsPoint(const Point &point) const = 0;

    virtual Shape & rotate(Point center, double angle) = 0;
    virtual Shape & reflex(Point center) = 0;
    virtual Shape & reflex(Line axis) = 0;
    virtual Shape & scale(Point center, double coefficient) = 0;
    virtual ~Shape() {}
};

class Ellipse : public Shape {
protected:
    Point f1, f2, cent;
    Line d1, d2;
    double dist;
    double c;
    double a, b;
    double e;
    double p;
    virtual void calc();

public:
    Ellipse(const Point &f1, const Point &f2, double dist);

    Ellipse(pair<Point, Point> f, double dist) : Ellipse(f.first, f.second, dist) {}
    ~Ellipse() {}

    pair<Point, Point> focuses() const { return pair<Point, Point>{f1, f2}; }
    pair<Line, Line> directrices() const {
        cerr << "dir of " << *this << endl;
        double angle = atan2(f2.y-f1.y, f2.x-f1.x) / pi * 180;
        
        Point f3(f1.x + 2*c, f1.y);
        Point dp1(f1.x - p/e, f1.y), dp2(f3.x + p/e, f3.y);
        
        Line d1(dp1.rotate(f1, angle), Point(dp1.x, dp1.y+1).rotate(f1, angle));
        Line d2(dp2.rotate(f1, angle), Point(dp2.x, dp2.y+1).rotate(f1, angle));

        cerr << d1 << endl;
        cerr << d2 << endl;
        return pair<Line, Line>{d1, d2}; 
    }

    double r1() const { return a; }
    double r2() const { return b; }

    double eccentricity() const { 
        cerr << "ecc of " << *this << endl;
        double c = f1.distanceTo(f2) * 0.5;
        
        double a = dist - c;
//0,72111
        a = dist / 2;
        return c / a; 
    }
    Point center() const { return Point((f1.x + f2.x)/2, (f1.y + f2.y)/2); }

    double perimeter() const {
        cerr << "per of " << *this << endl; 
        double k = 3*(a-b)*(a-b)/(a+b)/(a+b);
        return pi*(a+b)*(1 + k/(10 + sqrt(4 - k)));
    }

    double area() const { 
        cerr << "area of " << *this << endl; 
        return pi * a * b; 
    }
    bool operator==(const Shape &another) const;
    bool isCongruentTo(const Shape &another) const;
    bool isSimilarTo(const Shape &another) const;
    bool containsPoint(const Point &point) const;

    Shape & rotate(Point center, double angle);
    Shape & reflex(Point center);
    Shape & reflex(Line axis);
    Shape & scale(Point center, double coefficient);

    friend ostream &operator<<(ostream &stream, const Ellipse &o);
};

class Circle : public Ellipse {
    double r;
    void calc();
public:
    Circle(Point center = Point(0, 0), double radius = 1) :
        r(radius), Ellipse(pair<Point, Point>(center, center), 2*r) {
    }
    ~Circle() {}

    double radius() const { return r; }
    Point center() const { return cent; }

    double perimeter() const {return 2 * pi * r; }
    double area() const { return pi * r * r; }
    
    bool operator==(const Shape &another) const;
    bool isCongruentTo(const Shape &another) const;
    bool isSimilarTo(const Shape &another) const;
    bool containsPoint(const Point &point) const;

    Shape & rotate(Point center, double angle);
    Shape & reflex(Point center);
    Shape & reflex(Line axis);
    Shape & scale(Point center, double coefficient);

    friend ostream &operator<<(ostream &stream, const Circle &o);
};

class Polygon : public Shape {
protected:
    vector<Point> vertices;
public:
    Polygon() {}

    Polygon(vector<Point> points) : vertices(points) {}

    Polygon(const Polygon &another) : vertices(another.vertices) {}

    template<typename... T>
    Polygon(const T&... args) {
        // cerr << "Polygon(const T&... args)" << endl;
        for (auto&& p : std::initializer_list<Point>{args...}) {
            vertices.push_back(p);
            // cerr << p << endl;
        }
    }

    
    ~Polygon() {}

    int verticesCount() const { return vertices.size(); }
    vector<Point> getVertices() const { return vertices; }
    bool isConvex() const;
    Point centroid() const;

    double perimeter() const;
    double area() const;
    bool operator==(const Shape &another) const;
    bool operator!=(const Shape &another) const { return !(*this == another); }
    bool isCongruentTo(const Shape &another) const;
    bool isSimilarTo(const Shape &another) const;
    bool containsPoint(const Point &point) const;

    Shape & rotate(Point center, double angle);
    Shape & reflex(Point center);
    Shape & reflex(Line axis);
    Shape & scale(Point center, double coefficient);
    Shape & move(Point vector);

    Shape & scale1(Point center, double coefficient);
    Shape & move1(Point vector);

    friend ostream &operator<<(ostream &stream, const Polygon &o);
};

class Triangle : public Polygon {
public:
    Triangle(vector<Point> &points) : Polygon(points) {
        // cerr << "Triangle(vector<Point> &points)" << endl;
    }
    Triangle(const Point &p1, const Point &p2, const Point &p3) : Polygon(p1, p2, p3) {
        // cerr << "Triangle(const Point &p1, const Point &p2, const Point &p3)" << endl;
    }
    ~Triangle() {};
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    Point orthocenter() const;
    Line EulerLine() const;
    Circle ninePointsCircle() const;
    
    double area() const;

    friend ostream &operator<<(ostream &stream, const Triangle &o);
};

class Rectangle : public Polygon {
public:
    Rectangle() {}
    Rectangle(Point point1, Point point2, double rel);
    Rectangle(pair<Point, Point> points, double rel) : Rectangle(points.first, points.second, rel) {}
    ~Rectangle() {}
    Point center() const;
    pair<Line, Line> diagonals() const;
    Point centroid() const;

    double perimeter() const;
    double area() const;
    bool operator==(const Shape &another) const;
        
    friend ostream &operator<<(ostream &stream, const Rectangle &o);
};

class Square : public Rectangle
{
public:
    Square(Point point1, Point point2) : Rectangle(point1, point2, 1) {}
    Square(pair<Point, Point> points) : Square(points.first, points.second) {}

    Circle circumscribedCircle() const ;
    Circle inscribedCircle() const ;

    friend ostream &operator<<(ostream &stream, const Square &o);
};


Ellipse::Ellipse(const Point &f1, const Point &f2, double dist) : f1(f1), f2(f2), dist(dist) {
    calc();
}

void Ellipse::calc() {
    cent = Point((f1.x + f2.x) * 0.5, (f1.y + f2.y) * 0.5);

    c = f1.distanceTo(f2) * 0.5;
    //a = dist - c;
    a = dist / 2;
    b = sqrt(a*a - c*c);
    p = b*b / a;
    e = c / a;
}

bool Ellipse::operator==(const Shape &another) const {
    //cerr << "E:op= " << *this << endl;
    if (typeid(another) == typeid(Ellipse)) {
        const Ellipse &e2 = (Ellipse &) another;
        if ((f1 == e2.f1 && f2 == e2.f2 
            || f2 == e2.f1 && f1 == e2.f2) && e == e2.e) {
                return true;
        } 
    } else if (typeid(another) == typeid(Circle)) {
        const Circle &e2 = (Circle &) another;
        if ((f1 == e2.c && f2 == e2.c) && a == e2.radius()) {
            return true;
        }
    }  

    return false;
}

bool Ellipse::isCongruentTo(const Shape &another) const { 
    //cerr << "E:isC " << *this << endl;
    if (typeid(another) == typeid(Ellipse) || typeid(another) == typeid(Circle)) {
        const Ellipse &e2 = (Ellipse &) another;
        if (abs(e2.e - e) < eps && abs(e2.dist - dist) < eps) {
            return true;
        } 
    }
    
    return false; 
}

bool Ellipse::isSimilarTo(const Shape &another) const { 
    cerr << "E:isC " << *this << endl;
    if (typeid(another) == typeid(Ellipse) || typeid(another) == typeid(Circle)) {
        const Ellipse &e2 = (Ellipse &) another;
        if (abs(e2.e - e) < eps) {
            return true;
        } 
    }
    return false;
}

bool Ellipse::containsPoint(const Point &point) const {
    cerr << "E:cP(" << point << endl << *this << endl;
    return f1.distanceTo(point) + f2.distanceTo(point) < dist + eps;
}

Shape & Ellipse::rotate(Point center, double angle) { 
    cerr << "E:rotate " << center << angle <<*this << endl;
    f1.rotate(center, angle);
    f2.rotate(center, angle);
    calc();
    return *this; 
}

Shape & Ellipse::reflex(Point center) { 
    cerr << "E:reflex " << center << *this << endl;
    f1.reflex(center);
    f2.reflex(center);
    calc();
    return *this; 
}

Shape & Ellipse::reflex(Line axis) { 
    cerr << "E:reflexline " << axis << *this << endl;
    f1 = PointLine(f1).reflex(axis);
    f2 = PointLine(f2).reflex(axis);
    calc();
    return *this; 
}

Shape & Ellipse::scale(Point center, double coefficient) { 
    cerr << "E:scale " << center << coefficient << *this << endl;
    f1.scale(center, coefficient);
    f2.scale(center, coefficient);
    dist *= coefficient;
    calc();
    return *this; 
}

void Circle::calc() {
    Ellipse::calc();
    r = r1();
}

bool Circle::operator==(const Shape &another) const {
    cerr << "C:op= " << *this << endl;
    if (typeid(another) == typeid(Ellipse)) {
        const Ellipse &e2 = (Ellipse &) another;
        if (cent == e2.focuses().first && cent == e2.focuses().second 
            && abs(r - e2.r1()) < eps) {
                return true;
        } 
    } else if (typeid(another) == typeid(Circle)) {
        const Circle &e2 = (Circle &) another;
        if (cent == e2.cent && r == e2.r) {
            return true;
        }
    }  

    return false;
}

bool Circle::isCongruentTo(const Shape &another) const { 
    cerr << "C:isC" << endl;
    if (typeid(another) == typeid(Ellipse)) {
        const Ellipse &e2 = (Ellipse &) another;
        if (abs(e2.eccentricity() - e) < eps && abs(r - e2.r1()) < eps) {
            return true;
        } 
    } else if (typeid(another) == typeid(Circle)) {
        const Circle &e2 = (Circle &) another;
        if (abs(r - e2.r) < eps) {
            return true;
        }
    }
    return false;
}

bool Circle::isSimilarTo(const Shape &another) const { 
    cerr << "C:isS" << endl;
    if (typeid(another) == typeid(Ellipse)) {
        const Ellipse &e2 = (Ellipse &) another;
        if (abs(e2.eccentricity() - e) < eps) {
            return true;
        } 
    } else if (typeid(another) == typeid(Circle)) {
        return true;
    }
    return false; 
}

bool Circle::containsPoint(const Point &point) const {
    cerr << "C:cP" << endl;
    return (cent.x - point.x)*(cent.x - point.x) + (cent.y - point.y)*(cent.y - point.y) <= r*r ;
}

Shape & Circle::rotate(Point center, double angle) { 
    cerr << "C:rotate " << center << angle << *this << endl;
    return *this; 
}

Shape & Circle::reflex(Point center) {
    cerr << "C:reflexpoint " << center << *this << endl; 
    f1.reflex(center);
    f2.reflex(center);
    calc();
    return *this; 
}

Shape & Circle::reflex(Line axis) {
    cerr << "C:reflexline " << axis << *this << endl;
    f1 = PointLine(f1).reflex(axis);
    f2 = PointLine(f2).reflex(axis);
    calc();
    return *this; 
}

Shape & Circle::scale(Point center, double coefficient) {
    cerr << "C:scale " << center << coefficient << *this << endl;
    f1.scale(center, coefficient);
    f2.scale(center, coefficient);
    dist *= coefficient;
    calc();
    return *this; 
}

double Polygon::perimeter() const {
    double perimeter = 0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n-1; i++) {
        perimeter += vertices[i].distanceTo(vertices[i+1]);
    }
    perimeter += vertices[n-1].distanceTo(vertices[0]);

    return perimeter;
}

double Polygon::area() const {
    double area = 0;
    Point c = this->centroid();
    size_t n = vertices.size();
    for (size_t i = 0; i < n-1; i++) {
        area += Triangle(c, vertices[i], vertices[i+1]).area();
    }
    area += Triangle(c, vertices[n-1], vertices[0]).area();
    
    return area;
}

bool Polygon::operator==(const Shape &another) const {
    //cerr << "po=" << endl;
    //cerr << *this << endl << (Polygon &) another << endl;

    if (typeid(another) != typeid(*this)) {
        //cerr << "!type -> false" << endl;
        return false;
    }

    Polygon &p = (Polygon &) another;
    if (vertices.size() != p.vertices.size()) {
        //cerr << "!vc -> false" << endl;
        return false;
    }

    double dp = perimeter() - p.perimeter();
    if (dp*dp > eps) {
        //cerr << "!per -> false" << endl;
        return false; 
    }

    double ds = area() - p.area();

    if (ds*ds > eps) {
        //cerr << "!area -> false" << endl;
        return false;
    }

    set<Line> lines1, lines2;
    size_t n = vertices.size();
    for (size_t i = 1; i < n; i++) {
        lines1.insert(Line(vertices[i-1], vertices[i]));
        lines2.insert(Line(p.vertices[i-1], p.vertices[i]));
    }
    lines1.insert(Line(vertices[n-1], vertices[0]));
    lines2.insert(Line(p.vertices[n-1], p.vertices[0]));

    bool found;
    for (auto line1 : lines1) {
        found = false;
        for (auto line2 : lines2) {
            if (line1 == line2) {
                found = true;
                lines2.erase(line2);
                break;
            }
        }
        if (!found) {
            //cerr << "!found -> False" << endl;
            return false;
        }
    }
    //cerr << " -> True" << endl;
    return true;
}

bool Polygon::isCongruentTo(const Shape &another) const {
    //cerr << "P:isC: ";
    // cerr << (const Polygon &) *this << endl;
    if (typeid(another) != typeid(*this)) {
        //cerr << "diff shape -> False" << endl;
        return false;
    }

    Polygon p1(*this), p2((Polygon &) another);
    // cerr << endl << p1 << endl << p2 << endl;

    if (p1.verticesCount() != p2.verticesCount()) {
        //cerr << "diff vcount -> False" << endl;
        return false;
    }
    double s = p1.area() - p2.area();
    if (s*s > eps) {
        //cerr << "diff area -> False" << endl;
        return false;
    }

    Point c1 = p1.centroid();
    Point c2 = p2.centroid();

    size_t n = p1.verticesCount(); 

    vector<Point> v1 = p1.getVertices();
    vector<Point> v2 = p2.getVertices();

    vector<double> a1(n);
    vector<double> a2(n);
    
    Triangle *t;
    for (size_t i = 0; i < n; i++) {
        t = new Triangle(c1, v1[i], v1[(i+1) % n]);
        a1[i] = t->area();
        delete t;

        t = new Triangle(c2, v2[i], v2[(i+1) % n]);
        a2[i] = t->area();
        delete t;
    }

    // for (int i = 0; i < n; i++) {
    //    cerr << a1[i] << " | " << a2[i] << endl;
    // }

    for (size_t i = 0; i < n; i++) {
        bool found = true;
        int g = 0;
        // cerr << "Start g = " << g << endl;
        for (size_t j = 0; j < n; j++) {
            int h = (i + j) % n;
            double s = a1[g] - a2[h];
            if (s*s > eps) {
                // cerr << "(" << g << "," << h << ") -> False: " << s << " " <<  a1[g] << " != " << a2[h] << endl;
                found = false;
                break;
            } else {
                // cerr << "(" << g << "," << h << ") -> True: " << s << " " <<  a1[g] << " == " << a2[h] << endl;
            }
            g++;
        }
        if (found) {
            // cerr << " -> True" << endl;
            return true;
        }

        found = true;
        g = 0;
        // cerr << "Start g = " << g << endl;
        for (size_t j = 0; j < n; j++) {
            int h = (i - j + n) % n;
            double s = a1[g] - a2[h];
            if (s*s > eps) {
                // cerr << "(" << g << ","<< h << ") -> False: " << s << " " <<  a1[g] << " != " << a2[h] << endl;
                found = false;
                break;
            } else {
                // cerr << "(" << g << "," << h << ") -> True: " << s << " " <<  a1[g] << " == " << a2[h] << endl;
            }
            g++;
        }
        if (found) {
            //cerr << " -> True" << endl;
            return true;
        }
    }
    //cerr << "Triangles -> False" << endl;
    return false;
}

bool Polygon::isSimilarTo(const Shape &another) const {
    //cerr << "P:isS: ";
    if (typeid(another) != typeid(*this)) {
        //cerr << "diff type -> False" << endl;
        return false;
    }

    Polygon p1(*this);
    Polygon p2((Polygon &) another);
    if (p1.verticesCount() != p2.verticesCount()) {
        //cerr << "diff vcount -> False" << endl;
        return false;
    }

    // cerr << endl << p1 << endl << p2 << endl;

    double ks = sqrt(p1.area() / p2.area());
    double kp = p1.perimeter() / p2.perimeter();

    if ((ks - kp)*(ks - kp) > eps) {
        //cerr << ks << " != " << kp << " | " << kp - ks << " | " << (abs(ks - kp) > eps) << endl;
        //cerr << "diff k -> False" << endl;
        return false;
    }

    p1.move1(-p1.centroid());
    p2.move1(-p2.centroid());

    p2.scale1(Point(0, 0), kp);

    return p1.isCongruentTo(p2);
}

bool Polygon::containsPoint(const Point &point) const {
    // cerr << "P:cP(" << point << endl << *this << endl;
    vector<Point> v(vertices);

    v.push_back(vertices[0]);

    int prev_p = -1;

    for (size_t i = 0; i < vertices.size(); i++) {
        Point ab = Point(point.x - v[i].x, point.y - v[i].y);
        Point bc = Point(v[i+1].x - point.x, v[i+1].y - point.y);

        bool p = (ab.x * bc.y - ab.y * bc.x) > 0;
        
        if (prev_p == -1) {
            prev_p = p;
        } else if (p != prev_p) {
            return false;
        }
    }
    return true;
}

bool Polygon::isConvex() const {
    vector<Point> v(vertices);

    v.push_back(vertices[0]);
    v.push_back(vertices[1]);

    int prev_p = -1;

    for (size_t i = 1; i <= vertices.size(); i++) {
        Point ab = Point(v[i].x - v[i-1].x, v[i].y - v[i-1].y);
        Point bc = Point(v[i+1].x - v[i].x, v[i+1].y - v[i].y);

        bool p = (ab.x * bc.y - ab.y * bc.x) > 0;
        if (prev_p == -1) {
            prev_p = p;
        } else if (p != prev_p) {
            return false;
        }
    }
    return true;
}

Point Polygon::centroid() const {
    double x = 0, y = 0;
    for (auto p : vertices) {
        x += p.x;
        y += p.y;
    }

    x = x / vertices.size();
    y = y / vertices.size();

    return Point(x, y);
}

Shape & Polygon::rotate(Point center, double angle) {
    //cerr << "rotate(" << center << "," << angle << ") : ";
    //cerr << *this << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].rotate(center, angle);
    }
    // cerr << "->"<<  *this << endl;
    return *this;
}

Shape & Polygon::reflex(Point center) {
    //cerr << "reflex(" << center << ")" << endl;
    //cerr << *this << endl;

    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].reflex(center);
    }
    return *this;
}

Shape & Polygon::move(Point vector) {
    //cerr << "move(" << vector << ")" << endl;
    //cerr << *this << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].move(vector);
    }
    return *this;
}

Shape & Polygon::move1(Point vector) {
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].move(vector);
    }
    return *this;
}

Shape & Polygon::reflex(Line axis) {
    //cerr << "reflex(" << axis << ")" << endl;
    // cerr << *this << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
        PointLine p = vertices[i];
        vertices[i] = p.reflex(axis);
    }
    // cerr << " -> " << *this << endl;
    return *this;
}

Shape & Polygon::scale(Point center, double coefficient) {
    //cerr << "scale(" << center << "," << coefficient << "): ";
    //cerr << *this;
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].scale(center, coefficient);
    }
    //cerr << "->"<<  *this << endl;
    return *this;
}

Shape & Polygon::scale1(Point center, double coefficient) {
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i].scale(center, coefficient);
    }
    return *this;
}

Rectangle::Rectangle(Point point1, Point point2, double r) {
    double angle = 0;
    Point p1, p2;
    p1 = point1;
    p2 = point2;

    if (abs(p1.y - p2.y) > eps) {
        angle = atan2(p2.y - p1.y, p2.x - p1.x) * 180 / pi;
        
        p2.rotate(p1, -angle);
    }

    // cerr << p1 << ", " << p2 << endl;

    // cerr << "angle = " << angle << endl;

    if (p1.x < p2.x) {
        if (r < 1) r = 1/r;
    } else {
        if (r > 1) r = 1/r;
    }

    double c = p1.distanceTo(p2);
    double h = c * r /(1 + r*r);
    double a = h / r;


    Point p3, p4;
    
    if (p1.x < p2.x) {
        p3 = Point(p1.x + a, p1.y + h);
        p4 = Point(p2.x - a, p2.y - h);
    } else {
        p3 = Point(p1.x - a, p1.y + h);
        p4 = Point(p2.x + a, p2.y - h);
    }

    vertices.push_back(p1);
    vertices.push_back(p3.rotate(p1, angle));
    vertices.push_back(p2.rotate(p1, angle));
    vertices.push_back(p4.rotate(p1, angle));

    // cerr << ": " << *this << endl;
}

double Rectangle::perimeter() const { 
    return 2 * (vertices[0].distanceTo(vertices[1]) + vertices[0].distanceTo(vertices[3])); 
}

double Rectangle::area() const { 
    // cerr << " a = " << vertices[0].distanceTo(vertices[1]) << endl;
    // cerr << " b = " << vertices[0].distanceTo(vertices[3]) << endl;
    return (vertices[0].distanceTo(vertices[1]) * vertices[0].distanceTo(vertices[3])); 
}

bool Rectangle::operator==(const Shape &another) const { 
    if (typeid(another) == typeid(Square) 
        || typeid(another) == typeid(Rectangle)
        || typeid(another) == typeid(Polygon)) {
        // cerr << "Check to Square or Polygon" << endl;
        Polygon p1(getVertices());
        Polygon p2(((Polygon &) another).getVertices());
        return p1 == p2;
    }

    return false; 
}

double Triangle::area() const {
    const Point &A = vertices[0], &B = vertices[1], &C = vertices[2];
    // cout << "Calc area" << endl;
    double a = A.distanceTo(B);

    // cout << "A = " << A << " B = " << B << " C = " << C << endl;
    // cout << "AB = " << a << endl;
    // cout << "Cross: " << PointLine(C).projection(Line(A, B)) << endl;
    double h = C.distanceTo(PointLine(C).projection(Line(A, B))); 
    // cout << "h = " << h << endl;
    // cout << endl;
    return 0.5 * a * h;
}

Circle Triangle::circumscribedCircle() const { 
    cerr << "T:circumscribedCircle() " << *this << endl;
    const Point &A = vertices[0], &B = vertices[1], &C = vertices[2];
    double a, b, c;
    
    a = B.distanceTo(C);
    b = C.distanceTo(A);
    c = A.distanceTo(B);

    double R = a*b*c / 4 / area();
    return Circle(orthocenter(), R); 
}

Circle Triangle::inscribedCircle() const { 
    cerr << "T:inscribedCircle() " << *this << endl;
    double r = 2*area() / perimeter();

    const Point &A = vertices[0], &B = vertices[1], &C = vertices[2];
    double a, b, c;
    
    a = B.distanceTo(C);
    b = C.distanceTo(A);
    c = A.distanceTo(B);
    double p = perimeter();

    Point center = A*(a/p) + B*(b/p) + C*(c/p);
    return Circle(center, r);
}

Point Triangle::orthocenter() const { 
    cerr << "T:orthocenter() " << *this << endl;
    Line l1(vertices[0], vertices[1]);
    Line l2(vertices[1], vertices[2]);
    
    Point c1 = (vertices[0] + vertices[1]) * 0.5;
    Point c2 = (vertices[1] + vertices[2]) * 0.5;

    l1 = l1.perpendicular(c1);
    l2 = l2.perpendicular(c2);

    return l2.cross(l1); 
}
Line Triangle::EulerLine() const { 
    cerr << "T:EulerLine() " << *this << endl;
    Line line(orthocenter(), centroid());
    return line; 
}

Circle Triangle::ninePointsCircle() const { 
    cerr << "T:ninePointsCircle() " << *this << endl;
    const Point &A = vertices[0], &B = vertices[1], &C = vertices[2];
    Triangle t(Point((A.x + B.x)*0.5, (A.y + B.y)*0.5),
         Point((B.x + C.x)*0.5, (B.y + C.y)*0.5),
         Point((C.x + A.x)*0.5, (C.y + A.y)*0.5));
    return t.circumscribedCircle(); 
}

ostream &operator<<(ostream &stream, const Point &o) {
    stream << "(" << o.x << "," << o.y << ")";
    return stream;
}

ostream &operator<<(ostream &stream, const Triangle &o) {
    vector<Point> v = o.getVertices();
    stream << "Triangle(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    stream << " | S = " << o.area() << " | P = " << o.perimeter();
    return stream;
}

ostream &operator<<(ostream &stream, Line &o) {
    if (o.is_vertical) {
        stream << "Line x = " << o.x;
    } else {
        stream << "Line y = " << o.k << " * x + " << o.b;
    }
    return stream;
}

ostream &operator<<(ostream &stream, const Line &o) {
    if (o.is_vertical) {
        stream << "Line x = " << o.x;
    } else {
        stream << "Line y = " << o.k << " * x + " << o.b;
    }
    return stream;
}

ostream &operator<<(ostream &stream, const Ellipse &o) {
    stream << "E(" << o.f1 << "," << o.f2 << "," << o.dist << ") e=" << o.e 
    << ", a=" << o.a << ", b=" << o.b << ", c=" << o.c << ", p=" << o.p;
    return stream;
}

ostream &operator<<(ostream &stream, const Circle &o) {
    return stream << "Circle(" << o.cent << ", " << o.radius() << ")";
}

ostream &operator<<(ostream &stream, const Polygon &o) {
    vector<Point> vertices = o.getVertices();
    stream.precision(5);
        
    stream << "P(";
    size_t n = vertices.size();
    if (n == 0) return stream << ")";

    for (size_t i = 0; i < n; i++) {
        stream << vertices[i];
        if (i < n-1) stream << ",";
    } 
    
    stream << ") " << o.area() << " | " << o.perimeter();
    // stream << " | is_convex = " << o.isConvex();
    return stream;
}

ostream &operator<<(ostream &stream, const Rectangle &o) {
    return stream << "R" << ((Polygon &) o);
}

ostream &operator<<(ostream &stream, const Square &o) {
    return stream << "S" << ((Polygon &) o);
}
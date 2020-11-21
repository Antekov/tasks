#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <cmath>

#define DBL_EPSILON 1e-09

using namespace std;

struct Point {
    double x, y, z;
    int id;

    Point(double x=0, double y=0, double z=0, int id=-1) : x(x), y(y), z(z), id(id) {}

    Point(const Point &p) : x(p.x), y(p.y), z(p.z), id(p.id) {}

    bool operator<(const Point &p) const {
        return z < p.z ? (y < p.y ? (x < p.x ? (id < p.id) : false) : false) : false;
    }

    bool operator==(const Point &p) const {
        return id == p.id;
    }

    friend ostream& operator<<(ostream& out, const Point& p) {
        out << "Point "<< p.id << " (" << p.x << ", " << p.y << ", " << p.z << ")";
        return out;
    }
};

struct Vector {
    double x, y, z;

    Vector(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}
    
    Vector(const Point& p1, const Point& p2) :
        x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z)
    {}

    bool operator<(const Vector &p) const {
        return z < p.z ? true : (y < p.y ? true : (x < p.x));
    }

    friend ostream& operator<<(ostream& out, const Vector& p) {
        out << "Vec(" << p.x << ", " << p.y << ", " << p.z << ")";
        return out;
    }

    double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector operator+(const Vector &other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    Vector operator-(const Vector &other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    double operator*(const Vector &v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector operator^(const Vector &v) const {
        return Vector(y*v.z - z*v.y, x*v.z - z*v.x, x*v.y - y*v.x);
    }

    bool isClockwise(const Vector &v) const {
        return x*v.y - y*v.x > 0;
    } 

    double mix(const Vector &a, const Vector &b) {
        return x * (a.y*b.z - a.z*b.y) - y * (a.x*b.z - a.z * b.x) + z * (a.x*b.y - a.y*b.x);
    }    

    double cosPhi(const Vector &a) const {
        if (this->norm() * a.norm() <= DBL_EPSILON) {
            return 1;
        }
        return *this * a / (this->norm() * a.norm());
    }
};

struct Facet {
    Point p1, p2, p3;

    Facet() {}
    Facet(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3) {}

    Vector n() {
        return Vector(p1, p2) ^ Vector(p1, p3);
    }

    double cosPhi(const Vector& v = Vector(0, 0, 1)) {
        return v.cosPhi(this->n()); 
    }

    friend ostream& operator<<(ostream& out, const Facet& f) {
        out << "3 " << f.p1.id << " " << f.p2.id << " " << f.p3.id;
        return out;
    }

    void sort() {
        cerr << "Sort " << *this << endl;
        vector<Point> p(3);
        if (p1.id < p2.id && p1.id < p3.id) {
            cerr << "Var 1" << endl;
            p[0] = p1; p[1] = p2; p[2] = p3;
        } else if (p2.id < p1.id && p2.id < p3.id) {
            cerr << "Var 2" << endl;
            p[0] = p2; p[1] = p1; p[2] = p3;
        } else if (p3.id < p2.id && p3.id < p1.id) {
            cerr << "Var 3" << endl;
            p[0] = p3; p[1] = p2; p[2] = p1;
        } else {
            cerr << "Var -1" << endl;
        }
        
        bool cw = Vector(p1, p2).isClockwise(Vector(p1, p3));
        cerr << "Is cloclwise: " << Vector(p[0], p[1]) << " and " << Vector(p[0], p[2]) << ": " << cw << endl;
        if (cw) {
            std::swap(p[1], p[2]);
        }
        p1 = p[0];
        p2 = p[1];
        p3 = p[2];

        cerr << *this << endl;
    }
};

struct Edge {
    Point p1, p2;

    friend ostream& operator<<(ostream& out, const Edge& e) {
        out << "Edge(" << e.p1 << ", " << e.p2 << ")";
        return out;
    }
};


template <class T>
std::ostream& operator<<(std::ostream &out, vector<T> v) {
    if (v.size() > 0) {
        int i = 0;
        for (auto p : v) { out << "[" << i++ << "] = " <<p << std::endl; }
    } else {
        out << "[]" << std::endl;
    }
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream &out, set<T> v) {
    if (v.size() > 0) {
        int i = 0;
        for (auto p : v) { out << "[" << i++ << "] = " << p << std::endl; }
    } else {
        out << "[]" << std::endl;
    }
    return out;
}



const double INF = 1e99;
static Point nil = {INF, INF, INF, -1};
Point *NIL = &nil;

vector<Facet> solve(vector<Point> &points) {
    int n = points.size();
    vector<Facet> facets;

    vector<Edge> edges;
    vector<Point> S;

    cerr << points << endl;

    sort(points.begin(), points.end());

    cerr << points << endl;
    
    Point &p0 = points[0];
        
    double min_cos = 1;
    int min_i = 0;
    for (int i = 1; i < n; i++) {
        S.push_back(points[i]);
        
        double cur_cos = Vector(p0, points[i]).cosPhi(Vector(p0.x, p0.y, p0.z+1));
        cerr << "Cos(" << points[i] << ") = " << cur_cos << endl; 
        if (cur_cos < min_cos) {
            min_cos = cur_cos;
            min_i = i;
        }
    }
    cerr << "S0: " << endl << S << endl;
    cerr << min_i << endl;

    S.erase(find(S.begin(), S.end(), points[min_i]));

    min_cos = 1;
    int min_j = 0;
    for (int j = 1; j < n; j++) {
        if (j == min_i) continue;

        Facet f(p0, points[min_i], points[j]);

        double cur_cos = Vector(p0, points[j]).cosPhi(Vector(p0.x, p0.y, p0.z+1));
        cerr << "Cos(" << f << ", n=" << f.n() << ") = " << cur_cos << endl; 
        if (cur_cos < min_cos) {
            min_cos = cur_cos;
            min_j = j;
        }
    }

    cerr << min_j << endl;

    S.erase(find(S.begin(), S.end(), points[min_j]));

    facets.insert(facets.begin(), Facet(p0, points[min_i], points[min_j]));
    facets[0].sort();

    cerr << facets[0] << endl;

    edges.push_back({facets[0].p3, facets[0].p1});
    edges.push_back({facets[0].p2, facets[0].p3});
    edges.push_back({facets[0].p1, facets[0].p2});
        

    while (!edges.empty()) {
        Edge e = edges[edges.size() - 1];

        cerr << e << endl;
        Point p1, p2;

        p1 = e.p1;
        p2 = e.p2;

        Vector n = facets.front().n();
        double min_cos = 1;
        Point min_p;
        cerr << "S: " << endl << S << endl;
        for (auto p3 : S) {
            cerr << "p3 = " << p3 << endl;
            Vector Vn = Facet(p3, p2, p1).n();

            double cur_cos = n.cosPhi(Vn);
            if (cur_cos < min_cos) {
                min_cos = cur_cos;
                min_p = p3;
            }
        }

        facets.insert(facets.begin(), Facet(min_p, p2, p1));
        // facets[0].sort();
        cerr << min_p << facets[0] << endl;
        
        cerr << "Need erase from S: " << endl << e.p1 << endl << e.p2 << endl; 
        if (find(S.begin(), S.end(), e.p1) != S.end()) {
            S.erase(find(S.begin(), S.end(), e.p1));
        }
        if (find(S.begin(), S.end(), e.p2) != S.end()) {
            S.erase(find(S.begin(), S.end(), e.p2));
        }
        edges.pop_back();
    }

    

    return facets;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    vector<Point> points(n); // input
    for (int i = 0; i < n; i++) { 
        cin >> points[i].x; cin >> points[i].y; cin >> points[i].z;
        points[i].id = i; 
    }

    vector<Facet> facets = solve(points);

    cout << facets.size() << endl;

    for (int i = 0; i < facets.size(); i++) {
        
        cout << facets[i] << endl;
    }
    cerr << "After sort: " << endl;

    sort(facets.begin(), facets.end(), [](const Facet &a, const Facet &b) {
        return a.p1.id < b.p1.id ? true : (a.p2.id < b.p2.id ? true : a.p3.id < b.p3.id);
    });

    for (int i = 0; i < facets.size(); i++) {
        facets[i].sort();
        cout << facets[i] << endl;
    }

    return 0;
}
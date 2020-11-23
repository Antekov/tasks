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
        out << "Point "<< p.id << " (" << p.x << ", " << p.y << ", " << p.z << ") ";
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
        return Vector(y*v.z - z*v.y, -x*v.z + z*v.x, x*v.y - y*v.x);
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
    Facet(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3) {
        //sort();
    }

    Vector n() {
        return Vector(p1, p2) ^ Vector(p2, p3);
    }

    bool operator==(const Facet &e) const {
        set<int> s;
        s.insert(p1.id);
        s.insert(p2.id);
        s.insert(p3.id);
        s.erase(e.p1.id);
        s.erase(e.p2.id);
        s.erase(e.p3.id);
        return s.empty();
    }

    double cosPhi(const Vector& v = Vector(0, 0, 1)) {
        return v.cosPhi(this->n()); 
    }

    friend ostream& operator<<(ostream& out, const Facet& f) {
        out << "3 " << f.p1.id << " " << f.p2.id << " " << f.p3.id << " ";
        return out;
    }

    void sort(const Point &center) {
        //cerr << "Sort " << *this << endl;
        //cerr << p1 << p2 << p3 << endl;
    
        //cerr << "n = " << n() << endl;

        vector<Point> p = {p1, p2, p3};
        Vector g = Vector(center, p1) + Vector(center, p2) + Vector(center, p3);

        auto min_id = (*min_element(p.begin(), p.end(), [](const Point& a, const Point& b) { return a.id < b.id; })).id;

        int i = 0;
        for (; i < p.size() && p[i].id != min_id; i++) {
            Vector a = Vector(p[i], p[(i+1) % 3]);
            Vector b = Vector(p[(i+1) % 3], p[(i+2) % 3]);
            Vector c = Vector(p[i], p[(i+2) % 3]);
            //cerr << i + 1 << ": " << a << "^ " << b << " = " << (a ^ b) << endl;
        }

        //cerr << "Started from min:" << endl; 
        //cerr << p[i] << p[(i+1) % 3] << p[(i+2) % 3] << endl;

        Vector a = Vector(p[i], p[(i+1) % 3]);
        Vector b = Vector(p[(i+1) % 3], p[(i+2) % 3]);
        Vector c = Vector(p[i], p[(i+2) % 3]);

        ////cerr << "AB x BC" << ": " << a << "^ " << b << " = " << (a ^ b) << endl;
        ////cerr << "AB x AC" << ": " << a << "^ " << c << " = " << (a ^ c) << endl;

        bool cw = a.isClockwise(b);
        double cphi = n().cosPhi(g);

        //cerr << "Is cloclwise: " << cw << endl;
        //cerr << "Cos Phi: " << cphi << endl;

        if (cw == 0 && cphi < 0) {
            //cerr << "Var 1, swap" << endl;
            std::swap(p[(i+1) % 3], p[(i+2) % 3]);
        }

        if (cw == 0 && cphi > 0) {
            //cerr << "Var 2, not swap" << endl;
            //std::swap(p[(i+1) % 3], p[(i+2) % 3]);
        }

        if (cw == 1 && cphi < 0) {
            //cerr << "Var 3, swap" << endl;
            std::swap(p[(i+1) % 3], p[(i+2) % 3]);
        } 

        if (cw == 1 && cphi > 0) {
            //cerr << "Var 4, swap" << endl;
            //std::swap(p[(i+1) % 3], p[(i+2) % 3]);
        }

        a = Vector(p[i], p[(i+1) % 3]);
        b = Vector(p[(i+1) % 3], p[(i+2) % 3]);

        //cerr << "After try swap:" << endl; 
        //cerr << p[i] << p[(i+1) % 3] << p[(i+2) % 3] << endl;

        p1 = p[i];
        p2 = p[(i+1) % 3];
        p3 = p[(i+2) % 3];

        cw = a.isClockwise(b);
        cphi = n().cosPhi(g);

        //cerr << "Is cloclwise: " << cw << endl;
        //cerr << "Cos Phi: " << cphi << endl;  

        


        
        
        ////cerr << *this << endl;
    }
};

struct Edge {
    Point p1, p2, p3;

    Edge() = default;
    Edge(const Point &p1, const Point &p2, const Point &p3) : p1(p1), p2(p2), p3(p3) {}

    bool operator==(const Edge &e) const {
        set<int> s;
        s.insert(p1.id);
        s.insert(p2.id);
        s.erase(e.p1.id);
        s.erase(e.p2.id);
        return s.empty() && p3.id == e.p3.id;
    }

    friend ostream& operator<<(ostream& out, const Edge& e) {
        out << "Edge(" << e.p1.id << ", " << e.p2.id << " : " << e.p3.id << ") ";
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

vector<Facet> solve(vector<Point> &points) {
    int n = points.size();
    double cx = 0, cy = 0, cz = 0;

    for (auto p : points) {
        cx += p.x;
        cy += p.y;
        cz += p.z;
    }

    Point center(cx / n, cy / n, cz / n);
    //cerr << "Center: " << center << endl;

    vector<Facet> facets;

    vector<Edge> edges;
    vector<Point> S;

    ////cerr << points << endl;

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return (a.z < b.z ? true : false);
    });

    ////cerr << points << endl;
    
    Point &p0 = points[0];
    S.push_back(points[0]);
        
    double min_cos = 1;
    int min_i = 0;
    for (int i = 1; i < n; i++) {
        S.push_back(points[i]);
        
        double cur_cos = Vector(p0, points[i]).cosPhi(Vector(0, 0, 1));
        ////cerr << "Cos(" << points[i] << ") = " << cur_cos << endl; 
        if (cur_cos < min_cos) {
            min_cos = cur_cos;
            min_i = i;
        }
    }
    ////cerr << "S0: " << endl << S << endl;
    ////cerr << min_i << endl;

    
    min_cos = 1;
    int min_j = 0;
    for (int j = 1; j < n; j++) {
        if (j == min_i) continue;

        Facet f(p0, points[min_i], points[j]);

        double cur_cos = Vector(p0, points[j]).cosPhi(Vector(0, 0, 1));
        ////cerr << "Cos(" << f << ", n=" << f.n() << ") = " << cur_cos << endl; 
        if (cur_cos < min_cos) {
            min_cos = cur_cos;
            min_j = j;
        }
    }

    ////cerr << min_j << endl;

    facets.insert(facets.begin(), Facet(p0, points[min_i], points[min_j]));
    
    ////cerr << facets[0] << endl;

    edges.push_back({facets[0].p3, facets[0].p1, facets[0].p2});
    edges.push_back({facets[0].p2, facets[0].p3, facets[0].p1});
    edges.push_back({facets[0].p1, facets[0].p2, facets[0].p3});
        
    bool is_new_edges = true;
    while (is_new_edges && !edges.empty() && !S.empty()) {
        is_new_edges = false;
        ////cerr << "Edges: " << endl;
        ////cerr << edges << endl;

        
        
            Edge e = edges[0];
            Vector n = Facet(e.p1, e.p2, e.p3).n();

            ////cerr << "Last edge: " << e << endl;
            Point p1, p2;

            p1 = e.p1;
            p2 = e.p2;

            
            double min_cos = 1;
            Point min_p;
            ////cerr << "S: " << endl << S << endl;
            for (auto p : S) {
                ////cerr << "p = " << p << endl;
                Vector Vn = Facet(p, p1, p2).n();

                double cur_cos = n.cosPhi(Vn);
                ////cerr << "Cos(" << Vn << ", " << n << ") = " << cur_cos << endl;
                if (cur_cos < min_cos) {
                    min_cos = cur_cos;
                    min_p = p;
                }
            }
            edges.erase(edges.begin());


            if (find(facets.begin(), facets.end(), Facet{min_p, p2, p1}) == facets.end()) {
                facets.insert(facets.begin(), Facet(min_p, p2, p1));
                ////cerr << "Found new Facet: " << min_p << facets[0] << endl;
                if (find(edges.begin(), edges.end(), Edge{min_p, p2, p1}) == edges.end()) {
                    edges.push_back({min_p, p2, p1});
                    is_new_edges = true;
                }

                if (find(edges.begin(), edges.end(), Edge{p1, min_p, p2}) == edges.end()) {
                    edges.push_back({p1, min_p, p2});
                    is_new_edges = true;
                }
            } else {
                ////cerr << "Found old Facet: " << min_p << Facet(min_p, p2, p1) << endl;
                if (find(S.begin(), S.end(), min_p) != S.end()) {
                    //S.erase(find(S.begin(), S.end(), min_p));
                    is_new_edges = true;
                }
            }
            
    }

    for (int i = 0; i < facets.size(); i++) {
        facets[i].sort(center);
    }

    return facets;
}

int main() {
    freopen("input.txt", "r", stdin);
    int t = 1, n;
    cin >> t;
    while (t--) {
        cin >> n;

        vector<Point> points(n); // input
        for (int i = 0; i < n; i++) { 
            cin >> points[i].x; cin >> points[i].y; cin >> points[i].z;
            points[i].id = i; 
        }

        vector<Facet> facets = solve(points);

        cout << facets.size() << endl;

        

        sort(facets.begin(), facets.end(), [](const Facet& a, const Facet& b) {
            return pair<int, int>{a.p1.id, a.p2.id} < pair<int, int>{b.p1.id, b.p2.id};
        });
        ////cerr << "After sort: " << endl;
        for (int i = 0; i < facets.size(); i++) {
            
            cout << facets[i] << endl;
        }
    }


    return 0;
}
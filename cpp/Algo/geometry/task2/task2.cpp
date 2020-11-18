#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

//std::ostringstream message;

struct Point {
    int x = 0, y = 0;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point(const pair<int, int> p) : x(p.first), y(p.second) {}

    double phi(const Point &p) const {
        Point a = (p - *this);
        // if (a.x == 0 && a.y == 0) return 0;
        return atan2(a.y, a.x);
    }

    bool operator<(const Point &p) const {
        return pair<int, int>{y, x} < pair<int, int>{p.y, p.x};
    }
 
    double dist2(const Point &p) const {
        return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
    }

    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    int operator*(const Point &p) const {
        return x * p.y - y * p.x;
    }

    bool is_left_rotate(const Point &b, const Point &c) const {
        const Point &a = *this;
        return (b - a) * (c - b) >= 0;
    }

    friend ostream& operator<<(ostream &out, const Point& p) {
        return out << "(" << p.x << ", " << p.y << ")";
    }

};

template <class T>
ostream& operator<<(ostream &out, vector<T> v) {
    for (auto p : v) { out << p << endl; }
    return out;
}

template <class T>
ostream& operator<<(ostream &out, pair<T, T> v) {
    out << "{" << v.first << ", " << v.second << "}";
    return out;
}

vector<Point> Graham(vector<Point> Q) {
    vector<Point> S;

    //message << "Q: " << endl;
    //message << Q << endl;

    std::sort(Q.begin(), Q.end());

    //message << "After sort by Y-coord:" << endl;
    //message << Q << endl;

    Point p = Q[0];

    std::sort(Q.begin() + 1, Q.end(), [p](Point a, Point b) {
         return pair<double, double>{p.phi(a), p.dist2(a)} 
            < pair<double, double>{p.phi(b), p.dist2(b)}; 
    });

    //message << pair<double, double>{p.phi(Point(2, 0)), p.dist2(Point(2, 0))} << " < ";
    //message << pair<double, double>{p.phi(Point(2, 2)), p.dist2(Point(2, 2))} << endl;

    //message << "After sort by Phi and dist realtive to: " << p << endl;
    //message << Q;

    S.push_back(p);
    S.push_back(Q[1]);

    //message << "Init S:" << endl;
    //message << S << endl;

    for (size_t i = 2; i < Q.size(); i++) {
        //message << "Q[" << i << "] = " << Q[i] << endl;

        Point NextToTop = S[S.size() - 2]; 
        Point Top = S[S.size() - 1];
        
        //message << "Check left for [" << NextToTop << ", " << Top << ", " << Q[i] << "] = " << NextToTop.is_left_rotate(Top, Q[i]) << endl; 

        while (!NextToTop.is_left_rotate(Top, Q[i]) && S.size() > 1) {
            S.pop_back();
            NextToTop = S[S.size() - 2];
            Top = S[S.size() - 1];

            //message << "Pop back from S:" << endl;
            //message << S;
            //message << "Check left for [" << NextToTop << ", " << Top << ", " << Q[i] << "] = " << NextToTop.is_left_rotate(Top, Q[i]) << endl;
        }
        S.push_back(Q[i]);

        //message << "Push to S:" << endl;
        //message << S;

    }

    return S;
}

int main() {
    //freopen("input.txt", "r", stdin);

    int n, x, y;
    double lenght = 0;
    std::set<std::pair<int, int>> points;
    vector<Point> Q;
    vector<Point> S;


    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        points.insert({x, y});
    }

    for (auto p : points) {
        Q.push_back(p);
    }

    if (Q.size() > 1) {

        S = Graham(Q);

        //message << "Result:" << endl;
        //message << S << endl;

        for (int i = 0; i < S.size(); i++) {
            lenght += sqrt(S[i].dist2(S[(i+1) % S.size()])*100);
        } 

        //message << lenght << endl;

        //cerr << message.str() << endl;
    }

    cout << fixed << setprecision(8) << lenght / 10 << endl;
    return 0;
}
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

using namespace std;

struct Point {
    int64_t x = 0, y = 0;
    Point(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}
    Point(const pair<int64_t, int64_t> &p) : x(p.first), y(p.second) {}

    double angle(const Point &p) const {
        Point a = (p - *this);
        return atan2(a.y, a.x);
    }
    
    bool operator<(const Point &p) const {
        return pair<int64_t, int64_t>{y, x} < pair<int64_t, int64_t>{p.y, p.x};
    }
    
    double dist2(const Point &p) const {
        return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
    }
    
    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    
    int64_t operator*(const Point &p) const {
        return x * p.y - y * p.x;
    }
    
    bool is_left_rotate(const Point &b, const Point &c) const {
        const Point &a = *this;
        return (b - a) * (c - b) >= 0;
    }
};

vector<Point> Graham(vector<Point> Q) {
    vector<Point> S;
    sort(Q.begin(), Q.end());
    Point p = Q[0];
    sort(Q.begin() + 1, Q.end(), [p](Point a, Point b) {
         return pair<double, double>{p.angle(a), p.dist2(a)} < pair<double, double>{p.angle(b), p.dist2(b)}; 
    });
    S.push_back(p);
    S.push_back(Q[1]);
    for (size_t i = 2; i < Q.size(); i++) {
        Point NextToTop = S[S.size() - 2];
        Point Top = S[S.size() - 1];
        while (!NextToTop.is_left_rotate(Top, Q[i]) && S.size() > 1) {
            S.pop_back();
            NextToTop = S[S.size() - 2];
            Top = S[S.size() - 1];
        }
        S.push_back(Q[i]);
    }
    return S;
}

class Solution {
public:
    static double solve(vector<Point> &Q) {
        double length = 0;
        
        if (Q.size() > 1) {
            vector<Point> S = Graham(Q);
            for (int i = 0; i < S.size(); i++) {
                length += sqrt(S[i].dist2(S[(i+1) % S.size()])*100);
            }
        }
        return length / 10;
    }
};

int main() {
    int64_t n, x, y;
    double lenght = 0;
    set<pair<int64_t, int64_t>> points;
    vector<Point> Q;
    
    cin >> n;
    for (int64_t i = 0; i < n; i++) {
        cin >> x >> y;
        points.insert({x, y});
    }

    for (auto p : points) {
        Q.push_back(p);
    }
    
    cout << fixed << setprecision(8) << Solution::solve(Q) << endl;
    return 0;
}
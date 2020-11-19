#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
#define DBL_EPSILON 2.2204460492503131e-08
#define INF 1e+49

using namespace std;

struct Point {
    double x = 0, y = 0;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point(const pair<double, double> p) : x(p.first), y(p.second) {}
    double phi(const Point &p) const {
        Point a = (p - *this);
        return atan2(a.y, a.x);
    }
    bool operator<(const Point &p) const {
        return pair<double, double>{x, y} < pair<double, double>{p.x, p.y};
    }
    double dist2(const Point &p) const {
        return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
    }
    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator+(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    double operator*(const Point &p) const {
        return x * p.y - y * p.x;
    }

    friend std::ostream& operator<<(std::ostream &out, const Point &v) {
        out << "(" << v.x << ", " << v.y << ")";
        return out;
    }
    
    bool lessThanByAngle(const Point &p) {
        if (x > 0 && p.x < 0) {
            return true;
        }
        if (x < 0 && p.x > 0) {
            return false;
        }
        
        if (fabs(x) < DBL_EPSILON) {
            if (y > 0) {
                return p.x < 0;
            } else {
                return false;
            }
        }

        double tg1 = y / x;
        double tg2 = p.y / p.x;

        if (fabs(p.x) < DBL_EPSILON) {
            if (p.y > 0) {
                return x > 0;
            } else {
                return fabs(tg1 - tg2) > DBL_EPSILON;
            }
        }

        if (fabs(tg1 - tg2) < DBL_EPSILON) {
            return false;
        }
        return tg1 < tg2;
    }





};


template <class T>
std::ostream& operator<<(std::ostream &out, std::vector<T> v) {
    if (v.size() > 0) {
        int i = 0;
        for (auto p : v) { out << "[" << i++ << "] = " <<p << std::endl; }
    } else {
        out << "[]" << std::endl;
    }
    return out;
}

/*
vector<Point> Graham(vector<Point> Q) {
    vector<Point> S;
    sort(Q.begin(), Q.end());
    Point p = Q[0];
    sort(Q.begin() + 1, Q.end(), [p](Point a, Point b) {
         return pair<double, double>{p.phi(a), p.dist2(a)} < pair<double, double>{p.phi(b), p.dist2(b)}; 
    });
    S.push_back(p);
    S.push_back(Q[1]);
    for (long long i = 2; i < Q.size(); i++) {
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
*/

double getY(Point a, Point b) {
    if (fabs(a.x - b.x) < DBL_EPSILON) {
        if (fabs(a.x) < DBL_EPSILON) {
            return (a.y + b.y) / 2;
        } else {
            return INF;
        }
    }
    if (fabs(a.y - b.y) < DBL_EPSILON) {
        return a.y;
    }
    double k = (b.y - a.y) / (b.x - a.x);
    return a.y - k * a.x;
}

double getX(Point a, Point b) {
    //std::cerr << "getX(" << a << ", " << b << ")" << endl;

    if (fabs(a.x - b.x) < DBL_EPSILON) {
        return a.x;
    }
    if (fabs(a.y - b.y) < DBL_EPSILON) {
        if (fabs(a.y) < DBL_EPSILON && a.x * b.x < 0) {
            return (a.x + b.x) / 2;
        } else {
            return INF;
        }
    }
    double k = (b.y - a.y) / (b.x - a.x);
    double c = a.y - k * a.x;
    return -c / k;
}

bool insideTriangle(Point a, Point b, Point c) {
    //std::cerr << "InsideTriangle: " << a << b << c << endl;
    double yc, ya, yb;
    int count = 0;

    if (a.x * b.x < 0) {
        yc = getY(a, b);
        if (yc >= 0 && min(a.y, b.y) <= yc && yc <= max(a.y, b.y)) {
            count++;
        }
    }

    if (b.x * c.x < 0) {
        ya = getY(b, c);
        if (yc >= 0 && min(b.y, c.y) <= ya && ya <= max(b.y, c.y)) {
            count++;
        }
    }

    if (c.x * a.x < 0) {
        yb = getY(c, a);
        if (yc >= 0 && min(c.y, a.y) <= yb && yb <= max(c.y, a.y)) {
            count++;
        }
    }

    return count == 1;
    
}


int main() {
    //freopen("input.txt", "r", stdin);
    vector<Point> Q;
    long long n;
    double x, y;
    cin >> n;
    for(long long i = 0; i < n; i++) {
        cin >> x >> y;
        Q.push_back({x, y});       
    }

    vector<Point> S;
    long long m;
    double x1, y1;
    cin >> m;
    for(long long j = 0; j < m; j++) {
        cin >> x1 >> y1;
        S.push_back({-x1, -y1});       
    }

    

    sort(Q.begin(), Q.end());

   

    Point p = Q[0];
    sort(Q.begin() + 1, Q.end(), [p](Point a, Point b) {
         return pair<double, double>{p.phi(a), p.dist2(a)} < pair<double, double>{p.phi(b), p.dist2(b)}; 
    });

    //std::cerr << Q << endl;

    
    sort(S.begin(), S.end());
       
    
    Point q;
    q = S[0];
    sort(S.begin() + 1, S.end(), [q](Point a, Point b) {
         return pair<double, double>{q.phi(a), q.dist2(a)} < pair<double, double>{q.phi(b), q.dist2(b)}; 
    });

    //std::cerr << S << endl; 
    

    Q.push_back(Q[0]);
    S.push_back(S[0]);
    vector<Point> ans;
    long long i = 0;
    long long j = 0;

    while(i < Q.size() - 1 && j < S.size() - 1) {
        ans.push_back(Q[i] + S[j]);
        //std::cout << ans[i].x << " " << ans[i].y << endl;
        if ((Q[i + 1] - Q[i]).lessThanByAngle(S[j + 1] - S[j])) {
            i++;
        } else if ((S[j + 1] - S[j]).lessThanByAngle((Q[i + 1] - Q[i]))) {
            j++;
        } else {
            i++;
            j++;
        }
    }

    bool inside = false;

    
    ans.push_back(ans[0]);
    //std::cerr << ans << endl;

    int count = 0;
    double x0 = INF;
    for (int i = 0; i < ans.size() - 1; i++) {
        Point a = ans[i], b = ans[i+1];

        if (a.y * b.y <= 0 && !(x == a.x && 0 == a.y)) {
            x0 = getX(a, b);
            if (x0 > 0 && x0 < INF) {
                //std::cerr << "x[" << i << "] = " << x0 << std::endl;
                count++;
            }
        }
    }

    inside = (count % 2 == 1);




    /*
    ans.push_back(ans[0]);
    int left = 0, right = ans.size() - 1;

    while (right - left > 2) {
        int mid = left + (right - left) / 2;

        double x1, y1, x2, y2, k, b;
        x1 = ans[left].x;
        y1 = ans[left].y;
        x2 = ans[mid].x;
        y2 = ans[mid].y;

        if (fabs(x2 - x1) < DBL_EPSILON) {
            b = -x1;
        } else {
            k = (y2 - y1) / (x2 - x1);
            b = y1 - k * x1;
        }

        if (fabs(b) < DBL_EPSILON) {
            inside = true;
            break;
        }

        if (b < 0) {
            right = mid;
        } else {
            left = mid;
        }
    }

    //std::cerr << left << " " << right << endl;
    */
    if (inside) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    














   
    return 0;
}

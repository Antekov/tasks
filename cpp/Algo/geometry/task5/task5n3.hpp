#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cmath>
#include <iomanip>

namespace n3 {

#define DBL_EPSILON 2.2204460492503131e-010
#define INF 1e+49

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

struct Point2D {
    double x, y;

    Point2D(double x=0, double y=0) : x(x), y(y) {}

    bool operator<(const Point2D &p) const {
        return x < p.x ? true : (y < p.y ? true : false);
    }

    friend std::ostream& operator<<(std::ostream &out, const Point2D &v) {
        out << "(" << v.x << ", " << v.y << ")";
        return out;
    }
};

struct Segment2D {
    Point2D start, end;

    Segment2D(const Point2D &start={0, 0}, const Point2D &end={0, 0}) : start(start), end(end) {
        if (end < start) {
            std::swap(this->start, this->end);
        } 
    }

    friend std::ostream& operator<<(std::ostream &out, const Segment2D &v) {
        out << "Seg(" << v.start << ", " << v.end << ")";
        return out;
    }

    double intersectY1(double px) const {
        double py = INF;
        if (abs(start.x - end.x) <= DBL_EPSILON) {
            py = start.y;
        } else if (px >= start.x && px <= end.x) {
            py = start.y + (end.y - start.y) * (px - start.x) / (end.x - start.x);
        }
        return py;
    }

    Point2D intersectPoint(Segment2D s) const {
        double k1, k2, b1, b2, px = INF, py = INF;
        if (abs(end.x - start.x) <= DBL_EPSILON) {
            px = start.x;
            py = intersectY1(px);
        } else if (abs(s.end.x - s.start.x) <= DBL_EPSILON) {
            px = s.start.x;
            py = s.intersectY1(px);
        } else {
            k1 = (end.y - start.y) / (end.x - start.x);

            k2 = (s.end.y - s.start.y) / (s.end.x - s.start.x);
            b1 = start.y - k1*start.x;
            b2 = s.start.y - k2*s.start.x; 
            std::cerr << k1 << " " << b1 << " " << k2 << " " << b2 << std::endl; 
            std::cerr << "abs(k2 - k1)" << " = " << fabs(k2 - k1) << std::endl; 
            if (fabs(k2 - k1) <= DBL_EPSILON) {
                if (fabs(b1 - b2) <= DBL_EPSILON) {
                    px = std::min(start.x, s.start.x);
                    py = k1 * px + b1;
                } else {
                    px = INF, py = INF;
                }
            } else {
                
                px = (b1 - b2) / (k2 - k1);
                py = k1 * px + b1;
            }
        }
        return Point2D(px, py);
    }

    bool intersectX(const Segment2D &s) const {
        return 
            std::max(start.x, end.x) >= std::min(s.start.x, s.end.x) ||
            std::min(start.x, end.x) >= std::max(s.start.x, s.end.x);
    }

    bool intersectY(const Segment2D &s) const {
        return 
            std::max(start.y, end.y) >= std::min(s.start.y, s.end.y) ||
            std::min(start.y, end.y) >= std::max(s.start.y, s.end.y);
    }

    int product(const Point2D &c) const {
        double r = (end.x - start.x) * (c.y - start.y) - (end.y - start.y) * (c.x - start.x);
	    return abs(r) <= DBL_EPSILON ? 0 : (r > 0 ? 1 : -1);
    }

    bool intersect(const Segment2D &s) const {
        return this->intersectX(s) && this->intersectY(s) 
            && this->product(s.start) * this->product(s.end) <= 0
            && s.product(this->start) * s.product(this->end) <= 0;
    }
};

std::ostringstream message;

std::pair<int, int> solve(const std::vector<std::vector<int>> &seg) {
    int n = seg.size();
    bool found = false;

    int x1, y1, x2, y2;
    
    std::vector<Segment2D> segments;
    Point2D min_point(INF, INF);
    std::map<std::pair<int, int>, std::vector<int>> points;
    std::pair<int, int> numbers{-100000, -100000};

    for (int i = 0; i < n; i++) {
        x1 = seg[i][0];
        y1 = seg[i][1];
        x2 = seg[i][2];
        y2 = seg[i][3];

        if (x2 < x1) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        Point2D p1(x1, y1), p2(x2, y2);
        
        segments.push_back(Segment2D(p1, p2));
    }

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (segments[i].intersect(segments[j])) {
                
                auto point = segments[i].intersectPoint(segments[j]);
                std::cerr << "Found:" << std::endl;
                std::cerr << i+1 << " " << j+1 << std::endl;
                std::cerr << point << std::endl;
                if (point < min_point) {
                    min_point = point;
                    numbers = {i, j};
                }
            }
        }
    }

    //std::cerr << message.str() << std::endl;

    if (found) {
        if (numbers.first < numbers.second) {
            return numbers;
        } else {
           return std::pair<int, int>{numbers.second, numbers.first};
        }
    }
    return numbers;
}
}
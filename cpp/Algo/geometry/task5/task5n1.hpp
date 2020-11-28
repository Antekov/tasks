#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cmath>
#include <iomanip>

namespace n1 {
#define DBL_EPSILON 2.2204460492503131e-09
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
        return x < p.x ? true : false;
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
            std::cerr << "Swap " << end << ' ' << start << std::endl; 
            std::swap(this->start, this->end);
        } 
    }

    friend std::ostream& operator<<(std::ostream &out, const Segment2D &v) {
        out << "Seg(" << v.start << ", " << v.end << ")";
        return out;
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

    double intersectY1(double px) const {
        double py = INF;
        if (abs(start.x - end.x) <= DBL_EPSILON) {
            py = start.y;
        } else if (px >= start.x && px <= end.x) {
            py = start.y + (end.y - start.y) * (px - start.x) / (end.x - start.x);
        }
        return py;
    }

    bool intersectX(const Segment2D &s) const {
        return 
            std::max(start.x, end.x) >= std::min(s.start.x, s.end.x) - DBL_EPSILON ||
            std::min(start.x, end.x) >= std::max(s.start.x, s.end.x) - DBL_EPSILON;
    }

    bool intersectY(const Segment2D &s) const {
        return 
            std::max(start.y, end.y) >= std::min(s.start.y, s.end.y) - DBL_EPSILON ||
            std::min(start.y, end.y) >= std::max(s.start.y, s.end.y) - DBL_EPSILON;
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

    bool intersect1(const Segment2D &s) const {
        Point2D o = this->intersectPoint(s);
        std::cerr << *this << " intersect " << s << " at " << o << std::endl;
        return std::min(this->start.x, this->end.x) <= o.x && o.x <= std::max(this->start.x, this->end.x);
    }
};

std::ostringstream message;

std::pair<int, int> solve(const std::vector<std::vector<int>> &seg) {
    int n = seg.size();
    bool found = false;

    int x1, y1, x2, y2;
    
    std::vector<Segment2D> segments;
    std::vector<int> x;
    std::map<int, std::vector<int>> started;
    std::map<int, std::vector<int>> ended;
    std::pair<int, int> numbers;

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
        x.push_back(x1);
        x.push_back(x2);

        started[x1].push_back(i);
        ended[x2].push_back(i);
        
        segments.push_back(Segment2D(p1, p2));
    }

    std::cerr << "segments: " << std::endl;
    std::cerr << segments << std::endl;

    std::sort(x.begin(), x.end());
    auto last = std::unique(x.begin(), x.end());
    x.erase(last, x.end());

    std::cerr << "x: " << std::endl;
    std::cerr << x << std::endl;

    std::vector<int> intersect;
    
    for (int k = 0; k < x.size(); k++) {
        std::cerr << "k = " << k << std::endl;
        std::cerr << "intersect: " << std::endl;
        std::cerr << intersect << std::endl;

        if (started[x[k]].size() > 0) {
            std::sort(started[x[k]].begin(), started[x[k]].end(), [segments](int i, int j) {
                return segments[i].start.y < segments[j].start.y; 
            });
            std::cerr << "Add segments started at " << x[k] << ": " << std::endl;
            std::cerr << started[x[k]] << std::endl;

            auto iter1 = started[x[k]].begin();
            auto pos = intersect.begin();

            while (iter1 != started[x[k]].end()) {
                std::cerr << "*iter1 = " << *iter1 << std::endl;
                //std::cerr << "*pos = " << *pos << std::endl;
                
                if (pos != intersect.end()) {
                    std::cerr << "y1 >= y2: " << segments[*iter1].start.x << " " << segments[*iter1].start.y << " >=";
                    std::cerr << (segments[*pos].intersectY1(segments[*iter1].start.x)) << ": ";
                    std::cerr << (segments[*iter1].start.y >= segments[*pos].intersectY1(segments[*iter1].start.x)) << std::endl;
                    while (pos != intersect.end() 
                        && segments[*iter1].start.y >= segments[*pos].intersectY1(segments[*iter1].start.x)) {
                        std::cerr << "*pos = " << *pos << std::endl;
                        pos++;
                    }
                }

                auto next = pos != intersect.end() ? pos + 1 : pos;
                auto prev = pos != intersect.begin() ? pos - 1 : intersect.end();

                if (next != intersect.end() && segments[*next].intersect(segments[*iter1])) {
                    std::cerr << "Found next: " << std::endl;
                    numbers = {*next, *iter1};
                    found = true;
                    break;    
                }

                if (prev != intersect.end() && segments[*prev].intersect(segments[*iter1])) {
                    std::cerr << "Found prev: " << std::endl;
                    numbers = {*prev, *iter1};
                    found = true;
                    break;    
                }

                std::cerr << "After adding " << *iter1 << " before ";
                std::cerr << ((pos != intersect.end()) ? (*pos) : -1) << ":" << std::endl;
                if (pos != intersect.end()) {
                    pos = intersect.insert(pos, *iter1);
                    std::cerr << "pos != end()" << std::endl;
                    std::cerr << *pos << std::endl;
                    pos++;
                    std::cerr << *pos << std::endl;
                } else {
                    intersect.push_back(*iter1);
                    std::cerr << "pos == end()" << std::endl;
                    pos = intersect.end();
                }
                
                std::cerr << intersect << std::endl;
                std::cerr << "end = " << !(pos != intersect.end()) << std::endl;
                
                iter1++;
            }
        }

        if (found) break;

        if (ended[x[k]].size() > 0) {
            std::cerr << "Remove segments ended at " << x[k] << ": " << std::endl;
            std::cerr << ended[x[k]] << std::endl;
            for (int i : ended[x[k]]) {
                auto pos = std::find(intersect.begin(), intersect.end(), i);
                int prev_i, next_i;
                if (pos != intersect.begin() && pos+1 != intersect.end()) {
                    prev_i = *(pos - 1);
                    next_i = *(pos + 1);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        std::cerr << "Found 1: " << std::endl;
                        found = true;
                        numbers = {prev_i, next_i};
                        break;
                    }
                } else if (pos == intersect.begin() && pos+1 != intersect.end()) {
                    prev_i = *(pos);
                    next_i = *(pos + 1);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        std::cerr << "Found 2: " << std::endl;
                        found = true;
                        numbers = {prev_i, next_i};
                        break;
                    }

                } else if (pos != intersect.begin() && pos+1 == intersect.end()) {
                    prev_i = *(pos - 1);
                    next_i = *(pos);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        std::cerr << "Found 3: " << std::endl;
                        found = true;
                        numbers = {prev_i, next_i};
                        break;
                    }

                }
                intersect.erase(pos);
            }
        }
        
        if (found) break;
    }

    std::cerr << message.str() << std::endl;

    if (found) {
        if (numbers.first < numbers.second) {
            return numbers;
        } else {
           return {numbers.second, numbers.first};
        }
    }
    return std::pair<int, int>{-100000, -100000};
}
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cmath>
#include <iomanip>

#define DBL_EPSILON 2.2204460492503131e-016
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

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    bool found = false;

    int64_t x1, y1, x2, y2;
    
    std::cin >> n;

    std::vector<Segment2D> segments;
    std::vector<int> x;
    std::map<int, std::vector<int>> started;
    std::map<int, std::vector<int>> ended;
    std::pair<int, int> numbers;

    for (int i = 0; i < n; i++) {
        std::cin >> x1 >> y1;
        std::cin >> x2 >> y2;

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
    std::copy(started[x[0]].begin(), started[x[0]].end(), std::back_inserter(intersect));
    std::sort(intersect.begin(), intersect.end(), [segments](int i, int j) {
        return segments[i].start.y < segments[j].start.y; 
    });
    
    for (int k = 1; k < x.size(); k++) {
        std::cerr << "k = " << k << std::endl;
        std::cerr << "intersect: " << std::endl;
        std::cerr << intersect << std::endl;

        for (int j = 0; j < intersect.size() - 1; j++) {
            if (segments[intersect[j]].intersect(segments[intersect[j + 1]])) {
                std::cerr << "Found: " << std::endl;
                numbers = {intersect[j], intersect[j + 1]};
                found = true;
                break;
            }
        }

        if (started[x[k]].size() > 0) {
            std::sort(started[x[k]].begin(), started[x[k]].end(), [segments](int i, int j) {
                return segments[i].start.y < segments[j].start.y; 
            });
            std::cerr << "Add segments started at " << x[k] << ": " << std::endl;
            std::cerr << started[x[k]] << std::endl;

            auto iter1 = started[x[k]].begin();
            auto iter2 = intersect.begin();

            std::cerr << *iter1 << " " << *iter2 << std::endl;

            while (iter1 != started[x[k]].end()) {
                std::cerr << "*iter1 = " << *iter1 << std::endl;
                while (iter2 != intersect.end() 
                    && segments[*iter1].start.y >= segments[*iter2].intersectY1(segments[*iter1].start.x)) {
                    std::cerr << "*iter2 = " << *iter2 << std::endl;
                    iter2++;
                }
                
                if (iter2 != intersect.end()) {
                    intersect.insert(iter2, *iter1);
                } else {
                    intersect.push_back(*iter1);
                }
                iter1++;
            }
            /*
            std::copy(started[x[k]].begin(), started[x[k]].end(), std::back_inserter(intersect));
            std::sort(intersect.begin(), intersect.end(), [segments](int i, int j) {
                return segments[i].start.y < segments[j].start.y; 
            });
            */
        }

        if (ended[x[k-1]].size() > 0) {
            std::cerr << "Remove segments ended at " << x[k-1] << ": " << std::endl;
            std::cerr << ended[x[k-1]] << std::endl;
            for (int i : ended[x[k-1]]) {
                auto pos = std::find(intersect.begin(), intersect.end(), i);
                int prev_i, next_i;
                if (pos != intersect.begin() && pos != intersect.end()) {
                    prev_i = *(pos - 1);
                    next_i = *(pos + 1);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        std::cerr << "Found: " << std::endl;
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
        std::cout << "YES" << std::endl;
        if (numbers.first < numbers.second) {
            std::cout << numbers.first + 1 << " " << numbers.second + 1 << std::endl;
        } else {
            std::cout << numbers.second + 1<< " " << numbers.first + 1<< std::endl;
        }
    } else {
        std::cout << "NO" << std::endl;
    }


    

    
    
    return 0;
}
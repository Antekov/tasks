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
            //std::cerr << "Swap " << end << ' ' << start << std::endl; 
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
    //freopen("input.txt", "r", stdin);
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

    //std::cerr << "segments: " << std::endl;
    //std::cerr << segments << std::endl;

    std::sort(x.begin(), x.end());
    auto last = std::unique(x.begin(), x.end());
    x.erase(last, x.end());

    //std::cerr << "x: " << std::endl;
    //std::cerr << x << std::endl;

    std::vector<int> intersect;
    
    for (int k = 0; k < x.size(); k++) {
        //std::cerr << "k = " << k << std::endl;
        //std::cerr << "intersect: " << std::endl;
        //std::cerr << intersect << std::endl;

        if (started[x[k]].size() > 0) {
            std::sort(started[x[k]].begin(), started[x[k]].end(), [segments](int i, int j) {
                return segments[i].start.y < segments[j].start.y; 
            });
            //std::cerr << "Add segments started at " << x[k] << ": " << std::endl;
            //std::cerr << started[x[k]] << std::endl;

            auto iter1 = started[x[k]].begin();
            auto pos = intersect.begin();

            while (iter1 != started[x[k]].end()) {
                //std::cerr << "*iter1 = " << *iter1 << std::endl;
                ////std::cerr << "*pos = " << *pos << std::endl;
                
                if (pos != intersect.end()) {
                    //std::cerr << "y1 >= y2: " << segments[*iter1].start.x << " " << segments[*iter1].start.y << " >=";
                    //std::cerr << (segments[*pos].intersectY1(segments[*iter1].start.x)) << ": ";
                    //std::cerr << (segments[*iter1].start.y >= segments[*pos].intersectY1(segments[*iter1].start.x)) << std::endl;
                    while (pos != intersect.end() 
                        && segments[*iter1].start.y >= segments[*pos].intersectY1(segments[*iter1].start.x)) {
                        //std::cerr << "*pos = " << *pos << std::endl;
                        pos++;
                    }
                }

                auto next = pos != intersect.end() ? pos + 1 : pos;
                auto prev = pos != intersect.begin() ? pos - 1 : intersect.end();

                if (next != intersect.end() && segments[*next].intersect(segments[*iter1])) {
                    //std::cerr << "Found next: " << std::endl;
                    numbers = {*next, *iter1};
                    found = true;
                    break;    
                }

                if (prev != intersect.end() && segments[*prev].intersect(segments[*iter1])) {
                    //std::cerr << "Found prev: " << std::endl;
                    numbers = {*prev, *iter1};
                    found = true;
                    break;    
                }

                //std::cerr << "After adding " << *iter1 << " before ";
                //std::cerr << ((pos != intersect.end()) ? (*pos) : -1) << ":" << std::endl;
                if (pos != intersect.end()) {
                    pos = intersect.insert(pos, *iter1);
                    //std::cerr << "pos != end()" << std::endl;
                    //std::cerr << *pos << std::endl;
                    pos++;
                    //std::cerr << *pos << std::endl;
                } else {
                    intersect.push_back(*iter1);
                    //std::cerr << "pos == end()" << std::endl;
                    pos = intersect.end();
                }
                
                //std::cerr << intersect << std::endl;
                //std::cerr << "end = " << !(pos != intersect.end()) << std::endl;
                
                iter1++;
            }
            /*
            std::copy(started[x[k]].begin(), started[x[k]].end(), std::back_inserter(intersect));
            std::sort(intersect.begin(), intersect.end(), [segments](int i, int j) {
                return segments[i].start.y < segments[j].start.y; 
            });
            */
        }

        if (ended[x[k]].size() > 0) {
            //std::cerr << "Remove segments ended at " << x[k] << ": " << std::endl;
            //std::cerr << ended[x[k]] << std::endl;
            for (int i : ended[x[k]]) {
                auto pos = std::find(intersect.begin(), intersect.end(), i);
                int prev_i, next_i;
                if (pos != intersect.begin() && pos+1 != intersect.end()) {
                    prev_i = *(pos - 1);
                    next_i = *(pos + 1);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        //std::cerr << "Found 1: " << std::endl;
                        found = true;
                        numbers = {prev_i, next_i};
                        break;
                    }
                } else if (pos == intersect.begin() && pos+1 != intersect.end()) {
                    prev_i = *(pos);
                    next_i = *(pos + 1);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        //std::cerr << "Found 2: " << std::endl;
                        found = true;
                        numbers = {prev_i, next_i};
                        break;
                    }

                } else if (pos != intersect.begin() && pos+1 == intersect.end()) {
                    prev_i = *(pos - 1);
                    next_i = *(pos);
                    if (segments[prev_i].intersect(segments[next_i])) {
                        //std::cerr << "Found 3: " << std::endl;
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

    //std::cerr << message.str() << std::endl;

    if (found) {
        std::cout << "YES" << std::endl;
        if (numbers.first < numbers.second) {
            std::cout << numbers.first + 1 << " " << numbers.second + 1 << std::endl;
        } else {
            std::cout << numbers.second + 1 << " " << numbers.first + 1<< std::endl;
        }
    } else {
        std::cout << "NO" << std::endl;
    }


    

    
    
    return 0;
}
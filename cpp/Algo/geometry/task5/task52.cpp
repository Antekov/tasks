#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define DBL_EPSILON 2.2204460492503131e-9
 
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
    int id;

    Segment2D(const Point2D &start={0, 0}, const Point2D &end={0, 0}, int id=-1) : start(start), end(end), id(id) {
        if (end < start) {
            //std::cerr << "Swap " << end << ' ' << start << std::endl; 
            std::swap(this->start, this->end);
        } 
    }
    bool operator< (const Segment2D & s) const {
        double x = max (min (start.x, end.x), min (s.start.x, s.end.x));
        return this->getY(x) < s.getY(x) - DBL_EPSILON;
    }

    friend std::ostream& operator<<(std::ostream &out, const Segment2D &v) {
        out << "Seg[" << v.id << "](" << v.start << ", " << v.end << ")";
        return out;
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

    bool intersect1(const Segment2D &s) const {
        return this->intersectX(s) && this->intersectY(s) 
            && this->product(s.start) * this->product(s.end) <= 0
            && s.product(this->start) * s.product(this->end) <= 0;
    }

    bool intersect(const Segment2D &s) const;

    double getY (double x) const {
        if (abs (start.x - end.x) < DBL_EPSILON)  return start.y;
        return start.y + (end.y - start.y) * (x - start.x) / (end.x - start.x);
    }
};

inline bool intersect1d (double l1, double r1, double l2, double r2) {
	if (l1 > r1)  swap (l1, r1);
	if (l2 > r2)  swap (l2, r2);
	return max (l1, l2) <= min (r1, r2) + DBL_EPSILON;
}
 
inline int vec (const Point2D & a, const Point2D & b, const Point2D & c) {
	double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return abs(s)<DBL_EPSILON ? 0 : s>0 ? +1 : -1;
}
 
bool intersect0 (const Segment2D & a, const Segment2D & b) {
	return a.intersectX(b)
		&& intersect1d (a.start.y, a.end.y, b.start.y, b.end.y)
		&& a.product(b.start) * a.product(b.end) <= 0
		&& b.product(a.start) * b.product(a.end) <= 0;
}

bool Segment2D::intersect(const Segment2D &s) const {
        return intersect0(*this, s);
    }

struct event {
    double x;
    int type, id;
 
	event() {}
    event (double x, int type, int id) : x(x), type(type), id(id) {}
 
    bool operator< (const event & e) const {
        if (abs (x - e.x) > DBL_EPSILON)  return x < e.x;
        return type > e.type;
    }

    friend std::ostream &operator<<(std::ostream &out, event &e) {
        out << "e(" << e.x << ", " << e.type << ", " << e.id << ")";
        return out;
    }
};

template <class T>
std::ostream& operator<<(std::ostream &out, std::set<T> v) {

    if (v.size() > 0) {
        int i = 0;
        for (auto p : v) { out << "[" << i++ << "] = " <<p << std::endl; }
    } else {
        out << "{}" << std::endl;
    }
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream &out, std::vector<T> v) {

    if (v.size() > 0) {
        int i = 0;
        for (auto p : v) { out << "[" << i++ << "] = " <<p << std::endl; }
    } else {
        out << "{}" << std::endl;
    }
    return out;
}
 
set<Segment2D> s;
vector < set<Segment2D>::iterator > where;
 
inline set<Segment2D>::iterator prev (set<Segment2D>::iterator it) {
    return it == s.begin() ? s.end() : --it;
}
 
inline set<Segment2D>::iterator next (set<Segment2D>::iterator it) {
    return ++it;
}
 
pair<int, int> solve (const vector<Segment2D> & a) {
    int n = (int) a.size();
    vector<event> e;
    for (int i=0; i<n; ++i) {
        e.push_back (event(std::min(a[i].start.x, a[i].end.x), +1, i));
        e.push_back (event(std::max(a[i].start.x, a[i].end.x), -1, i));
    }
    std::sort(e.begin(), e.end());
 
    s.clear();
    where.resize(a.size());

    //std::cerr << e << std::endl;

    for (size_t i=0; i<e.size(); ++i) {
        //std::cerr << "Event " << i << ": " << e[i] << endl;
        //std::cerr << s << endl;

        int id = e[i].id;
        if (e[i].type == 1) {
            auto nxt = s.lower_bound(a[id]);
            auto prv = prev(nxt);
            //std::cerr << (nxt != s.end() ? (*nxt).id : -1) << " | " << id << endl;

            if (nxt != s.end() && nxt->intersect(a[id])) {
                //std::cerr << "Return 1: " << nxt->id << endl;
                return make_pair (nxt->id, id);
            }
            if (prv != s.end() && prv->intersect(a[id])) {
                //std::cerr << "Return 2" << endl;
                return make_pair (prv->id, id);
            }
            where[id] = s.insert(nxt, a[id]);
        }
        else {
            auto nxt = next (where[id]);
            auto prv = prev (where[id]);
            if (nxt != s.end() && prv != s.end() && nxt->intersect(*prv)) {
                //std::cerr << "Return 3" << endl;
                return make_pair (prv->id, nxt->id);
            }
            s.erase (where[id]);
        }
    }
 
    return make_pair (-100000, -100000);
}

int main() {
    //freopen("input.txt", "r", stdin);
    int n;
    bool found = false;

    int64_t x1, y1, x2, y2;
    
    std::cin >> n;

    std::vector<Segment2D> segments;
    std::pair<int, int> numbers;

    for (int i = 0; i < n; i++) {
        std::cin >> x1 >> y1;
        std::cin >> x2 >> y2;    

        Point2D p1(x1, y1), p2(x2, y2);
        segments.push_back(Segment2D{p1, p2, i});
    }

    numbers = solve(segments);

    if (numbers.first >= -10000) {
        std::cout << "YES" << std::endl;
        if (numbers.first < numbers.second) {
            std::cout << numbers.first + 1 << " " << numbers.second + 1 << std::endl;
        } else {
            std::cout << numbers.second + 1 << " " << numbers.first + 1 << std::endl;
        }
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
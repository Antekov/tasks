#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define DBL_EPSILON 2.2204460492503131e-016
 
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



 
struct seg {
	Point2D p, q;
	int id;
 
	double get_y (double x) const {
		if (abs (p.x - q.x) < DBL_EPSILON)  return p.y;
		return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
	}

	friend std::ostream &operator<<(std::ostream &out, seg &s) {
		out << "seg(" << s.p << ", " << s.q << ")";
		return out;
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
 
bool intersect (const seg & a, const seg & b) {
	return intersect1d (a.p.x, a.q.x, b.p.x, b.q.x)
		&& intersect1d (a.p.y, a.q.y, b.p.y, b.q.y)
		&& vec (a.p, a.q, b.p) * vec (a.p, a.q, b.q) <= 0
		&& vec (b.p, b.q, a.p) * vec (b.p, b.q, a.q) <= 0;
}
 
 
bool operator< (const seg & a, const seg & b) {
	double x = max (min (a.p.x, a.q.x), min (b.p.x, b.q.x));
	return a.get_y(x) < b.get_y(x) - DBL_EPSILON;
}
 
 
struct event {
	double x;
	int tp, id;
 
	event() { }
	event (double x, int tp, int id = -10)
		: x(x), tp(tp), id(id)
	{ }
 
	bool operator< (const event & e) const {
		if (abs (x - e.x) > DBL_EPSILON)  return x < e.x;
		return tp > e.tp;
	}

	friend std::ostream &operator<<(std::ostream &out, event &e) {
		out << "e(" << e.x << ", " << e.tp << ", " << e.id << ")";
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
 
set<seg> s;
vector < set<seg>::iterator > where;
 
inline set<seg>::iterator prev (set<seg>::iterator it) {
	return it == s.begin() ? s.end() : --it;
}
 
inline set<seg>::iterator next (set<seg>::iterator it) {
	return ++it;
}
 
pair<int,int> solve (const vector<seg> & a) {
	int n = (int) a.size();
	vector<event> e;
	for (int i=0; i<n; ++i) {
		e.push_back (event (min (a[i].p.x, a[i].q.x), +1, i));
		e.push_back (event (max (a[i].p.x, a[i].q.x), -1, i));
	}
	sort (e.begin(), e.end());
 
	s.clear();
	where.resize(a.size());

	std::cerr << e << std::endl;

	for (size_t i=0; i<e.size(); ++i) {
		std::cerr << "Event " << i << ": " << e[i] << endl;
		std::cerr << s << endl;

		int id = e[i].id;
		if (e[i].tp == +1) {
			set<seg>::iterator
				nxt = s.lower_bound (a[id]),
				prv = prev (nxt);
			std::cerr << (nxt != s.end() ? (*nxt).id : -1) << " | " << id << endl;
			if (nxt != s.end() && intersect (*nxt, a[id])) {
				std::cerr << "Return 1" << endl;
				return make_pair (nxt->id, id);
			}
			if (prv != s.end() && intersect (*prv, a[id])) {
				std::cerr << "Return 2" << endl;
				return make_pair (prv->id, id);
			}
			where[id] = s.insert (nxt, a[id]);
		}
		else {
			set<seg>::iterator
				nxt = next (where[id]),
				prv = prev (where[id]);
			if (nxt != s.end() && prv != s.end() && intersect (*nxt, *prv)) {
				std::cerr << "Return 3" << endl;
				return make_pair (prv->id, nxt->id);
			}
			s.erase (where[id]);
		}
	}
 
	return make_pair (-100000, -100000);
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    bool found = false;

    int64_t x1, y1, x2, y2;
    
    std::cin >> n;

    std::vector<seg> segments;
    std::pair<int, int> numbers;

    for (int i = 0; i < n; i++) {
        std::cin >> x1 >> y1;
        std::cin >> x2 >> y2;

        if (x2 < x1) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        Point2D p1(x1, y1), p2(x2, y2);
        segments.push_back(seg{p1, p2, i});
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
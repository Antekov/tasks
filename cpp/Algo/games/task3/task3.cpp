// https://www.e-olymp.com/ru/submissions/8059053
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int mex(const std::set<int> &s) {
    int ans = 0;

    while (s.count(ans) > 0) {
        ans++;
    }
    return ans;
}

template <class T>
std::ostream& operator<<(std::ostream &out, std::vector<T> v) {
    for (auto p : v) { out << p << "\n"; }
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream &out, std::set<T> v) {
    if (v.size() > 0) {
        int i = 0;
        out << '{';
        for (auto p : v) { out << p << ", "; }
        out << '}';
    } else {
        out << "{}" << std::endl;
    }
    return out;
}

class Solution {
public:
    std::vector<int> solve(int n) {
        std::vector<int> g(std::max(4, n+1), 0);
        std::vector<int> ans;
        std::set<int> s;
        std::vector<int> start;

        g[0] = mex({});
        g[1] = mex({});

        for (size_t k = 2; k <= n; k++) {
            s.clear();

            for (size_t i = 1; i <= k; i++) {
                int x = g[i-1] ^ g[k-i];
                s.insert(x);
                if (k == n && x == 0) {
                    ans.push_back(i);
                }
            }
            
            g[k] = mex(s);
            // std::cerr << k << ": " << s << " | g[k] = " << g[k] << std::endl;
        }

        std::sort(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    int n = 7;
    std::cin >> n;
    
    std::vector<int> ans;

    for (int i = n; i <= n; i++) {
        // std::cerr << "Solve n = " << i << std::endl;
        Solution solution;
        ans = solution.solve(i);
        if (ans.size() > 0) {
            std::cout << "Schtirlitz" << std::endl;
            std::cout << ans;
        } else {
            std::cout << "Mueller" << std::endl;
        }
    }
    return 0;
}
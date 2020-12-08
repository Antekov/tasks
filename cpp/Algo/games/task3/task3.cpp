#include <iostream>
#include <vector>
#include <set>

int mex(std::set<int> &s) {
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
        std::vector<int> p(std::max(4, n+1), 0);
        std::vector<int> ans;
        std::set<int> s;
        std::vector<int> start;

        g[0] = 0;
        g[1] = 1;
        g[2] = 2;
        g[3] = 3;

        for (size_t k = 4; k <= n; k++) {
            s.clear();
            s.insert(g[k-1]);
            s.insert(g[k-2]);

            for (size_t i = 3; i <= k-2; i++) {
                s.insert(g[i-1] ^ g[k-i]);
            }
            
            g[k] = mex(s);
            std::cerr << k << ": " << s << " | g[k] = " << g[k] << std::endl;
        }

        int goal = g[n];
        int bit = 0;

        while (goal > 0) {
            bit++;
            goal /= 2;
        }

        bit = 1 << bit;

        for (size_t i = 1; i <= n; i++) {
            if ((i & bit) == 1) {
                ans.push_back(i);
            }
            
        }

        return ans;
        

        p[0] = 1;
        p[1] = 0;
        p[2] = 0;
        p[3] = 2;

        for (size_t k = 4; k <= n; k++) {
            s.clear();

            s.insert(p[k-1]);
            s.insert(p[k-2]);

            for (size_t i = 3; i <= k-2; i++) {
                s.insert(p[i-1] ^ p[k-i]);
            }
            
            p[k] = mex(s);
            std::cerr << k << ": " << s << " | p[k] = " << p[k] << std::endl;
        }
        
        return ans;

        if (g[n] > 0) {
            //std::cout << "Schtirlitz" << std::endl;
            if (n == 1) {
                ans.push_back(1);
            } else if (n == 2) {
                ans.push_back(1);
                ans.push_back(2);
            } else if (n == 3) {
                ans.push_back(2);
            } else if (n > 3) {
                if (g[n - 1] == 0) {
                    ans.push_back(1);
                }

                if (g[n - 2] == 0) {
                    ans.push_back(2);
                }

                for (size_t k = 3; k <= n - 2; k++) {

                    if (g[k - 1] > 0 && g[n - k] > 0 
                    ) {
                        if (p[k-1] == 0 && p[n-k] == 0) {
                            ans.push_back(k);
                        }
                    }
                }

                if (g[n - 2] == 0) {
                    ans.push_back(n - 1);
                }

                if (g[n - 1] == 0) {
                    ans.push_back(n);
                }
            }
        }
        return ans;
    }
};

int main() {
    int n = 5;
    //std::cin >> n;
    Solution solution;
    std::vector<int> ans;

    for (int i = n; i <= n; i++) {
        
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
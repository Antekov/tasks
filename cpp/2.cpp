#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Edge 
{
    int first, second, value;
};

void print(vector<int> &a) {
    for (auto x : a) {
        // cout << x << ' ';
    }
    // cout << endl;
}

int main() {
    int n, m, k, s, f;

    int INF = 2000000000;

    cin >> n >> m >> k >> s >> f;

    vector<Edge> e(m);

    for (int i = 0; i < m; i++) {
        cin >> e[i].first >> e[i].second >> e[i].value;
    }

    vector<int> d(n+1);
    vector<int> c(n+1);

    for (int i = 0; i <= n; i++) {
        d[i] = INF;
        c[i] = 0;
    }

    d[s] = 0;
    c[s] = 1;

    // print(d);
    for (int i = 0; i < k; i++) {
        // cout << "i = " << i << endl;
        vector<int> pass;
        for (int j = 0; j < m; j++) {
            // cout << "j = " << j << endl;
            // print(d);
            if (c[e[j].first] > 0) {
                if (d[e[j].second] > d[e[j].first] + e[j].value) {
                    d[e[j].second] = d[e[j].first] + e[j].value;
                    pass.push_back(e[j].second);
                    
                }
            }
        }
        for (auto p : pass) {
            c[p] = 1;
        }
        // cout << "New values:" << endl;
        // print(d);
        // print(c);
    }

    if (d[f] == INF) {
        cout << -1;
    } else {
        cout << d[f];
    }
    return 0;
}
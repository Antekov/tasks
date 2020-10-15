#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <stdio.h>

using namespace std;

vector<pair<int, int>> p;
map<pair<int, int>, int> f;
vector<vector<int>> g;

void find_path(map<pair<int, int>, int> &cf, int n, int s, int t) {
    vector<int> path(n, -1);

    queue<int> q;
    vector<bool> visited;
    visited.assign(n, false);
    q.push(s);
    visited[s] = true;

    
    // vector<vector<int>> g(n);
    /*
    int i = 0;
    cout << "Before:" << endl;
    for (auto v1 : g) {
        cout << ++i << ": ";
        for (auto v2 : v1) {
            cout << v2+1 << " ";
        }
        cout << endl;
    }
    
    g.assign(n, vector<int>(0));


    for (auto edge : cf) {
        int u, v, w;
        u = edge.first.first;
        v = edge.first.second;
        w = edge.second;
        if (w > 0) {
            g[u].push_back(v);
        }
    }
    
    cout << "After: " << endl;
    i = 0;
    for (auto v1 : g) {
        cout << ++i << ": ";
        for (auto v2 : v1) {
            cout << v2+1 << " ";
        }
        cout << endl;
    }
    */

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : g[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
                path[v] = u;

                if (v == t) {
                    break;
                }
            }

            /*
            cout << "Path: " << endl;
            for (int i = 1; i <= n; i++) {
                cout << i << " ";
            }
            cout << endl;

            for (auto el : path) {

                cout << el+1 << " ";
            }
            cout << endl;
            */
            
            if (path[t] != -1) {
                break;
            }
        }
    }
    
    p.clear();
    
    if (path[t] == -1) return;

    int vertex = t;
    
    while (vertex != s) {
        assert(path[vertex] != vertex);

        p.insert(p.begin(), {path[vertex], vertex});
        vertex = path[vertex];
    }

    /*
    for (auto v : p) {
        cout << v.first+1 << "-" << v.second+1 << endl;
    }
    */
}

map<pair<int, int>, int> ford_falc(map<pair<int, int>, int> &c, int n, int s, int t) {
    map<pair<int, int>, int> cf;

    for(auto edge : c) {
        f[edge.first] = 0;
        f[{edge.first.second, edge.first.first}] = 0;
        cf[edge.first] = edge.second;
    }

    g.assign(n, vector<int>(0));
    
    for (auto edge : cf) {
        int u, v, w;
        u = edge.first.first;
        v = edge.first.second;
        w = edge.second;
        if (w > 0) {
            g[u].push_back(v);
        }
    }
    
    
    /*
    cout << "find_path()" << endl;

    for(auto edge : cf) {
        cout << "c(" << edge.first.first + 1 << "," << edge.first.second +1 << ") = " << cf[edge.first] << endl;
    }
    */
    find_path(cf, n, s, t);
    int count = 0;
    while (p.size() > 0) {
        int min_cf = -1;
        for (auto edge : p) {
            if (cf[edge] < min_cf || min_cf == -1) {
                min_cf = cf[edge];
            }
        }

        for (auto edge : p) {
            pair<int, int> rev_edge = {edge.second, edge.first};
            f[edge] = f[edge] + min_cf;
            f[rev_edge] = f[rev_edge] - min_cf;
        }

        for (auto edge : p) {
            pair<int, int> rev_edge = {edge.second, edge.first};

            int old_cf = cf[edge], old_cf_rev = cf[rev_edge];

            cf[edge] = cf[edge] - f[edge];
            cf[rev_edge] = cf[rev_edge] - f[rev_edge];

            
            if (cf[edge] == 0) {
                g[edge.first].erase(find(g[edge.first].begin(), g[edge.first].end(), edge.second));
            } else if (old_cf == 0) {
                g[edge.first].push_back(edge.second);
            }

            if (cf[rev_edge] == 0) {
                auto it = find(g[rev_edge.first].begin(), g[rev_edge.first].end(), rev_edge.second);
                if (it != g[rev_edge.first].end()) {
                    g[rev_edge.first].erase(it);
                }
            } else if (old_cf_rev == 0) {
                g[rev_edge.first].push_back(rev_edge.second);
            }
    
        }

        /*
        cout << "find_path()" << endl;

        for(auto edge : cf) {
           cout << "c(" << edge.first.first + 1 << "," << edge.first.second +1 << ") = " << cf[edge.first] << endl;
        }
        */
        find_path(cf, n, s, t);
    }

    return f;
}


int main() {
    int n, m, s, t;
    
    cin >> n >> m >> s >> t;

    s--;
    t--;

    map<pair<int, int>, int> edges;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;

        if (x == y) continue;

        x--;
        y--;

        if (edges.count({x, y}) == 0) {
            edges[{x, y}] = 1;
        } else {
            edges[{x, y}] += 1;
        }
    }

    ford_falc(edges, n, s, t);

    int t1 = -1, t2 = -1;

    for (auto edge : f) {
        // cout << edge.first.first + 1<< " " << edge.first.second + 1 << " : " << edge.second << endl;
        if (edge.first.second == t)
            if (edge.second > 1) {
                t1 = edge.first.first;
                t2 = edge.first.first;
                break;
            } else if (edge.second == 1) {
                if (t1 == -1) {
                    t1 = edge.first.first; 
                } else {
                    t2 = edge.first.first;
                    break;
                }
        }
    }

    if (t1 != -1 && t2 != -1) {
        cout << "YES" << endl;
        vector<int> p1, p2;
        int vertex;

        p1.push_back(t);
        vertex = t1;

        while (vertex != s) {
            p1.push_back(vertex);
            for (auto edge : f) {
                if (edge.first.second == vertex && edge.second >= 1) {
                    vertex = edge.first.first;
                    break;
                }
            }
        }
        p1.push_back(s);

        p2.push_back(t);
        vertex = t2;
        
        while (vertex != s) {
            p2.push_back(vertex);
            for (auto edge : f) {
                if (edge.first.second == vertex && edge.second >= 1) {
                    vertex = edge.first.first;
                    break;
                }
            }
        }
        p2.push_back(s);

        for (int i = p1.size() - 1; i >=0; i--) {
            cout << p1[i]+1 << ' ';
        }
        cout << endl;

        for (int i = p2.size() - 1; i >=0; i--) {
            cout << p2[i]+1 << ' ';
        }
        cout << endl;

    } else {
        cout << "NO" << endl;
    }

    return 0;
}
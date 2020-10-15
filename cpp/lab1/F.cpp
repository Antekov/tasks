#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int>> find_path(map<pair<int, int>, int> &cf, int n, int s, int t) {
    vector<int> path(n, -1);

    queue<int> q;
    vector<bool> visited;
    visited.assign(n, false);
    q.push(s);
    visited[s] = true;

    vector<vector<int>> g(n);

    for (auto edge : cf) {
        int u, v, w;
        u = edge.first.first;
        v = edge.first.second;
        w = edge.second;
        if (w > 0) {
            g[u].push_back(v);
        }
    }

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

    vector<pair<int, int>> p;

    if (path[t] == -1) return p;

    int vertex = t;

    while (vertex != s) {
        p.insert(p.begin(), {path[vertex], vertex});
        vertex = path[vertex];
    }

    /*
    for (auto v : p) {
        cout << v.first+1 << "-" << v.second+1 << endl;
    }
    */
    return p;
}

map<pair<int, int>, int> ford_falc(map<pair<int, int>, int> &c, int n, int s, int t) {
    map<pair<int, int>, int> f;
    map<pair<int, int>, int> cf;

    for(auto edge : c) {
        f[edge.first] = 0;
        f[{edge.first.second, edge.first.first}] = 0;
        cf[edge.first] = edge.second;
    }

    /*
    cout << "find_path()" << endl;

    for(auto edge : cf) {
        cout << "c(" << edge.first.first + 1 << "," << edge.first.second +1 << ") = " << cf[edge.first] << endl;
    }
    */
    vector<pair<int, int>> p = find_path(cf, n, s, t);

    while (p.size() > 0) {
        int min_cf = -1;
        for (auto edge : p) {
            if (cf[edge] < min_cf || min_cf == -1) {
                min_cf = cf[edge];
            }
        }

        for (auto edge : p) {
            f[edge] = f[edge] + min_cf;
            f[{edge.second, edge.first}] = f[{edge.second, edge.first}] - min_cf;
        }

        for (auto edge : p) {
            cf[edge] = cf[edge] - f[edge];
            cf[{edge.second, edge.first}] = cf[{edge.second, edge.first}] - f[{edge.second, edge.first}];
        }

        /*
        cout << "find_path()" << endl;

        for(auto edge : cf) {
           cout << "c(" << edge.first.first + 1 << "," << edge.first.second +1 << ") = " << cf[edge.first] << endl;
        }
        */
        p = find_path(cf, n, s, t);
    }

    return f;
}

int main() {
    int n, s, t;
    
    cin >> n;

    map<pair<int, int>, int> edges;

    for (int i = 0; i < n; i++) {
        char c;
        for (int j = 0; j < n; j++) {
            cin >> c;
            if (c == '1' && i != j) {
                if (edges.count({i, j}) == 0) {
                    edges[{i, j}] = 1;
                } else {
                    edges[{i, j}] += 1;
                }
            }
        }
    }


    for (int s = 0; s < n-1; s++) {
        for (int t = s+1; t < n; t++) {
            cout << s+1 << " -> " << t+1 << endl;
            map<pair<int, int>, int> f = ford_falc(edges, n, s, t);

            
            int t1 = -1, t2 = -1;

            for (auto edge : f) {
                cout << edge.first.first + 1<< " " << edge.first.second + 1 << " : " << edge.second << endl;
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

            
        }
    }


    return 0;
}
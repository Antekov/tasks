#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> deik(map<int, map<int, int>> edges, vector<int> &d, int n, int m, int x) {
    
    vector<vector<pair<int, int>>> t(n);
    set<int> inf_d;
    
    const int INF = 200000000;
    
    for (int i = 0; i < n; i++)
    {
        d[i] = INF;
        inf_d.insert(i);
    }

    d[x] = 0;
    inf_d.erase(x);

    set<int> vertexes, next_vertexes;

    vertexes.insert(x);

    for (long long i = 0; i < n; i++) {
        bool is_changed = false;

        next_vertexes.clear();

        for (auto start : vertexes)
        {
            //cout << "Handle start = " << start << endl;
            for (auto end: edges[start]) {
                if (d[end.first] > d[start] + end.second) {
                    d[end.first] = d[start] + end.second;

                    t[end.first] = t[start];
                    t[end.first].push_back({start, end.first});
                    
                    inf_d.erase(end.first);
                    is_changed = true;
                }

                //cout << "Add (z+1) % M = "<< (start + 1) << " % M = " << end.first << " to next" << endl;
                next_vertexes.insert(end.first);
            }

            //cout << "Count of Inf d: " << inf_d.size() << endl;
            //cout << "Is changed: " << is_changed << endl;
            if (inf_d.size() == 0 && !is_changed) {
                break;        
            }
        }

        if (inf_d.size() == 0 && !is_changed) {
            break;        
        }

        vertexes = next_vertexes;
    }

    return t;
}

int main() {
    int n, m, s, t;
    
    cin >> n >> m >> s >> t;

    s--;
    t--;

    map<int, map<int, int>> edges;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;

        edges[x-1].insert({y-1, 1});
    }
    
    vector<int> d(n);
    vector<vector<pair<int, int>>> D = deik(edges, d, n, m, s);
    
    set<pair<int, int>> T;

    int i = 0;
    for (auto path: D) {
        //cout << "Path from " << s << " to " << i+1 << endl;
        if (D[i].size() > 0) {
            for (auto e : D[i]) {
                //cout << e.first+1 << " " << e.second+1 << endl;
                T.insert(e);
            }
        } else {
            //cout << "[]" << endl;
        }
        i++;
    }

    vector<pair<int, int>> P1;
   
    for (auto e : D[t]) {
        P1.push_back(e);
    }

    for (auto e : edges) {
        int u = e.first;

        for (auto vertex : e.second) {
            int v = vertex.first;
            int w = vertex.second;

            edges[u][v] = w - d[v] + d[u];

            //cout << "u = " << u + 1 << " | v = " << v + 1 << " | w = " << edges[u][v] << endl;
        }
        
    }

    map<int, map<int, int>> edges1;

    for (auto e : edges) {
        int u = e.first;

        for (auto vertex : e.second) {
            int v = vertex.first;
            int w = vertex.second;
            
            if (v != s) {
                if (count(P1.begin(), P1.end(), pair{u, v}) == 0) {
                    edges1[v][u] = w;
                } else {
                    edges1[u][v] = w;
                }
            }
            
        }
        
    }

    for (auto e : edges1) {
        int u = e.first;

        for (auto vertex : e.second) {
            int v = vertex.first;
            int w = vertex.second;

            //cout << "u = " << u + 1 << " | v = " << v + 1 << " | w = " << w << endl;
        }
        
    }

    vector<vector<pair<int, int>>> D1 = deik(edges1, d, n, m, s);

    vector<pair<int, int>> P2;
    //cout << "P2" << endl;
    for (auto e : D1[t]) {
        P2.push_back(e);
        //cout << e.first << " " << e.second << endl;
    }

    set<pair<int, int>> P3;

    for (auto e : P1) {
        int u = e.first;
        int v = e.second;

        if (count(P2.begin(), P2.end(), pair{v, u}) == 0) {
            P3.insert(e);
        }
    }

    for (auto e : P2) {
        int u = e.first;
        int v = e.second;

        if (P1.count({v, u}) == 0) {
            P3.insert(e);
        }
    }

    int s1 = -1, s2 = -1;

    //cout << "P3" << endl;
    for (auto e : P3) {
        //cout << e.first << " " << e.second << endl;
        if (e.first == s) {
            if (s1 == -1) {
                s1 = e.second;
            } else {
                s2 = e.second;
                break;
            }
        }
    }


    //cout << s1 << ", " << s2 << endl;

    if (s1 != -1 && s2 != -1) {

        vector<int> path1, path2;

        path1.push_back(s);
        path1.push_back(s1);

        path2.push_back(s);
        path2.push_back(s2);

        int v = s1;
        while (v != t) {
            for (auto e : P3) {
                if (e.first == v) {
                    v = e.second;
                    path1.push_back(v);
                    break;
                }
            }
        }

        v = s2;
        while (v != t) {
            for (auto e : P3) {
                if (e.first == v) {
                    v = e.second;
                    path2.push_back(v);
                    break;
                }
            }
        }

        cout << "YES" << endl;
        for (auto v : path1) {
            cout << v+1 << ' ';
        }
        cout << endl;
        for (auto v : path2) {
            cout << v+1 << ' ';
        }
        cout << endl;
    } else {
        cout << "NO";
    }

    return 0;
}
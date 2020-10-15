#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

map<pair<int, int>, int> f;
map<pair<int, int>, int> cf;
vector<vector<int>> g, gs;
vector<int> visited;
map<pair<int, int>, int> edges;

int n, m, s, t;

int dfs(int u, int Cmin) {
    if (u == t) {
        return Cmin;
    }

    if (visited[u]) {
        return 0;
    }

    visited[u] = 1;
    //cout << "dfs(" << u+1 << ", " << Cmin << ")" << endl;
    //for (auto v : visited) { cout << v << " "; }
    //cout << endl;
    for (auto v : g[u]) {
        //cout << "!visited[" << v + 1 << "] && f[" << u + 1 << ", " << v + 1 << "] < cf[" 
        //    << u + 1 << ", " << v + 1 << "] = " << "(" 
        //    << cf[{u, v}]<< ")" << (!visited[v] && f[{u, v}] < cf[{u, v}]) << endl;
        if (!visited[v] && f[{u, v}] < cf[{u, v}]) {
            int delta = dfs(v, min(Cmin, (cf[{u, v}] - f[{u, v}])));
            //cout << delta << endl;
            if (delta > 0) {
                f[{u, v}] += delta;
                f[{v, u}] -= delta;
                //cout << "return " << delta << endl;
                return delta;
            }
            
        }
    }
    
    return 0;
}


int ford_falkerson(){
    int flow = 0;
    int min_cap = 2;
    
    while (true){
        visited.assign(n, 0);
        int delta = dfs(s, min_cap);
        if (delta > 0)
            flow += delta;
        else
            return flow;
    }
}


void pass(int u, std::vector<int>& path){
    if(u != t)
        for (auto v: gs[u])
            if (cf[{u, v}] >= f[{u, v}] && f[{u, v}] > 0){
                f[{u, v}]--;
                cf[{u, v}]--;
                path.push_back(v);
                pass(v, path);
                break;
            }

}

std::vector<int> get_path(){
    std::vector<int> path = {s};
    pass(s, path);
    return path;
}

int main() {
    cin >> n >> m >> s >> t;

    g.assign(n, vector<int>());
    gs.assign(n, vector<int>());

    s--;
    t--;

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

        gs[x].push_back(y);
        g[y].push_back(x);
        g[x].push_back(y);
        
    }

    for(auto edge : edges) {
        f[edge.first] = 0;
        f[{edge.first.second, edge.first.first}] = 0;
        cf[edge.first] = edge.second;
    }

    int max_flow = ford_falkerson();

    // cout << "max_flow = " << max_flow << endl;
    if (max_flow > 1) {

        /*        
        for (auto edge : f) {
            cout << edge.first.first + 1<< " " << edge.first.second + 1 << " : " << edge.second << endl;
        }
        */
        
            cout << "YES" << endl;

            
            vector<int> p1, p2;

            p1 = get_path();


            
           
            for (int i = 0; i < p1.size(); i++) {
                cout << p1[i]+1 << ' ';
            }
            cout << endl;
            /*
            for (auto edge : f) {
                cout << edge.first.first + 1<< " " << edge.first.second + 1 << " : " << edge.second << endl;
                
            }
            */
            
            p2 = get_path();

            for (int i = 0; i < p2.size(); i++) { 
                cout << p2[i]+1 << ' ';
            }
            cout << endl;


        
    } else {
        cout << "NO" << endl;
    }
    

    return 0;
}
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

class TaskE {
public:

    map<pair<int, int>, int> f;
    map<pair<int, int>, int> cf;
    vector<vector<int>> g, gs;
    vector<int> visited;
    map<pair<int, int>, int> edges;
    vector<int> p1, p2;
    string answer;

    int n, m, s, t;

    TaskE(int n, int m, int s, int t, vector<pair<int, int>> roads) : n(n), m(m), s(s-1), t(t-1) {
        
        g.assign(n, vector<int>());
        gs.assign(n, vector<int>());

        
        for (int i = 0; i < m; i++) {
            int x, y;
            x = roads[i].first;
            y = roads[i].second;

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
    }

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

    string run() {
        int max_flow = ford_falkerson();

        if (max_flow > 1) {
            answer = "YES";
            p1 = get_path();
            p2 = get_path();
        } else {
            answer = "NO";
        }
        
        return answer;
    }
};

int main() {
    int n = 3, m = 3, s = 1, t = 3;

    std::vector<std::pair<int, int>> roads;

    roads.push_back({1, 2});
    roads.push_back({1, 3});
    roads.push_back({2, 3});


    TaskE task(n,m,s,t,roads);
    task.run();
    cout << task.answer << endl;
    if (task.answer == "YES") {
        for (auto x : task.p1) {
            cout << x+1 << ' ';
        }
        cout << endl;
        for (auto x : task.p2) {
            cout << x+1 << ' ';
        }
    }
}
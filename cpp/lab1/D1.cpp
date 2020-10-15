#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

vector<vector<int>> g;
vector<int> visited;
vector<int> last;
vector<string> s;

int n, m, t_out;

int num(int i, int j) {
    return i * m + j;
}

void add_edge(int i, int j) {   
    g[i].push_back(j);
}

bool is_broken(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m && s[i][j] == '*';
}

bool dfs(int v) {
    if  (last[v] == t_out) {
        return false;
    }
    last[v] = t_out;

    for (auto to : g[v]) {
        if (visited[to] == -1 || dfs(visited[to])) {
            visited[to] = v;
            return true;
        }
    }
    return false;
}

int main() {

    int a, b;
    cin >> n >> m >> a >> b;

    g.resize(n * m);
    s.resize(n);

    for (int i = 0; i < n; i++) {
        s[i].resize(m);
        char c;
        for (int j = 0; j < m; j++) {
            cin >> c;
            s[i][j] = c;
        }
    }
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if  ((i + j) % 2 && is_broken(i, j)) {
                if  (is_broken(i, j+1)) {
                    add_edge(i * m + j, i * m + j + 1);  
                }
                if  (is_broken(i, j-1)) {
                    add_edge(i * m + j, i * m + j - 1);  
                }
                if  (is_broken(i+1, j)) {
                    add_edge(i * m + j, (i+1) * m + j);  
                }
                if  (is_broken(i-1, j)) {
                    add_edge(i * m + j, (i-1) * m + j);  
                }

            }
            k += is_broken(i, j);
        }
    }

    if  (2 * b <= a) {
        cout << b * k;
    } else {
        visited.assign(n * m, -1);
        last.assign(n * m, -1);

        t_out = 0;
        for (int v = 0; v < n*m; v++) {
            t_out++;
            dfs(v);    
        }

        int f = 0;
        for (int to = 0; to < n * m; to++) {
            f += (visited[to] != -1);
        }

        cout << f * a + (k - 2 * f) * b << endl;
    }

    return 0;
}
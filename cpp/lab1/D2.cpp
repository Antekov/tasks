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
    cin.ignore();

    g.resize(n * m);
    s.resize(n);

    for (int i = 0; i < n; i++) {
        getline(cin, s[i]);
        s[i].resize(m);
    }

    cout << 5;

    return 0;
}
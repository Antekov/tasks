#include <iostream>
#include <vector>
#include <set>
using namespace std;

int a, b, M, x, y, start, end;

const int INF = 200000000;
const int FOUND = -1;

vector<int> d;

vector<int> path;
set<int> path_nodes;

void print(vector<int> &a) {
    for (auto x : a) {
        // cout << x << ' ';
    }
    // cout << endl;
}

int cost(int node, int succ) {
    int res = INF;
    if ((node + 1) % M == succ) res = a;
    if ((node*node + 1) % M == succ) res = res > b ? b : res;
    return res;
}

int h(int node) {
    int c = a < b ? a : b;
    return c*((M + y - node) % M) / 2;
}

bool is_goal(int node) { return node == y; }

vector<int> & successors(int node) {
    vector<int> *s = new vector<int>(2);
    (*s)[0] = (node + 1) % M;
    (*s)[1] = (node*node + 1) % M;
    return *s;
}


int search(int g, int bound) {
    // cout << "Search with path:" << endl;\
    print(path);
    int node = *(path.end()-1);
    int f = g + h(node);

    if (f > INF) { f = INF; }

    // cout << "f = " << f << endl;
    
    if (f > bound) return f;
    if (is_goal(node)) return FOUND;

    int min = INF;
    // cout << "Successors:" << endl;
    print(successors(node));

    for (auto succ : successors(node)) {
        if (path_nodes.count(succ) == 0) {
            // cout << "Add " << succ << " to path | " << g + cost(node, succ) << endl;
            path.push_back(succ);

            int t = search(g + cost(node, succ), bound);
            if (t == FOUND) return FOUND;
            if (t < min) min = t;
            // cout << "Remove " << succ << " to path" << endl;
            path.pop_back();
        }
    }

    return min;
}



int ida_star(int root) {
    int bound = h(root);
    
    path.push_back(root);
    path_nodes.insert(root);

    // cout << "Initial:" << endl;
    print(d);
    
    while (true) {

        print(path);
        int t = search(0, bound);
        if (t == FOUND) {
            return bound;
        }
        if (t == INF) {
            return INF;
        }
        bound = t;
    }
}

int main() {
    cin >> a >> b >> M >> x >> y;

    d.resize(M);
    
    for (int i = 0; i < M; i++)
    {
        d[i] = INF;
    }
    
    d[x] = 0;

    int res = 0;
    
    res = ida_star(x);

    // cout << "Res = ";
    cout << res << endl;
    
    return 0;
}
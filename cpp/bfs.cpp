#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

long long a, b, M, x, y, start, end;

const long long INF = 200000000;
const long long FOUND = -1;

vector<long long> d;

vector<long long> path;
set<long long> path_nodes;

void print(vector<long long> &a) {
    for (auto x : a) {
        cout << x << ' ';
    }
    cout << endl;
}


long long cost(long long node, long long succ) {
    long long res = INF;
    if ((node + 1) % M == succ) res = a;
    if ((node*node + 1) % M == succ) res = res > b ? b : res;
    return res;
}

long long h(long long node) {
    long long c = a < b ? a : b;
    return c*((M + y - node) % M) / 2;
}

bool is_goal(long long node) { return node == y; }

vector<long long> & successors(long long node) {
    vector<long long> *s = new vector<long long>(2);
    (*s)[0] = (node + 1) % M;
    (*s)[1] = (node*node + 1) % M;
    return *s;
}

long long BFS (long long v)
{
    vector<long long> dist(M, -1);
    dist[v] = 0;
    queue<long long> q;
    q.push(v);
    while(!q.empty())
    {
        long long t = q.front();
        q.pop();
        for(long long vertex: successors(t))
        {
            if(dist[vertex] == -1 || dist[vertex] > dist[t] + cost(t, vertex))
            {
                q.push(vertex);
                dist[vertex] = dist[t] + cost(t, vertex);
            }
        }
    }
    return dist[y];
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
    
    res = BFS(x);

    // cout << "Res = ";
    cout << res << endl;
    
    return 0;
}
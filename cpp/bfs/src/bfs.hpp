#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

class BFS_Task {
public:
    long long a, b, M, x, y, start, end;
    const long long INF = 200000000;
    const long long FOUND = -1;

    vector<long long> path;
    set<long long> path_nodes;

    BFS_Task(long long a, long long b, long long M, long long x, long long y) : a(a), b(b), M(M), x(x), y(y) {}
  
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

    vector<long long> successors(long long node) {
        vector<long long> s(2);
        (s)[0] = (node + 1) % M;
        (s)[1] = (node*node + 1) % M;
        return s;
    }

    long long run()
    {
        vector<long long> dist(M, -1);
        dist[x] = 0;
        queue<long long> q;
        q.push(x);
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
};



#include <iostream>
#include <set>
#include <vector>

class CGraph {
public:
    CGraph(int verticesAmount) {
        graph.resize(verticesAmount + 1);
    }

    void add(int b, int e, int w) {
        graph[b].push_back(std::make_pair(e, w));
        graph[e].push_back(std::make_pair(b, w));
    }

    std::vector<std::vector<std::pair<int, int>>> getGraph() {
        return graph;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> graph;
};

int prim(std::vector<std::vector<std::pair<int, int>>> graph, int verticesAmount) {
    std::vector<bool> used(verticesAmount + 1, false);
    int INF = 1000000000;    
    std::vector<int> minWeight (verticesAmount + 1, INF);
    minWeight[1] = 0;
    std::set<std::pair<int,int>> q;
    q.insert (std::make_pair (0, 1));
    int answer = 0;
    for(int i = 0; i <= verticesAmount; i++) {
        if (q.empty()) {
            break;
        }
        int curr = q.begin()->second;
        used[curr] = true;
        answer += q.begin()->first;
        q.erase (q.begin());
        
        for (int j = 0; j < graph[curr].size(); j++) {
            int to = graph[curr][j].first;
            int cost = graph[curr][j].second;
            if(used[to]) {
                continue;
            }
            if (cost < minWeight[to]) {
                q.erase(std::make_pair(minWeight[to], to));
                minWeight[to] = cost;
                q.insert (std::make_pair (minWeight[to], to));
            }
        }
    }
    return answer;
}

int main() {
    int verticesAmount;
    int edgesAmount;
    std::cin >> verticesAmount >> edgesAmount;
    CGraph graph(verticesAmount);
    for(int i = 0; i < edgesAmount; i++) {
        int b;
        int e;
        int w;
        std::cin >> b >> e >> w;
        graph.add(b, e, w);
    }

    std::cout << prim(graph.getGraph(), verticesAmount);
    return 0;
}
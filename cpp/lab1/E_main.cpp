#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int INF = 2147483647;

class Edge{
public:
    Edge(int from, int to, char is_straight, int c = 1, int f = 0): from(from), to(to), is_straight(is_straight), capacity(c), flow(f){};
    int from, to, capacity, flow, back_edge_num;
    bool is_straight;
};

class Graph{
public:
    Graph(int num_of_vertices): num_of_vertices(num_of_vertices) {edges.resize(num_of_vertices);}
    int add_edge(int from, Edge edge);
    int get_num_of_edges();
    int get_num_of_vertices();
    std::vector<std::vector<Edge> > edges;
private:
    const int num_of_vertices;
    int num_of_edges = 0;
};

int Graph::add_edge(int from, Edge edge){
    edges[from].push_back(edge);
    ++num_of_edges;
    return (edges[from].size() - 1);
}

int Graph::get_num_of_edges(){
    return num_of_edges;
}

int Graph::get_num_of_vertices(){
    return num_of_vertices;
}

int dfs(Graph& graph, std::vector<bool>& visited, int u, int t, int min_cap){
    if(u == t)
        return min_cap;
    if(visited[u])
        return 0;
    visited[u] = true;
    cout << "dfs(" << u+1 << ", " << min_cap << ")" << endl;
    for (auto v : visited) { cout << v << " "; }
    cout << endl;
    for (Edge& edge: graph.edges[u]) {
        cout << "!visited[" << edge.to + 1 << "] && f[" << edge.from + 1 << ", " << edge.to + 1 << "] < cf[" 
            << edge.from + 1 << ", " << edge.to + 1 << "] = " << "(" << edge.capacity << ")" 
            << (!visited[edge.to] && edge.capacity > edge.flow) << endl;
        if((!visited[edge.to])&&(edge.capacity > edge.flow)){
            int delta = dfs(graph, visited, edge.to, t, std::min(min_cap, (edge.capacity - edge.flow)));
            cout << delta << endl;
            if(delta > 0){
                edge.flow += delta;
                graph.edges[edge.to][edge.back_edge_num].flow -= delta;
                cout << "return " << delta << endl;
                return delta;
            }
        }
    }
    return 0;
}

int Ford_Falkerson(Graph& graph, int s, int t){
    int flow = 0;
    int min_cap = INF;
    std::vector<bool> visited (graph.get_num_of_vertices(), false);
    while (true){
        visited.assign(graph.get_num_of_vertices(), false);
        int delta = dfs(graph, visited, s, t, min_cap);
        if (delta > 0)
            flow += delta;
        else
            return flow;
    }
}

void pass(Graph& graph, int from, int to, std::vector<int>& path){
    if(from != to)
        for (Edge& edge: graph.edges[from])
            if((edge.capacity == edge.flow)&&(edge.is_straight)){
                --edge.flow;
                path.push_back(edge.to);
                pass(graph, edge.to, to, path);
                break;
            }

}

std::vector<int> get_path(Graph& graph, int from, int to){
    std::vector<int> path = {from};
    pass(graph, from, to, path);
    return path;
}

int main()
{
    int num_of_opushki, num_of_edges, s, t;
    std::cin >> num_of_opushki >> num_of_edges >> s >> t;
    Graph graph = Graph(num_of_opushki);
    int from, to;
    for (int i = 0; i < num_of_edges; ++i){
        std::cin >> from >> to;
        Edge straight_edge = Edge(from-1, to-1, true);
        int straight_edge_num = graph.add_edge(from-1, straight_edge);
        Edge back_edge = Edge(to-1, from-1, false, 0);
        int back_edge_num = graph.add_edge(to-1, back_edge);
        graph.edges[from-1][straight_edge_num].back_edge_num = back_edge_num;
        graph.edges[to-1][back_edge_num].back_edge_num = straight_edge_num;
    }
    if(Ford_Falkerson(graph, s-1, t-1) > 1){
        std::cout << "YES" << "\n";
        std::vector<int> first_path = get_path(graph, s-1, t-1);
        std::vector<int> second_path = get_path(graph, s-1, t-1);
        for (int i: first_path)
            std::cout << i+1 << " ";
        std::cout << "\n";
        for (int i: second_path)
            std::cout << i+1 << " ";
    }
    else
        std::cout << "NO";
    return 0;
}

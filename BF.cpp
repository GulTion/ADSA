#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge { int u, v, weight; };

class Graph {
    int V; 
    vector<Edge> edges;

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int weight) {
        if (u < 0 || v < 0 || u >= V || v >= V) {
            cout << "Invalid edge from " << u << " to " << v << endl;
            return;
        }
        edges.push_back({u, v, weight});
    }

    void bellmanFord(int src) {
        if (src < 0 || src >= V) {
            cout << "Invalid source vertex: " << src << endl;
            return;
        }

        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Relax all edges V-1 times
        for (int i = 1; i < V; ++i) {
            for (const Edge& e : edges) {
                if (dist[e.u] != INT_MAX && dist[e.u] + e.weight < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.weight;
                }
            }
        }

        // Check for negative-weight cycles
        for (const Edge& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.weight < dist[e.v]) {
                cout << "Negative weight cycle detected" << endl;
                return;
            }
        }

        // Print the distances
        for (int i = 0; i < V; ++i) {
            cout << "Vertex " << i << " \t Distance: " << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
        }
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int V, E;
    cin >> V >> E;
    if (V <= 0) {
        cout << "Number of vertices must be positive." << endl;
        return 0;
    }
    if (E < 0) {
        cout << "Number of edges cannot be negative." << endl;
        return 0;
    }

    Graph g(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    int src;
    cout << "Enter source vertex: ";
    cin >> src;
    g.bellmanFord(src);
    return 0;
}

//5 8
//0 1 -1
//0 2 4
//1 2 3
//1 3 2
//1 4 2
//3 2 5
//3 1 1
//4 3 -3

//0 0
//1 -1
//2 2
//3 -2
//4 1




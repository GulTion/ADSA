#include <iostream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

struct Edge {
    int u, v;
    int weight;
};

class Graph {
    int V;
    vector<Edge> edges;

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i = 1; i < V; ++i) {
            for (const Edge& edge : edges) {
                int u = edge.u;
                int v = edge.v;
                int weight = edge.weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        // Check for negative weight cycles
        for (const Edge& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains a negative weight cycle" << endl;
                return;
            }
        }

        // Print the distance array
        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < V; ++i) {
            stringstream ss;
            ss << dist[i];
            string distance = (dist[i] == INT_MAX) ? "INF" : ss.str();
            cout << i << "\t\t" << distance << endl;
        }
    }
};

int main() {
    int V, E; // Number of vertices and edges

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter each edge in the format (u v weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cout << "Edge " << (i + 1) << ": ";
        cin >> u >> v >> weight; // Read each edge
        g.addEdge(u, v, weight);
    }

    cout << "Running Bellman-Ford algorithm from source vertex 0" << endl;
    g.bellmanFord(0);

    return 0;
}


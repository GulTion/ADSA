#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <sstream>

using namespace std;

struct Edge {
    int v;
    int weight;
};

class Graph {
    int V; 
    vector<vector<Edge>> adj; 

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        typedef pair<int, int> pii;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        pq.push(pii(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (const Edge& edge : adj[u]) {
                int v = edge.v;
                int weight = edge.weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(pii(dist[v], v));
                }
            }
        }

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
    int V; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);

    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges in the format (u v weight):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight; // Read edges
        g.addEdge(u, v, weight);
    }

    cout << "Running Dijkstra's algorithm from source vertex " << 0 << endl;
    g.dijkstra(0);

    return 0;
}


#include <iostream>
#include <vector>
#include <limits>
#include <queue>

const int INF = std::numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

// Bellman-Ford algorithm to find shortest paths from a single source
std::vector<int> bellmanFord(const std::vector<std::vector<Edge>>& graph, int source) {
    int n = graph.size();
    std::vector<int> dist(n, INF);
    dist[source] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            if (dist[u] != INF) {
                for (const auto& e : graph[u]) {
                    if (dist[u] + e.weight < dist[e.to]) {
                        dist[e.to] = dist[u] + e.weight;
                    }
                }
            }
        }
    }

    return dist;
}

// Dijkstra's algorithm to find shortest paths from a single source
std::vector<int> dijkstra(const std::vector<std::vector<Edge>>& graph, int source) {
    int n = graph.size();
    std::vector<int> dist(n, INF);
    dist[source] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& e : graph[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                pq.emplace(dist[e.to], e.to);
            }
        }
    }

    return dist;
}

// Johnson's Algorithm to find shortest paths between all pairs of nodes
std::vector<std::vector<int>> johnsonAlgorithm(const std::vector<std::vector<Edge>>& graph) {
    int n = graph.size();
    std::vector<std::vector<Edge>> modifiedGraph(n + 1);

    for (int u = 0; u < n; ++u) {
        for (const auto& e : graph[u]) {
            modifiedGraph[u].push_back(e);
        }
        modifiedGraph[n].push_back({u, 0});
    }

    std::vector<int> h = bellmanFord(modifiedGraph, n);
    if (h[n] == INF) {
        std::cerr << "Negative-weight cycle detected" << std::endl;
        return {};
    }

    std::vector<std::vector<int>> distances(n, std::vector<int>(n, INF));

    for (int u = 0; u < n; ++u) {
        std::vector<std::vector<Edge>> reweightedGraph(n);
        for (int v = 0; v < n; ++v) {
            for (const auto& e : graph[v]) {
                reweightedGraph[v].push_back({e.to, e.weight + h[v] - h[e.to]});
            }
        }

        std::vector<int> dist = dijkstra(reweightedGraph, u);
        for (int v = 0; v < n; ++v) {
            if (dist[v] != INF) {
                distances[u][v] = dist[v] + h[v] - h[u];
            }
        }
    }

    return distances;
}

int main() {
    int n, m;
    std::cout << "Enter the number of nodes and edges: ";
    std::cin >> n >> m; // Read number of nodes and edges

    if (n <= 0 || m < 0) {
        std::cerr << "Invalid number of nodes or edges" << std::endl;
        return 1;
    }

    std::vector<std::vector<Edge>> graph(n);

    // Read edges from the user
    std::cout << "Enter the edges (format: u v w, where u and v are node indices and w is the weight):" << std::endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        if (u < 0 || u >= n || v < 0 || v >= n || w < 0) {
            std::cerr << "Invalid edge input" << std::endl;
            return 1;
        }
        graph[u].push_back({v, w});
    }

    // Perform Johnson's algorithm
    std::vector<std::vector<int>> distances = johnsonAlgorithm(graph);

    if (distances.empty()) {
        std::cout << "Graph contains a negative-weight cycle" << std::endl;
        return 1;
    }

    // Output the shortest distances
    std::cout << "Shortest distances between all pairs of nodes:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distances[i][j] == INF) {
                std::cout << "INF ";
            } else {
                std::cout << distances[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}


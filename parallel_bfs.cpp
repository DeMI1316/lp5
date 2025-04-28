#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void parallel_bfs(const vector<vector<int>> &g, int start) {
    int n = g.size();
    vector<bool> vis(n, false);
    queue<int> q;
    vis[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";

    while (!q.empty()) {
        int s = q.size();
        vector<int> next;

        #pragma omp parallel
        {
            vector<int> local_next;

            #pragma omp for
            for (int i = 0; i < s; ++i) {
                int u;
                #pragma omp critical
                { u = q.front(); q.pop(); cout << u << " "; }

                for (int v : g[u]) {
                    bool visit = false;
                    #pragma omp critical
                    { if (!vis[v]) { vis[v] = true; visit = true; } }
                    if (visit) local_next.push_back(v);
                }
            }

            #pragma omp critical
            next.insert(next.end(), local_next.begin(), local_next.end());
        }

        for (int v : next) q.push(v);
    }
    cout << endl;
}

int main() {
    int n, e;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    vector<vector<int>> g(n);

    cout << "Enter " << e << " edges (u v):\n";
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);  // Convert 1-based to 0-based indexing
        g[v - 1].push_back(u - 1);  // For undirected graph
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;
    start--;  // Convert 1-based to 0-based indexing

    parallel_bfs(g, start);
}


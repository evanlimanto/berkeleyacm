// Runs Bellman-Ford for Single-Source Shortest Paths with
// negative edge weights.
//
// Running time : O(|V| ^ 3)
//
//  INPUT:  start, w[i][j] = edge cost from i to j.
//  OUTPUT: dist[i] = min cost path from start to i.
//          prev[i] = previous node of i on best path from start node.

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000 * 1000 * 1000;

typedef vector<int> VI;
typedef vector<vector<int> > VVI;

bool BellmanFord(const VVI &w, VI &dist, VI &prev, int start) {
    int n = static_cast<int>(w.size());
    prev = VI(n, -1);
    dist = VI(n, INF);
    dist[start] = 0;

    // Iterate (n - 1) times for algorithm,
    // and once to check for negative cycles.
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[j] > dist[i] + w[i][j]) {
                    if (k == n - 1)
                        return false;
                    dist[j] = dist[i] + w[i][j];;
                    prev[j] = i;
                }
            }
        }
    }

    return true;
}

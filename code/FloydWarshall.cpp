#include <bits/stdc++.h>

using namespace std;

const int INF = 1000 * 1000 * 1000;

#define mp make_pair
#define pb push_back

typedef vector<vector<int> > VVI;
typedef vector<int> VI;

typedef pair<int, int> PII;

// Floyd-Warshall algorithm for All-Pairs Shortest paths.
// Also handles negative edge weights. Returns true if a negative
// weight cycle is found.
//
// Running time: O(|V| ^ 3)
//
//  INPUT:  w[i][j] = weight of edge from i to j
//  OUTPUT: w[i][j] = shortest path weight from i to j
//          prev[i][j] = node before j on the best path starting at i

bool FloydWarshall(VVI &w, VVI &prev) {
    int n = (int)w.size();
    prev = VVI(n, VI(n, -1));

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (w[i][j] > w[i][k] + w[k][j]) {
                    w[i][j] = w[i][k] + w[k][j];
                    prev[i][j] = k;
                }
            }
        }
    }

    // Check for negative weight cycles.
    for (int i = 0; i < n; i++)
        if (w[i][i] < 0) return false;
    return true;
}

int main() {
    return 0;
}

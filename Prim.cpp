// Runs Prim's algorithm for constructing MSTs.
//
// Running time: O(|V| ^ 2)
//
//  INPUT:  w[i][j] = cost of edge from i to j
//          (Make sure that w[i][j] is nonnegative and
//           symmetric. Missing edges should be given -1
//           weight.)
//
//  OUTPUT: edges = list of pair<int, int> in MST
//                  return total weight of tree

#include <iostream>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

const int INF = 1000 * 1000 * 1000;

#define pb push_back
#define mp make_pair

typedef vector<int> VI;
typedef vector<vector<int> > VVI;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

int Prim(const VVI &w, VPII &edges) {
    int n = (int)w.size();
    VI found(n);
    VI prev(n, -1);
    VI dist(n, INF);

    int here = 0;
    dist[here] = 0;

    while (here != -1) {
        found[here] = true;
        int best = -1;
        for (int k = 0; k < n; k++) {
            if (!found[k]) {
                if (w[here][k] != -1 && dist[k] > w[here][k]) {
                    dist[k] = w[here][k];
                    prev[k] = here;
                }
                if (best == -1 || dist[k] < dist[best]) best = k;
            }
        }
        here = best;
    }

    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        if (prev[i] != -1) {
            edges.pb(mp(prev[i], i));
            total_weight += w[prev[i]][i];
        }
    }
    return total_weight;
}

int main(){
  int ww[5][5] = {
    {0, 400, 400, 300, 600},
    {400, 0, 3, -1, 7},
    {400, 3, 0, 2, 0},
    {300, -1, 2, 0, 5},
    {600, 7, 0, 5, 0}
  };
  VVI w(5, VI(5));
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      w[i][j] = ww[i][j];
    
  // expected: 305
  //           2 1
  //           3 2
  //           0 3
  //           2 4
  
  VPII edges;
  cout << Prim (w, edges) << endl;
  for (int i = 0; i < edges.size(); i++)
    cout << edges[i].first << " " << edges[i].second << endl;
}

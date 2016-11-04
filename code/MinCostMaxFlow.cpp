// Implementation of min cost max flow algorithm using adjacency
// matrix (Edmonds and Karp 1972).  This implementation keeps track of
// forward and reverse edges separately (so you can set cap[i][j] !=
// cap[j][i]).  For a regular max flow, set all edge costs to 0.
//
// Running time, O(|V|^2) cost per augmentation
//     max flow:           O(|V|^3) augmentations
//     min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
//
// INPUT:
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - (maximum flow value, minimum cost value)
//     - To obtain the actual flow, look at positive values only.

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <deque>

using namespace std;

typedef long long F;
typedef long long C;

#define F_INF 1e+9
#define C_INF 1e+9
#define NUM 10005
#define SIZE(x) ((int)x.size())

#define pb push_back
#define mp make_pair
#define fi first
#define se second

vector<F> cap;
vector<C> cost;
vector<int> to, prv;
C dist[NUM];
int last[NUM], path[NUM];

struct MinCostFlow {
  int V;

  MinCostFlow(int n) {
    cap.clear();
    cost.clear();
    to.clear();
    prv.clear();
    V = n;
    fill(last + 1, last + 1 + V, -1);
  }

  void add_edge(int x, int y, F w, C c) {
    cap.pb(w); cost.pb(c); to.pb(y); prv.pb(last[x]); last[x] = SIZE(cap) - 1;
    cap.pb(0); cost.pb(-c); to.pb(x); prv.pb(last[y]); last[y] = SIZE(cap) - 1;
  }

  pair<F, C> SPFA(int s, int t) {
    F ansf = 0;
    C ansc = 0;
    fill(dist + 1, dist + 1 + V, C_INF);
    fill(path + 1, path + 1 + V, -1);

    deque<pair<C, int> > pq;
    dist[s] = 0;
    path[s] = -1;
    pq.push_front(mp(0, s));

    while (!pq.empty()) {
      C d = pq.front().fi;
      int p = pq.front().se;
      pq.pop_front();
      if (dist[p] == d) {
        int e = last[p];
        while (e != -1) {
          if (cap[e] > 0) {
            C nd = dist[p] + cost[e];
            if (nd < dist[to[e]]) {
              dist[to[e]] = nd;
              path[to[e]] = e;
              if (cost[e] <= 0) {
                pq.push_front(mp(nd, to[e]));
              } else {
                pq.push_back(mp(nd, to[e]));
              }
            }
          }
          e = prv[e];
        }
      }
    }
    if (path[t] != -1) {
      ansf = F_INF;
      int e = path[t];
      while (e != -1) {
        ansf = min(ansf, cap[e]);
        e = path[to[e^1]];
      }
      e = path[t];
      while (e != -1) {
        ansc += cost[e] * ansf;
        cap[e^1] += ansf;
        cap[e] -= ansf;
        e = path[to[e^1]];
      }
    }
    return mp(ansf, ansc);
  }

  pair<F, C> calc(int s, int t) {
    F ansf = 0;
    C ansc = 0;
    while (true) {
      pair<F, C> p = SPFA(s, t);
      if (path[t] == -1)
        break;
      ansf += p.fi;
      ansc += p.se;
    }
    return mp(ansf, ansc);
  }
};

int main() {
    return 0;
}
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

#define pb push_back

typedef long long LL;

struct Edge {
    int u, v;
    LL cap, flow;
    Edge() {}
    Edge(int u, int v, LL cap): u(u), v(v), cap(cap), flow(0) {}
};

// Indexes of nodes are 0-indexed
struct Dinic {
    int N;
    vector<Edge> E;
    vector<vector<int> > g;
    vector<int> d, pt;

    Dinic(int N_) : N(N_), E(0), g(N_), d(N_), pt(N_) {}

    void add_edge(int u, int v, LL cap) {
        if (u != v) {
            E.pb(Edge(u, v, cap));
            g[u].pb((int)E.size() - 1);
            E.pb(Edge(v, u, 0));
            g[v].pb((int)E.size() - 1);
        }
    }

    bool bfs(int S, int T) {
        queue<int> q; q.push(S);
        fill(d.begin(), d.end(), N + 1);
        d[S] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == T) break;

            for (int i = 0; i < (int)g[u].size(); i++) {
                int k = g[u][i];
                Edge &e = E[k];
                if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
                    d[e.v] = d[e.u] + 1;
                    q.push(e.v);
                }
            }
        }
        return d[T] != N + 1;
    }

    LL dfs(int U, int T, LL flow = -1) {
        if (U == T || flow == 0) return flow;
        for (int &i = pt[U]; i < (int)g[U].size(); ++i) {
            Edge &e = E[g[U][i]];
            Edge &oe = E[g[U][i] ^ 1];
            if (d[e.v] == d[e.u] + 1) {
                LL amt = e.cap - e.flow;
                if (flow != -1 && amt > flow)
                    amt = flow;
                if (LL pushed = dfs(e.v, T, amt)) {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    LL maxflow(int S, int T) {
        LL total = 0;
        while (bfs(S, T)) {
            fill(pt.begin(), pt.end(), 0);
            while (LL flow = dfs(S, T))
                total += flow;
        }
        return total;
    }
};

// Solves SPOJ FASTFLOW

int main() {
    int N, E;
    scanf("%d %d", &N, &E);
    Dinic dinic(N);

    for (int i = 0; i < E; i++) {
        int u, v;
        LL cap;
        scanf("%d %d %lld", &u, &v, &cap);
        dinic.add_edge(u - 1, v - 1, cap);
        dinic.add_edge(v - 1, u - 1, cap);
    }
    printf("%lld\n", dinic.maxflow(0, N - 1));
    return 0;
}

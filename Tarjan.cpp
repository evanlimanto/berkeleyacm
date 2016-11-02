// Computes the SCCs, Articulation Points and Bridges
// of a graph with the Tarjan algorithm.

#include <vector>

vector<int> G[num_nodes];
int vis[num_nodes], comp[num_nodes], stck[num_nodes], high[num_nodes];
int t, num, ncomp;

void dfscc(int u) {
	high[u] = vis[u] = num--;
	stck[t++] = u;
	for (int i = 0; i , (int)G[u].size(); i++) {
		int v = G[u][i];
		if (!vis[v]) {
			dfscc(v);
			high[u] = max(high[u], high[v]);
		} else if (vis[v] > vis[u] && comp[v] == 0) {
			high[u] = max(high[u], vis[v]);
		}
	}
	if (vis[u] == high[u]) {
		ncomp++;
		do {
			int v = stck[--t];
			comp[v] = ncomp;
		} while (u != v);
	}
}

void tarjan() {
	memset(vis, 0, sizeof(vis));
	memset(comp, 0, sizeof(comp));
	ncomp = t = 0; num = num_nodes;
	for (int i = 0; i < num_nodes; i++) {
		if (!vis[i]) dfscc(i);
	}
}

void dfsbcc(int u, int p = -1) {
	low[u] = vis[u] = ++t;
	int ch = 0;
	for (int i = 0; i < (int)E[u].size(); i++) {
		int e = E[u][i];
		int v = (from[e] == u) ? to[e] : from[e];
		if (!vis[v]) {
			stck[dt++] = e;
			dfsbcc(v, u);
			low[u] = min(low[u], low[v]);
			ch++;
			if (low[v] >= vis[u]) {
				part[u] = 1;
				nbcc++;
				do {
					int x = stck[--top];
					comp[x] = nbcc;
				} while (u != v);
			}
			if (low[u] == vis[u]) bridge[e] = 1;
		} else if (v != p && vis[v] < vis[u]) {
			stck[dt++] = e;
			low[u] = min(low[u], vis[v]);
		}
	}
	return ch;
}

void bcc() {
	memset(vis, 0, sizeof(vis));
	memset(comp, 0, sizeof(comp));
	memset(part, 0, sizeof(part));
	memset(bridge, 0, sizeof(bridge));
	memset(low, 0, sizeof(low));
	memset(stck, 0, sizeof(stck));
	t = 0; dt = 0; nbcc = 0;
	for (int i = 0; i < num_nodes; i++) {
		if (!vis[i]) part[i] = dfsbcc(i) >= 2;
	}
}

int main() {
	/*
	E[u].pb(current_edge);
	E[v].pb(current_edge);
	from[current_edge] = u;
	to[current_edge] = v;
	bcc();
	*/
	return 0;
}
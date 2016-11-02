#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

// type of weights
typedef int WT;
typedef tuple<WT, int, int> EDGE;
typedef vector<EDGE> GT;

int find(vector<int> &C, int x) {
	return (C[x] == x) ? x : C[x] = find(C, C[x]);
}

WT Kruskal(int V, GT graph) {
	WT mst = 0;
	sort(graph.begin(), graph.end());

	vector<int> C(V), R(V);
	for (int i = 0; i < V; i++) {
		C[i] = i;
		R[i] = 0;
	}

	for (auto e : graph) {
		int w, u, v;
		tie(w, u, v) = e;
		int uc = find(C, u), vc = find(C, v);
		if (uc != vc) {
			mst += w;

			if (R[uc] > R[vc]) C[vc] = uc;
			else if (R[vc] > R[uc]) C[uc] = vc;
			else { C[vc] = uc; R[uc]++; }
		}
	}

	return mst;
}

// SOLVE SPOJ BLINNET
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		GT graph;

		for (int k = 1; k <= n; k++) {
			string id;
			cin >> id;
			int p;
			cin >> p;
			for (int i = 1; i <= p; i++) {
				int x; WT w;
				cin >> x >> w;
				graph.push_back(EDGE(w, k-1, x-1));
			}
		}
		cout << Kruskal(n, graph) << endl;
	}
}

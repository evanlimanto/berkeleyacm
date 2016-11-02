#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// type of weights
typedef int WT;
struct edge {
	int u, v;
	WT d;
};

struct edgeCmp {
	int operator() (const edge& a, const edge& b) { return a.d > b.d; }
};

int find(vector<int>& C, int x) {
	return (C[x] == x) ? x : C[x] = find(C, C[x]);
}

WT Kruskal(vector<vector<WT>> &w) {
	int n = w.size();
	WT weight = 0;
	vector<int> C(n), R(n);
	for (int i = 0; i < n; i++) { C[i] = i; R[i] = 0; }

	vector<edge> T;
	priority_queue<edge, vector<edge>, edgeCmp> E;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (w[i][j] > 0) {
				edge e;
				e.u = i; e.v = j; e.d = w[i][j];
				E.push(e);
			}
		}
	}

	while (T.size() < n - 1 && !E.empty()) {
		edge cur = E.top(); E.pop();
		int uc = find(C, cur.u), vc = find(C, cur.v);
		if (uc != vc) {
			T.push_back(cur); weight += cur.d;

			if (R[uc] > R[vc]) C[vc] = uc;
			else if (R[vc] > R[uc]) C[uc] = uc;
			else { C[vc] = uc; R[uc]++; }
		}
	}

	return weight;
}

// SOLVE SPOJ BLINNET
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<vector<int>> vv;
		vv.resize(n);
		for (auto &v : vv) {
			v.resize(n);
		}

		int k = 1;
		while (k <= n) {
			string id;
			cin >> id;
			int p;
			cin >> p;
			for (int i = 1; i <= p; i++) {
				int x; WT w;
				cin >> x >> w;
				vv[k-1][x-1] = w;
			}
			k++;
		}
		// for (auto &v : vv) {
		// 	for (auto &a : v) {
		// 		cout << a << "	 ";
		// 	}
		// 	cout << endl;
		// }
		cout << Kruskal(vv) << endl;
	}
}

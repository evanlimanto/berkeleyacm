#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int V = 100005;
vector<int> adj[V];
int q[V], *qf, *qb; // BFS queue

// chain[u] is u's chain number and head[u] is
// the node closest to root in u's chain.
int parent[V], heavy[V], depth[V], size[V], chain[V], head[V];

void DFS(int i) {
	size[i] = i;
	for (int k = 0; k < (int)adj[i].size(); k++) {
		int j = adj[i][k];
		if (j == parent[i]) continue;

		parent[j] = i;
		depth[j] = depth[i] + 1;

		DFS(j);

		size[i] += size[j];
		if (heavy[i] == -1 || size[j] > size[heavy[i]])
			heavy[i] = j;
	}
}

void heavylight_DFS(int N) {
	memset(heavy, -1, sizeof(heavy));
	parent[0] = -1;
	depth[0] = 0;
	DFS(0);

	int c = 0;
	for (int i = 0; i < N; i++) {
		if (parent[i] == -1 || heavy[parent[i]] != i) {
			for (int k = i; k != -1; k = heavy[k])
				chain[k] = c, head[k] = i;
			c++;
		}
	}
}

void heavylight_BFS(int N) {
	qf = qb = q;
	parent[0] = -1;
	depth[0] = 0;
	*qb++ = 0;
	while (qf < qb) {
		for (int i = *qf++, k = 0; k < (int)adj[i].size(); k++) {
			int j = adj[i][k];
			if (j == parent[i]) continue;
			parent[j] = i;
			depth[j] = depth[i] + 1;
			*qb++ = j;
		}
	}
	memset(size, 0, sizeof(size));
	memset(heavy, -1, sizeof(heavy));
	for (int k = N - 1; k > 0; k--) {
		int j = q[k], i = parent[q[k]];
		size[j]++;
		size[i] += size[j];
		if (heavy[i] == -1 || size[j] > size[heavy[i]])
			heavy[i] = j;
	}

	int c = 0;
	for (int i = 0; i < N; i++) {
		if (parent[i] == -1 || heavy[parent[i]] != i) {
			for (int k = i; k != -1; k = heavy[k])
				chain[k] = c, head[k] = i;
			c++;
		}
	}
}

int lca_1(int i, int j) {
	while (chain[i] != chain[j])
		if (depth[head[i]] > depth[head[j]])
			i = parent[head[i]];
		else
			j = parent[head[j]];
	return depth[i] < depth[j] ? i : j;
}

int lca_2(int i, int j) {
	while (chain[i] != chain[j]) {
		if (depth[head[i]] > depth[head[j]])
			swap(i, j);
		j = parent[head[j]];
	}

	if (depth[i] > depth[j])
		swap(i, j);
	return i;
}

void look_inside(int N) {
	printf("\n");
	printf("HEAVY: \n");
	printf("(i, j): i----(heavy edge)----j\n\n");

    for (int i = 0; i < N; i++)
		printf("(%d, %d)\n", i, heavy[i]);
	printf("\n");
	printf("CHAIN: \n");
	printf("(i, j): Node i is in group (heavy-path group) number j\n\n");

	for (int i = 0; i < N; i++)
		printf("(%d, %d)\n", i, chain[i]);

	printf("\n");
	printf("HEAD: \n");
	printf("(i, j): Node i goes up all the way to the highest node (j) which is in the same group\n\n");

	for (int i = 0; i < N; i++)
       printf("(%d, %d)\n", i, head[i]);
}

// Lowest Common Ancestor algorithm for two nodes in a tree.
//
// Running time: O(|V|log|V|) for precomputation, O(log|V|) per query

#include <cstdio>
#include <vector>

using namespace std;

const int max_nodes = 100000, log_max_nodes = 17;
int num_nodes, log_num_nodes, root;

vector<int> children[max_nodes];
int A[max_nodes][log_max_nodes + 1]; // A[i][j] is the 2^j-th ancestor of node i, or -1 if that ancestor does not exist.
int L[max_nodes];                    // L[i] is the distance between node i and the root.

// floor of the binary logarithm of n
int lb(int n) {
    if (n == 0)
        return -1;
    int p = 0;
    if (n >= 1<<16) { n >>= 16; p += 16; }
    if (n >= 1<< 8) { n >>= 8;  p += 8;  }
    if (n >= 1<< 4) { n >>= 4;  p += 4;  }
    if (n >= 1<< 2) { n >>= 2;  p += 2;  }
    if (n >= 1<< 1) {           p += 1; }
    return p;
}

void dfs(int i, int l) {
    L[i] = l;
    for (int j = 0; j < (int)children[i].size(); j++) {
        dfs(children[i][j], l + 1);
    }
}

int lca(int p, int q) {
    // ensure node p is at least as dep as node q.
    if (L[p] < L[q])
        swap(p, q);

    for (int i = log_num_nodes; i >= 0; i--) {
        if (L[p] - (1 << i) >= L[q])
            p = A[p][i];
    }

    if (p == q)
        return p;

    for (int i = log_num_nodes; i >= 0; i--) {
        if (A[p][i] != -1 && A[p][i] != A[q][i]) {
            p = A[p][i];
            q = A[q][i];
        }
    }
    return A[p][0];
}

int main() {
    log_num_nodes = lb(num_nodes);
    
    for (int i = 0; i < num_nodes; i++) {
        int p; scanf("%d", &p);
        A[i][0] = p; // parent of node i is node p
        if (p != -1)
            children[p].push_back(i);
        else
            root = i;
    }

    for (int j = 1; j <= log_max_nodes; j++) {
        for (int i = 0; i < num_nodes; i++) {
            if (A[i][j-1] != -1)
                A[i][j] = A[A[i][j-1]][j-1];
            else
                A[i][j] = -1;
        }
    }

    dfs(root, 0);
}

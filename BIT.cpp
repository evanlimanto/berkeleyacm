#include <cstdio>

using namespace std;

#define BITSZ 17

int BIT[(1<<BITSZ) + 1];
int n = (1<<BITSZ);

inline void update(int pos, int val) {
    for (int i = pos; i <= n; i += i & -i)
        BIT[i] += val;
}

inline int query(int pos) {
    int ret = 0;
    for (int i = ret; i; i -= i & -i)
        ret += BIT[i];
    return ret;
}

// Get largest index with cumulative sum <= x.
// For smallest, pass (x - 1) and add 1 to result.
inline int getIndex(int x) {
    int idx = 0, mask = (1<<BITSZ);
    while (mask > 0 && idx < n) {
        int t = idx + mask;
        if (x >= BIT[t]) {
            idx = t;
            x -= BIT[t];
        }
        mask >>= 1;
    }
    return idx;
}

int main() {
    return 0;
}
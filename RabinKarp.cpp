#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <queue>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long LL;
typedef pair<int, int> pii; 

const int INF = 1000 * 1000 * 1000;
const LL LLINF = 1000000000000000000LL;

#define mp make_pair
#define pb push_back

const LL MOD = 1000000009;
const LL P = 2;

int r1, c1, r2, c2;
char arr1[2005][2005];
char arr2[2005][2005];
LL hash2[2005][2005];
int xx[2005][2005];
int yy[2005][2005];
LL prec[4000005];

inline LL update(LL old, int len, LL rem, LL add, int primeEx) {
	LL val = old - prec[len - primeEx] * rem;
	val %= MOD;
	val *= prec[primeEx];
	val %= MOD;
	val += add;
	return val % MOD;
}

int main() {

	prec[0] = 1;
	for (int i = 1; i <= 4000000; i++) {
		prec[i] = prec[i-1] * P;
		prec[i] %= MOD;
	}

	scanf("%d %d %d %d",&r1,&c1,&r2,&c2);

	for (int i = 1; i <= r1; i++) {
		for (int j = 1; j <= c1; j++) {
			register int ch = 0;
			while (ch != 'o' && ch != 'x') ch = getchar();
			xx[i][j] = (ch == 'o');
		}
	}

	for (int i = 1; i <= r2; i++) {
		for (int j = 1; j <= c2; j++) {
			register int ch = 0;
			while (ch != 'o' && ch != 'x') ch = getchar();
			yy[i][j] = (ch == 'o');
		}
	}

	LL hash1 = 0;
	for (int i = 1; i <= r1; i++) {
		for (int j = 1; j <= c1; j++) {
			hash1 = update(hash1, 1, 0, xx[i][j], 1);
		}
	}

	for (int i = 1; i <= r2; i++) {
		LL temp = 0;
		for (int j = 1; j <= c2; j++) {
			temp = update(temp, c1, (j > c1) ? yy[i][j - c1] : 0, yy[i][j], 1);
			if (j >= c1) {
				hash2[i][j + 1 - c1] = temp;
			}
		}
	}

	int ans = 0;
	for (int j = 1; j <= c2 - c1 + 1; j++) {
		LL temp = 0;
		for (int i = 1; i <= r2; i++) {
			temp = update(temp, r1 * c1, (i > r1) ? hash2[i - r1][j] : 0, hash2[i][j], c1);
			if (i >= r1 && temp == hash1) {
				ans++;
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}
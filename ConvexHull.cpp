#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

typedef double T;
const T EPS = 1e-7;

// uncomment to remove redundant points 
#define REDUNDANT

struct PT {
	T x, y;
	PT() {}
	PT(T x, T y) : x(x), y(y) {}
	bool operator<(const PT &r) const { return mp(y, x) < mp(r.y, r.x); }
	bool operator==(const PT &r) const { return mp(y,x) == mp(r.y, r.x); }
};

T cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
T area2(PT a, PT b, PT c) { return cross(a, b) + cross(b, c) + cross(c, a); }

#ifdef REDUNDANT
bool bt(const PT &a, const PT &b, const PT &c) {
	return fabs(area2(a, b, c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0;
}
#endif

// takes in a vector of points and returns the convex hull
void CHull(vector<PT> &pts) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<PT> up, dn;
	for (int i = 0; i < pts.size(); i++) {
		while (up.size() > 1 && area2(up[up.size() - 2], up.back(), pts[i]) >= 0) up.pop_back();
		while (dn.size() > 1 && area2(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) dn.pop_back();
		up.pb(pts[i]);
		dn.pb(pts[i]);
	}
	pts = dn;
	for (int i = (int)up.size() - 2; i > 0; i--) pts.pb(up[i]);

#ifdef REDUNDANT
	if (pts.size() <= 2) return;
	dn.clear();
	dn.pb(pts[0]);
	dn.pb(pts[1]);
	for (int i = 2; i < pts.size(); i++) {
		if (bt(dn[dn.size() - 2], dn[dn.size() - 1], pts[i])) dn.pop_back();
		dn.pb(pts[i]);
	}
	if (dn.size() >= 3 && bt(dn.back(), dn[0], dn[1])) {
		dn[0] = dn.back();
		dn.pop_back();
	}
	pts = dn;
#endif
}

// SOLVE SPOJ #26

#include <map>

double dist(PT a, PT b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

int main() {
	int t;
	scanf("%d", &t);
	for (int c = 0; c < t; c++) {
		int n;
		scanf("%d", &n);
		vector<PT> v(n);
		for (int i = 0; i < n; i++) scanf("%lf%lf", &v[i].x, &v[i].y);
		vector<PT> h(v);
		map<PT,int> index;
		for (int i = n - 1; i >= 0; i--) index[v[i]] = i + 1;
		CHull(h);

		double len = 0;
		for (int i = 0; i < h.size()- 1; i++) {
			len += dist(h[i], h[i+1]);
		}
		len += dist(h[0], h[h.size() - 1]);

		if (c > 0) puts("");

		printf("%.2f\n", len);
		for (int i = 0; i < h.size(); i++) {
			if (i > 0) printf(" ");
			printf("%d", index[h[i]]);
		}
		puts("");
	}
}

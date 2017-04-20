#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
typedef long long LL;

int n, it, linesit, pt;
pair<LL, LL> lines[50005];
pii points[50005], pts[50005];
inline bool bad(const pair<LL, LL> &l1, const pair<LL, LL> &l2, const pair<LL, LL> &l3) {
  return (l3.second - l1.second) * (l1.first - l2.first) < (l2.second - l1.second) * (l1.first - l3.first);
}

inline void add(LL m, LL c) {
  if (linesit == 0) lines[linesit++] = make_pair(m, c);
  else {
    pair<LL, LL> cur_line = make_pair(m, c);
    while (linesit >= 2 && bad(lines[linesit-2], lines[linesit-1], cur_line)) {
      linesit--;
    }
    lines[linesit++] = cur_line;
  }
}

LL query(LL x) {
  pt = min(pt, linesit - 1);
  while (pt + 1 < linesit) {
    if (lines[pt].first * x + lines[pt].second >
        lines[pt+1].first * x + lines[pt+1].second)
      ++pt;
    else
      break;
  }
  return lines[pt].first * x + lines[pt].second;
}

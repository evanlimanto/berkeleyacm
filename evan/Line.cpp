#include <utility>

using namespace std;

#define mp make_pair
typedef pair<int, int> pii;

int gcd(int a, int b) {
  if (a < 0) return gcd(-a, b);
  if (b < 0) return gcd(a, -b);
  if (b == 0) return a;
  return gcd(b, a%b);
}

struct Line {
  int a, b, c; // ax + by = c
  void normalize() {
    if (a < 0 || (a == 0 && b < 0) || (a == 0 && b == 0 && c < 0)) {
      a = -a;
      b = -b;
      c = -c;
    }
    int g = gcd(a, gcd(b, c));
    a /= g;
    b /= g;
    c /= g;
  }

  // perpendicular bisector
  Line(pii p1, pii p2) {
    pii mid = mp((p1.first + p2.first)/2, (p1.second + p2.second)/2);

    a = p2.first - p1.first;
    b = p2.second - p1.second;
    c = -(a * mid.first + b * mid.second);

    normalize();
  }

  // line
  Line(pii p1, pii p2, int dum) {
    a = p2.second - p1.second;
    b = p2.first - p1.first;
    c = -(a * p1.first + b * p1.second);

    normalize();
  }

  bool on_line(pii p) const {
    long long res = (long long)p.first * a;
    res += (long long)p.second * b;
    res += c;
    return (res == 0);
  }

  bool operator==(const Line &L) const {
    return a == L.a && b == L.b && c == L.c;
  }

  bool operator<(const Line &L) const {
    if (a != L.a) return a < L.a;
    if (b != L.b) return b < L.b;
    return c < L.c;
  }
};

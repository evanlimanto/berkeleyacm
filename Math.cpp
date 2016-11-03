#include <tuple>
#include <vector>
#include <iostream>
using namespace std;
typedef vector<int> VI;
typedef tuple<int,int,int> TIII;
typedef pair<int, int> PII;

// return smallest positive number equiv to a % b
int mod(int a, int b) {
  return ((a%b) + b) % b;
}

// return the gcd of a and b
int gcd(int a, int b) {
  while (b) {
    int t = a % b;
    a = b;
    b = t;
  }
  return a;
}

// lcm(a, b)
int lcm(int a, int b) {
  return a/gcd(a,b)*b;
}

// a^b mod m via successive squaring
int pmod(int a, int b, int m) {
  int p = 1;
  while (b) {
    if (b & 1) p = mod(p*a, m);
    a = mod(a*a, m);
    b >>= 1;
  }
  return p;
}

// returns a tuple of 3 ints containing d, x, y s.t. d = a * x + b * y
TIII egcd(int a, int b) {
  int x, xx, y, yy;
  xx = y = 0; yy = x = 1;
  while (b) {
    int q = a / b;
    int t = b; b = a % b; a = t;
    t = xx; xx = x - q*xx; x = t;
    t = yy; yy = y - q*yy; y = t;
  }
  return TIII(a, x, y);
}

// returns all solutions to ax = b (mod n)
VI mod_solve(int a, int b, int n) {
  VI ret;
  int g,x;
  tie(g,x,ignore) = egcd(a, n);
  if (!(b%g)) {
    x = mod(x*(b/g), n);
    for (int i = 0; i < g; i++)
      ret.push_back(mod(x + i*(n/g), n));
  }
  return ret;
}

// modular inverse of a mod n, or -1 if gcd(a, n) != 1
int minv(int a, int n) {
  int g,x;
  tie(g,x,ignore) = egcd(a, n);
  if (g > 1) return -1;
  return mod(x, n);
}

PII crt(int m1, int r1, int m2, int r2) {
  int g, s, t;
  tie(g,s,t) = egcd(m1, m2);
  if (r1 % g != r2 % g) return {0, -1};
  return {mod(s*r2*m1 + t*r1*m2, m1*m2)/g, m1*m2/g};
}

PII crt(const VI &m, const VI &r) {
  PII ret = {r[0], m[0]};
  for (int i = 1; i < m.size(); i++) {
    ret = crt(ret.second, ret.first, m[i], r[i]);
    if (ret.second == -1) break;
  }
  return ret;
}

/*
Multiplying nCr quickly:

Lucas's Theorem reduces nCr % M to

(n0Cr0 % M) (n1Cr1 % M) ... (nkCrk % M)

(nknk-1...n0) is the base M representation of n
(rkrk-1...r0) is the base M representation of r
*/

int main() {
  cout << "expect 2" << endl;
  cout << gcd(14, 30) << endl;

  int g, x, y;
  tie(g, x, y) = egcd(14, 30);
  cout << "expect 2 -2 1" << endl;
  cout << g << " " << x << " " << y << endl;

  VI sols = mod_solve(14, 30, 100);
  cout << "expect 95 451" << endl;
  for (auto i : sols) {
    cout << i << " ";
  }
  cout << endl;

  cout << "expect 8" << endl;
  cout << minv(8, 9) << endl;

  PII ret = crt({3,5,7}, {2,3,2});
  cout << "expect 23 105" << endl;
  cout << ret.first << " " << ret.second << endl;
}

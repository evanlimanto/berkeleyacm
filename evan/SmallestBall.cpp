#include <cstring>
#include <cmath>

const int N = 105;
int n;
double x[N], y[N], z[N], X, Y, Z, radius;

inline double sqr(double x) {
  return x * x;
}

void minball() {
  double P = 0.1, d;
  X = Y = Z = 0.0;
  for (int i = 0; i < n; i++) {
    X += x[i];
    Y += y[i];
    Z += z[i];
  }
  X /= n; Y /= n; Z /= n;
  for (int i = 0; i < 10000; i++) {
    double maxd = -1.0;
    int pt = 0;
    for (int j = 0; j < n; j++) {
      d = sqr(X - x[j]) + sqr(Y - y[j]) + sqr(Z - z[j]);
      if (d > maxd) pt = j, maxd = d;
    }
    X += (x[pt] - X) * P;
    Y += (y[pt] - Y) * P;
    Z += (z[pt] - Z) * P;
    P *= 0.999;
  }
  radius = sqrt(d);
}

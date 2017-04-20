#include <cmath>
#include <iostream>
#include <random>

using namespace std;

const double eps = 1e-8;
int dcmp(double x) { return fabs(x) <= eps ? 0 : (x < 0 ? -1 : 1); }

struct Point3 {
  Point3(double x, double y, double z) : x(x), y(y), z(z) {}
  double x, y, z;
  Point3 operator- (Point3 other) const {
    other.x = x - other.x;
    other.y = y - other.y;
    other.z = z - other.z;
    return other;
  }
};
typedef Point3 Vector3;

double Dot(const Vector3& A, const Vector3& B)
{ return A.x*B.x + A.y*B.y + A.z*B.z; }

double Length(const Vector3& A)
{ return sqrt(Dot(A, A)); }

double Angle(const Vector3& A, const Vector3& B)
{ return acos(Dot(A, B) / Length(A) / Length(B)); }

Vector3 Cross(const Vector3& A, const Vector3& B) {
  return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

double Area2(Point3 A, Point3 B, Point3 C)
{ return Length(Cross(B-A, C-A)); }

double Volume6(Point3 A, Point3 B, Point3 C, Point3 D)
{ return Dot(D-A, Cross(B-A, C-A)); }

double rand01() { return rand() / (double)RAND_MAX; }

double randeps() { return (rand01() - 0.5) * eps; }

Point3 add_noise(const Point3 &p) {
  return Point3(p.x + randeps(),
                p.y + randeps(), p.z + randeps());
}

struct Face {
  int v[3];
  Face(int a, int b, int c) {
    v[0] = a; v[1] = b; v[2] = c;
  }
  Vector3 Normal(const vector<Point3> &P) const
  { return Cross(P[v[1]] - P[v[0]], P[v[2]] - P[v[0]]); }
  int CanSee(const vector<Point3> &P, int i) const {
    return Dot(P[i] - P[v[0]], Normal(P)) > 0;
  } // whether f can see P[i]
  double area(const vector<Point3> &P) const {
    return Area2(P[v[0]], P[v[1]], P[v[2]]) * 0.5;
  }
  double volume_comp(const vector<Point3> &P) const {
    Vector3 n = Normal(P);
    double len = Length(n);
    n.x /= len; n.y /= len; n.z /= len;
    return Dot(n, P[v[0]]) * area(P);
  }
};

// Incremental Algorithm for Convex Hull.
// Assume no 4 points coplanar. Need add_noise otherwise.
vector<Face> CH3D(const vector<Point3> &P) {
  int n = (int)P.size();
  vector<vector<int> > vis(n);
  for (int i = 0; i < n; i++) vis[i].resize(n);
  vector<Face> cur;
  cur.push_back(Face(0, 1, 2));
  cur.push_back(Face(2, 1, 0));
  for (int i = 3; i < n; i++) {
    vector<Face> next;
    for (int j = 0; j < (int)cur.size(); j++) {
      Face &f = cur[j]; int res = f.CanSee(P, i);
      if (!res) next.push_back(f);
      for (int k = 0; k < 3; k++)
        vis[f.v[k]][f.v[(k+1)%3]] = res;
    } // compute whether it can be seen on the left side
    for (int j = 0; j < (int)cur.size(); j++) {
      for (int k = 0; k < 3; k++) {
        int a = cur[j].v[k], b = cur[j].v[(k+1)%3];
        if (vis[a][b] != vis[b][a] && vis[a][b])
          next.push_back(Face(a, b, i));
      } // (a, b) is the separating line
    }
    cur = next;
  }
  return cur;
}

double HullArea(const vector<Point3> &points, const vector<Face> &hull) {
  double area = 0.0;
  for (int i = 0; i < (int)hull.size(); i++) {
    area += hull[i].area(points);
  }
  return area;
}

double HullVolume(const vector<Point3> &points, const vector<Face> &hull) {
  double volume = 0.0;
  for (int i = 0; i < (int)hull.size(); i++) {
    volume += hull[i].volume_comp(points);
  }
  return volume / 3.0;
}

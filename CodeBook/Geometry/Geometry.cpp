#include <bits/stdc++.h>
using namespace std;
typedef complex<double> PT;

const double eps = 1e-9;
#define A first
#define B second
#define EQ(a, b) (fabs((a) - (b)) <= eps) /* equal to */
#define LT(a, b) ((a) < (b) - eps)        /* less than */
#define GT(a, b) ((a) > (b) + eps)        /* greater than */
#define LT(a, b) ((a) < (b) - eps)         /* less than */
#define LE(a, b) ((a) <= (b) + eps)        /* less than or equal to */
#define NE(a, b) (fabs((a) - (b)) > eps)  /* not equal to */

#define X real()
#define Y imag()

double dot(const PT& p, const PT& q) { return real(conj(p) * q); }
double cross(const PT& p, const PT& q) { return imag(conj(p) * q); }

// rotate PT a around PT o by th radians
PT rotate_ccw(const PT& a, const PT& o, double th) {
    return (a-o) * polar(1.0, th) + o;
}

//  does p -> q -> r rotates CCW
bool is_ccw(const PT& p, const PT& q, const PT& r) {
    return cross(q - p, r - p) > eps;
}

// angle to a, around b, from c, CCW + CW -
double angle(const PT& a, const PT& b, const PT& c) {
    return remainder(arg(a-b) - arg(c-b), 2.0 * M_PI);
}

//  are a, b, c collinear
bool is_collinear(const PT& a, const PT& b, const PT& c) {
    return abs(cross(b - a, c - a)) < eps;
}

//  whether lines a-b and c-d are parallel (or collinear)
bool is_parallel(const PT& a, const PT& b, const PT& c, const PT& d) {
    return abs(cross(b - a, c - d)) < eps;
}

//  intersection of lines a1-a2 and b1-b2
bool line_line(PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (abs(d) < eps) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

// project PT p on line (0,0) - v
PT project(const PT& p, const PT& v) {
    return v * dot(p, v) / norm(v);
}

// project PT p onto line a, b
PT project(const PT& p, const PT& a, const PT& b) {
    return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}

//  nearest PT to p, on segment a-b
PT nearest_on_segment(const PT& p, const PT& a, const PT& b) {
    double r = dot(b - a, b - a);
    if (abs(r) < eps) return a;
    r = dot(p - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a)*r;
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
    double r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a)*r;
}

//  whether p is on segment a-b
bool is_on_segment(const PT& p, const PT& a, const PT& b) {
    return abs(abs(a - p) + abs(b - p) - abs(a - b)) < eps;
}

// specifically not collinear segments
bool segments_intersect(const PT& a, const PT& b, const PT& p, const PT& q) {
  PT isect;
  if (line_line(a, b, p, q, isect)) {
    return is_on_segment(isect, a, b) && is_on_segment(isect, p, q);
  } else {
    return false;
  }
}

//  reflect p around line a-b
PT reflect(const PT& p, const PT& a, const PT& b) {
    PT z = p - a;
    PT w = b - a;
    return conj(z / w) * w + a;
}

//  whether PT a is on boundary of simple polygon p
bool is_on_polygon(const PT& a, const vector<PT> &p) {
    for (int i = 0; i < (int)p.size(); i++)
        if (is_on_segment(a, p[i], p[(i + 1) % (int)p.size()]))
            return true;
    return false;
}

// O(n)
//  whether PT a is inside a simple polygon p
bool is_in_polygon(const PT& a, const vector<PT> &p) {
    double sum = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        sum += angle(p[i], a, p[(i + 1) % (int)p.size()]);
    }
    return abs(abs(sum) - 2*M_PI) < eps;
}

// O(log n) convex polygon
bool in_polygon(const vector<PT>& v, const PT& p) {
  if (cross(v[1] - v[0], p - v[0]) < -eps ||
      cross(v[0] - v.back(), p - v.back()) < -eps) {
    return false;
  }

  int l = 0, r = v.size() - 1;
  while (l != r - 1) {
    int mid = (l + r) / 2;
    if (cross(v[mid] - v[0], p - v[0]) > 0) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return cross(v[r] - v[l], p - v[l]) > -eps;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool simple(const vector<PT> &p) {
  for (int i = 0; i < p.size(); i++) {
    for (int k = i + 1; k < p.size(); k++) {
      int j = (i + 1) % p.size();
      int l = (k + 1) % p.size();
      if (i == l || j == k) continue;
      if (segments_intersect(p[i], p[j], p[k], p[l]))
	return false;
    }
  }
  return true;
}

// returns true if we always make the same turn while examining
// all the edges of the polygon one by one
bool is_convex(const vector<PT> &P) {
    int sz = (int)P.size();
    if (sz <= 3) return false;
    bool isLeft = is_ccw(P[0], P[1], P[2]);
    for (int i = 1; i < sz-1; i++)
        if (is_ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
        return false;
    return true;
}

//  area of a simple polygon p
double area_polygon(const vector<PT> &p) {
    double area = 0;
    for (int i = 0; i < (int)p.size(); i++)
        area += cross(p[i], p[(i + 1) % (int)p.size()]);
    return abs(area) / 2.0;                                             //  CCW + CW -
}

//  area of triangle using Heron's formula
double area_heron(double x, double y, double z) {
    double s = 0.5 * (x + y + z);
    return sqrt(s) * sqrt(s - x) * sqrt(s - y) * sqrt(s - z);
}

//  radius of the (inner and outer) fourth circle in a set tangent at six distinct PTs using Descartes's theorem
pair<double, double> kissing_circle(double r1, double r2, double r3) {
    double k1 = 1 / r1, k2 = 1 / r2, k3 = 1 / r3;
    double s1 = k1 + k2 + k3;
    double s2 = 2 * sqrt(k1 * k2 + k2 * k3 + k3 * k1);
    return make_pair(1/(s1 + s2), 1/(s1 - s2));         //  2nd may be negative showing including circle
}

template<class It> PT centroid(It lo, It hi) {
  if (lo == hi) return PT(0, 0);
  double xtot = 0, ytot = 0, cnt = hi - lo;
  for (; lo != hi; ++lo) {
    xtot += lo->X;
    ytot += lo->Y;
  }
  return PT(xtot / cnt, ytot / cnt);
}

// triangle stuff ------------------

bool canFormTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

double area(double x1, double y1, double x2, double y2, double x3, double y3) {
    return 0.5 * (x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2);
}

double area(double ab, double bc, double ca) { // Heron's fomula
    double s = 0.5 * (ab + bc + ca);
    return sqrt(s) * sqrt(s - ab) * sqrt(s - bc) * sqrt(s - ca);
}

double area(PT a, PT b, PT c) {
    return area(dist(a, b), dist(b, c), dist(c, a));
}

double perimeter(double ab, double ac, double bc) {
    return ab + bc + ac;
}

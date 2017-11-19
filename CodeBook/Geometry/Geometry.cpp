#include <bits/stdc++.h>
using namespace std;
typedef complex<double> PT;

/* TODO : Centroid
          Circle Tangents
*/

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

//  whether p is on segment a-b
bool is_on_segment(const PT& p, const PT& a, const PT& b) {
    return abs(abs(a - p) + abs(b - p) - abs(a - b)) < eps;
}

//  reflect p around line a-b
PT reflect(const PT& p, const PT& a, const PT& b) {
    PT z = p - a;
    PT w = b - a;
    return conj(z / w) * w + a;
}

//  compute center of circle given three PTs
PT circle_center(const PT& a, const PT& b, const PT& c) {
    PT ab = (a + b) / double(2);
    PT ac = (a + c) / double(2);
    PT center;
    line_line(ab, ab + rotate_ccw(a - b, PT(0, 0), M_PI/2), ac, ac + rotate_ccw( a - c, PT(0 ,0), M_PI/2), center);
    return center;
}

//  intersection(s) of line a-b with circle @ c with radius r > 0
vector <PT> line_circle(PT a, PT b, PT c, double r) {
    vector<PT> ret;
    b = b - a;
    a = a - c;
    double A = norm(b);
    double B = dot(a, b);
    double C = norm(a) - r*r;
    double D = B*B - A*C;
    if (D < -eps) return ret;
    ret.push_back(c + a + b*(-B + sqrt(D + eps)) / A);
    if (D > eps)
        ret.push_back(c + a + b*(-B - sqrt(D)) / A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> circle_circle(PT c1, double r1, PT c2, double r2){
    vector<PT> ret;
    double d = abs(c1-c2);
    if (d > r1 + r2 || d + min(r1, r2) < max(r1, r2)) return ret;
    double x = (d*d - r2*r2 + r1*r1) / (2 * d);
    double y = sqrt(r1*r1 - x*x);
    PT v = (c2 - c1) / d;
    ret.push_back(c1 + v*x + rotate_ccw(v, PT(0,0), M_PI/2)*y);
    if (y > 0)
        ret.push_back(c1 + v*x - rotate_ccw(v, PT(0,0), M_PI/2)*y);
    return ret;
}

// Find tangent lines to circle center a and radius R1
// and circle with center b and radius R2.
// where R2 > R1
typedef pair<PT, PT> Segment;
pair<Segment,Segment> solve(PT a, double R1, PT b, double R2){
  PT d = b.c - a.c;
  double theta = acos((R2 - R1) / abs(d));

  Segment a1, a2;
  a1.A = a.c + d/PT(abs(d),0.0)*polar(1.0,theta)*R2;
  a2.A = a.c + d/PT(abs(d),0.0)*polar(1.0,-theta)*R2;

  a1.B = b.c + d/PT(abs(d),0.0)*polar(1.0,theta)*R1;
  a2.B = b.c + d/PT(abs(d),0.0)*polar(1.0,-theta)*R1;
  return make_pair(a1,a2);
}

//  whether PT a is on boundary of simple polygon p
bool is_on_polygon(const PT& a, const vector<PT> &p) {
    for (int i = 0; i < (int)p.size(); i++)
        if (is_on_segment(a, p[i], p[(i + 1) % (int)p.size()]))
            return true;
    return false;
}

//  whether PT a is inside a simple polygon p
bool is_in_polygon(const PT& a, const vector<PT> &p) {
    double sum = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        sum += angle(p[i], a, p[(i + 1) % (int)p.size()]);
    }
    return abs(abs(sum) - 2*M_PI) < eps;
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

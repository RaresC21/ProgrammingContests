#include <bits/stdc++.h>
using namespace std;

/*

Given a range of points on the 2D cartesian plane, determine
the equation of the circle with smallest possible area which
encloses all of the points. Note: in an attempt to avoid the
worst case, the circles are randomly shuffled before the
algorithm is performed. This is not necessary to obtain the
correct answer, and may be removed if the input order must
be preserved.

Time Complexity: O(n) average on the number of points given.

REQUIRES:
line_line
circle_center (for both three points and diameter made from two points)

*/


typedef complex<double> PT;
typedef pair<PT, double> circle;
#define X real()
#define Y imag()

#define A first
#define B second

const double eps = 1e-9;

#define LE(a, b) ((a) <= (b) + eps)       /* less than or equal to */
#define MP make_pair

double cross(PT a, PT b) { return imag(conj(a)*b); }

// rotate PT a around PT o by th radians
PT rotate_ccw(const PT& a, const PT& o, double th) {
    return (a-o) * polar(1.0, th) + o;
}

//  intersection of lines a1-a2 and b1-b2
bool line_line(PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (abs(d) < eps) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

// determine if point p is inside circle c.
bool contains(const circle& c, const PT& p) {
  return LE(abs(c.A - p), c.B);
}

//  compute center of circle given three points
pair<PT, double> circle_center(const PT& a, const PT& b, const PT& c) {
    PT ab = (a + b) / double(2);
    PT ac = (a + c) / double(2);
    PT center;
    line_line(ab, ab + rotate_ccw(a - b, PT(0, 0), M_PI/2), ac, ac + rotate_ccw( a - c, PT(0 ,0), M_PI/2), center);
    return MP(center, abs(center - a));
}

//  compute center of circle given oppsite diametral points a and b.
pair<PT, double> circle_center(const PT& a, const PT& b) {
  PT cntr = (a + b) * (1/2.0);
  double r = abs(a - b) * (1/2.0);
  return MP(cntr, r);
}

template<class It> circle smallest_circle(It lo, It hi) {
  if (lo == hi) return circle_center(0, 0, 0);
  if (lo + 1 == hi) return circle_center(*lo, 0);
  random_shuffle(lo, hi);
  circle res = circle_center(*lo, *(lo + 1));
  for (It i = lo + 2; i != hi; ++i) {
    if (contains(res, *i)) continue;
    res = circle_center(*lo, *i);
    for (It j = lo + 1; j != i; ++j) {
      if (contains(res, *j)) continue;
      res = circle_center(*i, *j);
      for (It k = lo; k != j; ++k)
        if (!contains(res, *k)) res = circle_center(*i, *j, *k);
    }
  }
  return res;
}

int main() {

  int N; cin >> N;
  vector<PT> v(N);
  for (int i = 0; i < N; i++) {
    double x, y; cin >> x >> y;
    v[i] = PT(x, y);
  }
  circle res = smallest_circle(v.begin(), v.end());
  cout << 2 * res.B << "\n";

  return 0;
}
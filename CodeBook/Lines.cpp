#include <bits/stdc++.h>
using namespace std;
/*
A 2D line is expressed in the form Ax + By + C = 0.
Given the line form, we can get two points on the line.
*/

const double eps = 1e-8;
#define MP make_pair
#define EQ(a, b) (fabs((a) - (b)) <= eps) /* equal to */
#define LT(a, b) ((a) < (b) - eps)        /* less than */
#define GT(a, b) ((a) > (b) + eps)        /* greater than */
#define LT(a, b) ((a) < (b) - eps)         /* less than */
#define LE(a, b) ((a) <= (b) + eps)        /* less than or equal to */
#define NE(a, b) (fabs((a) - (b)) > eps)  /* not equal to */

typedef complex<double> PT;
#define X real()
#define Y imag()

struct line {
  double a, b, c;
  line(): a(0), b(0), c(0) {} //invalid or uninitialized line
  line(double A, double B, double C) : a(A), b(B), c(C) {}

  //solve for y, given x
  //for vertical lines, either +inf, -inf, or nan is returned
  double y(const double& x) const {
    return (-c - a * x) / b;
  }

  pair<PT, PT> get_points() {
    PT p1, p2;
    if (EQ(b, 0)) { // vertical line
      p1 = PT(-c/a, 0);
      p2 = PT(-c/a, 10);
    } else {
      p1 = PT(0, y(0));
      p2 = PT(10, y(10));
    }
    return MP(p1, p2);
  }
};


int main() {

  // random
  line l1 = line(1,2,3);
  pair<PT, PT> p = l1.get_points();
  cout << p.first << " " << p.second << "\n";

  // vertical
  line l2 = line(1,0,3);
  p = l2.get_points();
  cout << p.first << " " << p.second << "\n";

  // horizontal
  line l3 = line(0,2,3);
  p = l3.get_points();
  cout << p.first << " " << p.second << "\n";

  return 0;
}
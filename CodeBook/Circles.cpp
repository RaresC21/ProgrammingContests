/*

A 2D circle with center at (h, k) and a radius of r can be expressed by
the relation (x - h)^2 + (y - k)^2 = r^2. In the following definition,
the radius used to construct it is forced to be a positive number.

*/

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> PT;
const double eps = 1e-9;
#define A first
#define B second


#define EQ(a, b) (fabs((a) - (b)) <= eps) /* equal to */
#define GT(a, b) ((a) > (b) + eps)        /* greater than */
#define LE(a, b) ((a) <= (b) + eps)       /* less than or equal to */

#define X real()
#define Y imag()

struct circle {
  double h, k, r;
  PT c;
  circle(): h(0), k(0), r(0) {c = PT(0,0); }
  circle(const double & R): h(0), k(0), r(fabs(R)) {}
  circle(const PT & o, const double & R): h(o.X), k(o.Y), r(fabs(R)) { c = o; }
  circle(const double & H, const double & K, const double & R):
    h(H), k(K), r(fabs(R)) { c = PT(h, k); }

  //circumcircle with the diameter equal to the distance from a to b
  circle(const PT & a, const PT & b) {
    h = (a.X + b.X) / 2.0;
    k = (a.Y + b.Y) / 2.0;
    r = abs(PT(a.X - h, a.Y - k));
    this->c = PT(h, k);
  }

  //circumcircle of 3 PTs - throws exception if abc are collinear/equal
  circle(const PT & a, const PT & b, const PT & c) {
    double an = norm(b - c);
    double bn = norm(a - c);
    double cn = norm(a - b);
    double wa = an * (bn + cn - an);
    double wb = bn * (an + cn - bn);
    double wc = cn * (an + bn - cn);
    double w = wa + wb + wc;
    if (fabs(w) < eps)
      throw std::runtime_error("No circle from collinear PTs.");
    h = (wa * a.X + wb * b.X + wc * c.X) / w;
    k = (wa * a.Y + wb * b.Y + wc * c.Y) / w;
    r = abs(a - PT(h, k));
    this->c = PT(h, k);
  }

  //circle from 2 PTs and a radius - many possible edge cases!
  //in the "normal" case, there will be 2 possible circles, one
  //centered at (h1, k1) and the other (h2, k2). Only one is used.
  //note that (h1, k1) equals (h2, k2) if dist(a, b) = 2 * r = d
  circle(const PT & a, const PT & b, const double & R) {
    r = fabs(R);
    if (LE(r, 0) && a == b) { //circle is a PT
      h = a.X;
      k = a.Y;
      return;
    }
    double d = abs(b - a);
    if (EQ(d, 0))
      throw std::runtime_error("Identical PTs, infinite circles.");
    if (GT(d, r * 2.0))
      throw std::runtime_error("PTs too far away to make circle.");
    double v = sqrt(r * r - d * d / 4.0) / d;
    PT m((a.X + b.X) / 2.0, (a.Y + b.Y) / 2.0);
    h = m.X + (a.Y - b.Y) * v;
    k = m.Y + (b.X - a.X) * v;
    this->c = PT(h, k);
    //other answer is (h, k) = (m.x-(a.y-b.y)*v, m.y-(b.x-a.x)*v)
  }

  bool operator == (const circle & c) const {
    return EQ(h, c.h) && EQ(k, c.k) && EQ(r, c.r);
  }

  bool operator != (const circle & c) const {
    return !(*this == c);
  }

  bool contains(const PT & p) const {
    return LE(norm(p - PT(h, k)), r * r);
  }

  bool on_edge(const PT & p) const {
    return EQ(norm(p - PT(h, k)), r * r);
  }

  PT center() const {
    return PT(h, k);
  }
};

//circle inscribed within PTs a, b, and c
circle incircle(const PT & a, const PT & b, const PT & c) {
  double al = abs(b - c);
  double bl = abs(a - c);
  double cl = abs(a - b);
  double p = al + bl + cl;
  if (EQ(p, 0)) return circle(a.X, a.Y, 0);
  circle res;
  res.h = (al * a.X + bl * b.X + cl * c.X) / p;
  res.k = (al * a.Y + bl * b.Y + cl * c.Y) / p;
  res.r = fabs((a.X - c.X) * (b.Y - c.Y) - (a.Y - c.Y) * (b.X - c.X)) / p;
  return res;
}

typedef pair<PT, PT> Segment;
pair<Segment,Segment> solve(circle a, circle b){
  double R2 = a.r;
  double R1 = b.r;
  PT d = b.c - a.c;
  double theta = acos((R2 - R1) / abs(d));

  Segment a1, a2;
  a1.A = a.c + d/PT(abs(d),0.0)*polar(1.0,theta)*R2;
  a2.A = a.c + d/PT(abs(d),0.0)*polar(1.0,-theta)*R2;

  a1.B = b.c + d/PT(abs(d),0.0)*polar(1.0,theta)*R1;
  a2.B = b.c + d/PT(abs(d),0.0)*polar(1.0,-theta)*R1;
  return make_pair(a1,a2);
}

/*** Example Usage ***/

#include <cassert>

int main() {
  circle c(-2, 5, sqrt(10)); //(x+2)^2+(y-5)^2=10
  assert(c == circle(PT(-2, 5), sqrt(10)));
  assert(c == circle(PT(1, 6), PT(-5, 4)));
  assert(c == circle(PT(-3, 2), PT(-3, 8), PT(-1, 8)));
  assert(c == incircle(PT(-12, 5), PT(3, 0), PT(0, 9)));
  assert(c.contains(PT(-2, 8)) && !c.contains(PT(-2, 9)));
  assert(c.on_edge(PT(-1, 2)) && !c.on_edge(PT(-1.01, 2)));
  return 0;
}
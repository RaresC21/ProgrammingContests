#include <bits/stdc++.h>
using namespace std;

typedef pair<double> circle;

// determine if point p is inside circle c.
bool contains(const circle& c, const PT& p) {
  return LE(abs(c.A - p), c.B);
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
    ret.push_back(c + a + b*(-B + sqrt(D)) / A);
    if (D > eps)
        ret.push_back(c + a + b*(-B - sqrt(D)) / A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> circle_circle(const circle& a, const circle& b){
  PT c1 = a.c, c2 = b.c;
  double r1 = a.r, r2 = b.r;
  vector<PT> ret;
  double d = abs(c1-c2);
  if (d > r1 + r2 || d + min(r1, r2) < max(r1, r2)) return ret;
  double x = (d*d - r2*r2 + r1*r1) / (2 * d);
  double y = sqrt(r1*r1 - x*x);
  PT v = (c2 - c1) / d;
  ret.push_back(c1 + v*x + rotate_ccw(v, PT(0,0), PI/2)*y);
  if (y > 0)
      ret.push_back(c1 + v*x - rotate_ccw(v, PT(0,0), PI/2)*y);
  return ret;
}

//  compute center of circle given three points
// assume points are not collinear
pair<PT, double> circle_center(const PT& a, const PT& b, const PT& c) {
    PT ab = (a + b) / double(2);
    PT ac = (a + c) / double(2);
    PT center;
    line_line(ab, ab + rotate_ccw(a - b, PT(0, 0), M_PI/2),
              ac, ac + rotate_ccw(a - c, PT(0 ,0), M_PI/2), center);
    return MP(center, abs(center - a));
}

// given two points on the circle and the radius, find the center.
// set flip to true, to get the second circle.
bool circle_center(PT p1, PT p2, double r, PT &c, bool flip) {
    if (flip) swap(p1, p2);
    double d2 = (p1.X - p2.X) * (p1.X - p2.X) +
        (p1.Y - p2.Y) * (p1.Y - p2.Y);
    double det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    double h = sqrt(det);
    double x = (p1.X + p2.X) * 0.5 + (p1.Y - p2.Y) * h;
    double y = (p1.Y + p2.Y) * 0.5 + (p2.X - p1.X) * h;
    c = PT(x, y);
    return true;
}

//  compute center of circle given oppsite diametral points a and b.
pair<PT, double> circle_center(const PT& a, const PT& b) {
  PT cntr = (a + b) * (1/2.0);
  double r = abs(a - b) * (1/2.0);
  return MP(cntr, r);
}

typedef pair<PT, PT> Segment;
pair<Segment,Segment> outer_tangent(circle a, circle b){
  double R2 = a.B;
  double R1 = b.B;
  PT d = b.A - a.A;
  double theta = acos((R2 - R1) / abs(d));

  Segment a1, a2;
  a1.A = a.A + d/PT(abs(d),0.0)*polar(1.0,theta)*R2;
  a2.A = a.A + d/PT(abs(d),0.0)*polar(1.0,-theta)*R2;

  a1.B = b.A + d/PT(abs(d),0.0)*polar(1.0,theta)*R1;
  a2.B = b.A + d/PT(abs(d),0.0)*polar(1.0,-theta)*R1;
  return make_pair(a1,a2);
}

bool inner_tangent(circle a, circle b, pair<Segment, Segment>& tangents) {
  double d = abs(a.A - b.A);
  double R1 = a.B, R2 = b.B;
  if (d - R1 - R2 < eps) return false;

  double x = d * R1 / (R1 + R2);
  double theta = acos(R1 / x);

  PT p1 = rotate_ccw(b.A, a.A, theta); p1 = a.A + (p1 - a.A) * (R1 / abs(p1 - a.A));
  PT p2 = rotate_ccw(a.A, b.A, theta); p2 = b.A + (p2 - b.A) * (R2 / abs(p2 - b.A));
  tangents.A = mp(p1, p2);

  PT q1 = rotate_ccw(b.A, a.A, -theta); q1 = a.A + (q1 - a.A) * (R1 / abs(q1 - a.A));
  PT q2 = rotate_ccw(a.A, b.A, -theta); q2 = b.A + (q2 - b.A) * (R2 / abs(q2 - b.A));
  tangents.B = mp(q1, q2);
  return true;
}

// find center of a circle of radius R that is tangent to both circles
pair<PT, PT> circle_tangent(circle c1, circle c2, double R) {
  PT a = c1.A, b = c2.A;
  double r1 = c1.B, r2 = c2.B;
  double v = R + r2;
  double u = R + r1;
  double d = abs(a - b);
  double theta = acos((u*u + d*d - v*v) / (2*u*d));

  PT p1 = rotate_ccw(b, a, theta) - a;
  PT p2 = rotate_ccw(b, a, -theta) - a;

  p1 = p1 * (u / abs(p1));
  p2 = p2 * (u / abs(p2));
  return mp(p1 + a, p2 + a);
}

// The Great-Circle Distance between any two points A and B on sphere
// is the shortest distance along a path on the surface of the sphere
double greater_circle_distance(double pLat, double pLong, double qLat, double qLong, double radius) {
    pLat *= PI / 180; pLong *= PI / 180; // conversion from degree to radian
    qLat *= PI / 180; qLong *= PI / 180;
    return radius * acos(cos(pLat)*cos(pLong)*cos(qLat)*cos(qLong) +
                        cos(pLat)*sin(pLong)*cos(qLat)*sin(qLong) +
                        sin(pLat)*sin(qLat));
}

double circle_area(double R) {
    return PI * R*R;
}

// given circle centered at 0,0 with radius R, finds the area that lies to the
// right of the line x = d
double circle_segment_area(double R, double d) {
    if (d == 0) return circle_area(R) / 2;
    double hh = (R*R - d*d);
    double theta = 2 * acos((R*R + d*d - hh) / (2*R*d));
    return R*R * (theta - sin(theta)) / 2;
}

// return volume of cap sphere with radius R, cap height h
double spherical_cap_volume(double R, double h) {
    return PI * h * h * (3.0 * R - h) / 3.0;
}

double spherical_cap_area(double R, double h) {
    return 2 * PI * R * h;
}

double rInCircle(double ab, double bc, double ca) {
    return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca));
}

double rInCircle(PT a, PT b, PT c) {
    return rInCircle(dist(a, b), dist(b, c), dist(c, a));
}

// returns 1 if there is an inCircle center, returns 0 otherwise
// if this function returns 1, ctr will be the inCircle center
// and r is the same as rInCircle
int inCircle(PT p1, PT p2, PT p3, PT &ctr, double &r) {
  r = rInCircle(p1, p2, p3);
  if (fabs(r) < EPS) return 0;                   // no inCircle center

  line l1, l2;                    // compute these two angle bisectors
  double ratio = dist(p1, p2) / dist(p1, p3);
  PT p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
  pointsToLine(p1, p, l1);

  ratio = dist(p2, p1) / dist(p2, p3);
  p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
  pointsToLine(p2, p, l2);

  areIntersect(l1, l2, ctr);           // get their intersection point
  return 1;
}

double rCircumCircle(double ab, double bc, double ca) {
    return ab * bc * ca / (4.0 * area(ab, bc, ca));
}

double rCircumCircle(PT a, PT b, PT c) {
    return rCircumCircle(dist(a, b), dist(b, c), dist(c, a));
}

// returns 1 if there is a circumCenter center, returns 0 otherwise
// if this function returns 1, ctr will be the circumCircle center
// and r is the same as rCircumCircle
int circumCircle(PT p1, PT p2, PT p3, PT &ctr, double &r){
    double a = p2.x - p1.x, b = p2.y - p1.y;
    double c = p3.x - p1.x, d = p3.y - p1.y;
    double e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    double f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    double g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (fabs(g) < EPS) return 0;

    ctr.x = (d*e - b*f) / g;
    ctr.y = (a*f - c*e) / g;
    r = dist(p1, ctr);
    return 1;
}

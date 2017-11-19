#include "bits/stdc++.h"
using namespace std;
#define EPS 1e-9
#define INF 1e100
#define PI acos(-1)

struct PT {
    double x, y;
    PT() {}
    PT(double x, double y, double z = 0) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    bool operator == (PT other) const {
     return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
    PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y, z); }
    PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y, z); }
    PT operator * (double c)     const { return PT(x*c, y*c); }
    PT operator / (double c)     const { return PT(x / c, y / c); }
};

double dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double dist(PT p, PT q) { return sqrt(dist2(p, q)); }
double cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }

// points to lines.
struct line { double a, b, c; };          // a way to represent a line

// create line that passes through points p1 and p2;
// the answer is stored in the third parameter (pass by reference)
void pointsToLine(PT p1, PT p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) {
        l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}

// planes. ---------------------------------------------------------------
struct Plane {
    double a, b, c, d; // ax + by + cz = d;
    Plane (double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}
};

// create a plane from 3 points;
Plane point_to_plane(PT a, PT b, PT c) {
    PT vec1 = a - c;
    PT vec2 = b - c;
    PT cross_ = cross3D(vec1, vec2);
    double d = dot(cross_, vec1);
    return Plane(cross_.x, cross_.y, cross_.z, d);
}

// vector stuff. ---------------------------------
struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(PT a, PT b) {       // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y);
}

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x * s, v.y * s);
}

PT translate(PT p, vec v) {        // translate p according to v
    return PT(p.x + v.x , p.y + v.y);
}

// -------------------------------------------------------------------

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p) { return PT(-p.y, p.x); }
PT RotateCW90(PT p) { return PT(p.y, -p.x); }
PT RotateCCW(PT p, double t) {  // by certain angle t
    return PT(p.x*cos(t) - p.y*sin(t), p.x*sin(t) + p.y*cos(t));
}
// returns true if point r is on the left side of line pq
bool is_ccw(PT p, PT q, PT r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

// get angle formed by vector 0->a and 0->b
double angle(PT a, PT b) {
     return atan2(a.y, a.x) - atan2(b.y, b.x);
}

double angle(PT a, PT o, PT b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}
// returns true if point r is on the same line as the line pq
bool collinear(PT p, PT q, PT r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}


// which side of a line formed by points a,b is point c on?
double point_on_side(PT a, PT b, PT c) {
    return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x));
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
    return a + (b - a)*dot(c - a, b - a) / dot(b - a, b - a);
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

// compute distance from c to segment between a and b
double DistancePointSegment(PT a, PT b, PT c) {
    return dist2(c, ProjectPointSegment(a, b, c));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
    double a, double b, double c, double d)
{
    return fabs(a*x + b*y + c*z - d) / sqrt(a*a + b*b + c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
    return fabs(cross(b - a, c - d)) < EPS;
}

bool areParallel(line l1, line l2) {       // check coefficients a & b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
    return LinesParallel(a, b, c, d)
        && fabs(cross(a - b, a - c)) < EPS
        && fabs(cross(c - d, c - a)) < EPS;
}

bool collinear(int ax, int ay, int bx, int by, int cx, int cy) {
    bool result = false;
    if (ay == by)
        result = (by == cy);
    else if (ax == bx)
        result = (bx == cx);
    else
        result = ((by - ay)*(cx - bx) == (cy - by)*(bx - ax));
    return result;
}

//true if (x2,y2) lies between (x1,y1) and (x3,y3), otherwise false
bool between(double x1, double y1, double x2, double y2, double x3, double y3) {
    bool xbetween = (x1<x3) ? (x1 <= x2 && x2 <= x3) : (x3 <= x2 && x2 <= x1);
    bool ybetween = (y1<y3) ? (y1 <= y2 && y2 <= y3) : (y3 <= y2 && y2 <= y1);
    return xbetween && ybetween && collinear(x1, y1, x2, y2, x3, y3);
}

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, PT &p) {
    if (areParallel(l1, l2)) return false;
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true;
}

// line segment p-q intersect with line A-B.
PT lineIntersectSeg(PT p, PT q, PT A,PT B) {
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
    return PT((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
    if (LinesCollinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
            dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    if (cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
    if (cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
    return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
    b = b - a; d = c - d; c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d) / cross(b, d);
}

// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
    b = (a + b) / 2;
    c = (a + c) / 2;
    return ComputeLineIntersection(b, b + RotateCW90(a - b), c, c + RotateCW90(a - c));
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
    for (int i = 0; i < p.size(); i++)
        if (dist2(ProjectPointSegment(p[i], p[(i + 1) % p.size()], q), q) < EPS)
            return true;
    return false;
}

bool point_in_polygon(PT pt, const vector<PT> &P) {
    double sum = 0;    // assume the first vertex is equal to the last vertex
    for (int i = 0; i < (int)P.size()-1; i++) {
        if (ccw(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]);
        else
            sum -= angle(P[i], pt, P[i+1]);
    }
    return fabs(fabs(sum) - 2*PI) < EPS;
}

// returns true if point is on or inside polygon.
bool PointInPolygon(const vector<PT> &p, PT q) {
    if (PointOnPolygon(p, q)) return true;

    bool c = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        if ((p[i].y <= q.y && q.y < p[j].y ||
            p[j].y <= q.y && q.y < p[i].y) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<PT> cutPolygon(PT a, PT b, const vector<PT> &Q) {
    vector<PT> P;
    for (int i = 0; i < (int)Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i]));
        double left2 = 0;
        if (i != (int)Q.size() - 1)
            left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
        if (left1 > -EPS) P.push_back(Q[i]);
        if (left1 * left2 < -EPS)
            P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front()))
        P.push_back(P.front());
    return P;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> CircleLineIntersection(PT a, PT b, PT c, double r) {
    vector<PT> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r*r;
    double D = B*B - A*C;
    if (D < -EPS) return ret;
    ret.push_back(c + a + b*(-B + sqrt(D + EPS)) / A);
    if (D > EPS)
        ret.push_back(c + a + b*(-B - sqrt(D)) / A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
    vector<PT> ret;
    double d = sqrt(dist2(a, b));
    if (d > r + R || d + min(r, R) < max(r, R)) return ret;
    double x = (d*d - R*R + r*r) / (2 * d);
    double y = sqrt(r*r - x*x);
    PT v = (b - a) / d;
    ret.push_back(a + v*x + RotateCCW90(v)*y);
    if (y > 0)
        ret.push_back(a + v*x - RotateCCW90(v)*y);
    return ret;
}

// This code computes the area or a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.
double ComputeSignedArea(const vector<PT> &p) {
    double area = 0;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

double ComputeArea(const vector<PT> &p) {
    return fabs(ComputeSignedArea(p));
}

PT ComputeCentroid(const vector<PT> &p) {
    PT c(0, 0);
    double scale = 6.0 * ComputeSignedArea(p);
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        c = c + (p[i] + p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<PT> &p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i + 1; k < p.size(); k++) {
            int j = (i + 1) % p.size();
            int l = (k + 1) % p.size();
            if (i == l || j == k) continue;
            if (SegmentsIntersect(p[i], p[j], p[k], p[l]))
                return false;
        }
    }
    return true;
}

// returns true if we always make the same turn while examining
// all the edges of the polygon one by one
bool isConvex(const vector<PT> &P) {
    int sz = (int)P.size();
    if (sz <= 3) return false;
    bool isLeft = is_ccw(P[0], P[1], P[2]);
    for (int i = 1; i < sz-1; i++)
        if (is_ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
        return false;
    return true;
}


// reflect p3 across line formed by p1, p2
PT calc_refl(PT p1, PT p2, PT p3) {
    double delx = p2.x - p1.x;
    double dely = p2.y - p1.y;
    double u = (-delx*(p3.y - p1.y) + dely*(p3.x - p1.x)) / (delx*delx + dely*dely);
    PT ans;
    ans.x = p3.x - dely * 2 * u;
    ans.y = p3.y + delx * 2 * u;
    return ans;
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(PT p, PT q, PT r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
    return false;
}

int orientation(PT p, PT q, PT r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

bool doIntersect(PT p1, PT q1, PT p2, PT q2){
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}

double distToLines(PT a, PT b, PT c, PT d) {
    if (SegmentsIntersect(a, b, c, d))
        return 0;
    double ans = min(DistancePointSegment(c, d, a), DistancePointSegment(c, d, b));
    ans = min(ans, DistancePointSegment(a, b, c));
    ans = min(ans, DistancePointSegment(a, b, d));
    return ans;
}

// trianlge stuff ------------------

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

// circle stuff. ----------------------------

// Descartes Circle Theorem
// given the radii of three circles, determine the radius of the fourth circle
// that is tangent to all three of them.
double descartes_circle(double r1, double r2, double r3) {
    double s1 = 1.0 / r1 + 1.0 / r2 + 1.0 / r3;
    double s2 = 1.0 / (r1*r2) + 1.0 / (r1*r3) + 1.0 / (r2*r3);
    return s1 + sqrt(s2); // substract here if you want internally tangent circle
}

// given points of intersection between two circles, get the centers of the circles.
bool circle2PtsRad(PT p1, PT p2, double r, PT &c, bool flip) {
    if (flip) swap(p1, p2);
    double d2 = (p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y);
    double det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    double h = sqrt(det);
    c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
    return true;          // to get the other center, reverse p1 and p2
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

// returns true if point d is inside the circumCircle defined by a,b,c
int inCircumCircle(PT a, PT b, PT c, PT d) {
  return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
         (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
         (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
         (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}

// Convex Hull. ------------------------------------------

PT pivot;
bool angleCmp(PT a, PT b) { // angle sorting function
    if (collinear(pivot, a, b))
        return dist(pivot, a) < dist(pivot, b);
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<PT> convex_hull(vector<PT> P) {
    int i, j, n = (int)P.size();
    if (n <= 3) {
        if (!(P[0] == P[n - 1])) P.push_back(P[0]);
        return P;
    }

    int P0 = 0;
    for (i = 1; i < n; i++)
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i;

    PT temp = P[0]; P[0] = P[P0]; P[P0] = temp;
    pivot = P[0];
    sort(++P.begin(), P.end(), angleCmp);

    vector<PT> S;
    S.push_back(P[n - 1]);
    S.push_back(P[0]);
    S.push_back(P[1]);
    i = 2;
    while (i < n) {
        j = (int)S.size() - 1;
        if (is_ccw(S[j - 1], S[j], P[i]))
            S.push_back(P[i++]);
        else
            S.pop_back();
    }
    return S;
}

int main() {

    return 0;
}

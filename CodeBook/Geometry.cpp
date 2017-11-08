typedef complex<double> PT;

#define EQ(a, b) (fabs((a) - (b)) <= eps) /* equal to */
#define LT(a, b) ((a) < (b) - eps)        /* less than */
#define GT(a, b) ((a) > (b) + eps)        /* greater than */
#define LT(a, b) ((a) < (b) - eps)         /* less than */
#define LE(a, b) ((a) <= (b) + eps)        /* less than or equal to */
#define NE(a, b) (fabs((a) - (b)) > eps)  /* not equal to */

const double eps = 1e-9;
#define X real()
#define Y imag()

double dot(const PT& p, const PT& q) { return real(conj(p) * q); }
double cross(const PT& p, const PT& q) { return imag(conj(p) * q); }

// rotate point a about point p by theta degrees
PT rotateCCW(PT p, PT a, double theta) {
    return (a-p) * polar(1.0, theta) + p;
}
bool ccw(PT p, PT q, PT r) {
    return cross(q - p, r - p) > eps;
}
// angle of a-b-c
double angle(PT a, PT b, PT c) {
    return abs(remainder(arg(a-b) - arg(c-b), 2.0 * M_PI));
}
bool collinear(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a)) < eps;
}
// project point p onto vector v
PT project(PT p, PT v) {
    return v * dot(p, v) / norm(v);
}
// project point p onto line a, b
PT project(PT p, PT a, PT b) {
    return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}
// check if p is on segment a-b
bool on_line(const PT& a, const PT& b, const PT& p) {
    if (fabs(abs(a - p) + abs(b - p) - abs(a - b)) < eps)
        return true;
    return false;
}
PT reflect(const& PT p, const& PT a, const& PT b) {
    PT z = p - a;
    PT w = b - a;
    return conj(z / w) * w + a;
}
bool lineline(PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (d == 0) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 100005
#define INF 100000000000000009

#define EPS 1e-9
struct PT {
    double x, y, z;
    PT() {}
    PT(double x, double y, double z = 0) : x(x), y(y), z(z) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    bool operator == (PT other) const {
     return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
    PT operator + (const PT &p)  const { return PT(x + p.x, y + p.y, z + p.z); }
    PT operator - (const PT &p)  const { return PT(x - p.x, y - p.y, z - p.z); }
    PT operator * (double c)     const { return PT(x*c, y*c, z*c); }
    PT operator / (double c)     const { return PT(x / c, y / c, z / c); }
};

struct Circle {
    PT center;
    double r;
    Circle() {
        r = 0;
    }
    Circle(PT c, double r) : r(r) {
        center = c;
    }
};

PT origin = PT(0,0);
double R;
Circle ans;

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

double dot(PT p, PT q) { return p.x*q.x + p.y*q.y + p.z*q.z; }
double cross(PT p, PT q) { return p.x*q.y - p.y*q.x; }
PT RotateCCW90(PT p) { return PT(-p.y, p.x); }

double dist(PT p, PT q) {
    double dx = p.x - q.x;
    double dy = p.y - q.y;
    return sqrt(dx * dx + dy * dy);
}

vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
    vector<PT> ret;
    double d = dist(a, b);
    if (d > r + R || d + min(r, R) < max(r, R)) return ret;
    double x = (d*d - R*R + r*r) / (2 * d);
    double y = sqrt(r*r - x*x);
    PT v = (b - a) / d;
    ret.push_back(a + v*x + RotateCCW90(v)*y);
    if (y > 0)
        ret.push_back(a + v*x - RotateCCW90(v)*y);
    return ret;
}

PT move(PT a, PT dir, double d) {
    double mag = sqrt(dir.x * dir.x + dir.y * dir.y);
    PT unit = dir / mag;

    return PT (a.x + unit.x * d,
               a.y + unit.y * d);
}

// which side of a line formed by points a,b is point c on?
double point_on_side(PT a, PT b, PT c) {
    return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x));
}

int sgn(double x) {
    if (x < 0) return -1;
    return 1;
}

bool in_circle(PT p, PT center, double r) {
    double d = dist(p, center);
    if (d < r) return true;
    return false;
}

void single(PT p1, PT p2) {
    double r1 = (R + dist(origin, p1)) / 2;
    PT c1 = move(p1, origin - p1, r1);

    if (!in_circle(p2, c1, r1)) {
        if (r1 > ans.r) {
            ans.r = r1;
            ans.center = c1;
        }
    }
}

void touch_both(PT p1, PT p2) {
    for (int flip = 0; flip < 2; flip++) {
        double minim = dist(p1, p2) / 2, maxim = R;
        for (int rep = 0; rep < 100; rep++) {
            double r = (minim + maxim) / 2;
            PT center;
            circle2PtsRad(p1, p2, r, center, flip);
            if (sgn(point_on_side(p1, p2, center)) != sgn(point_on_side(p1, p2, origin)))
            	break;

            vector<PT> hit = CircleCircleIntersection(center, origin, r, R);
            if (hit.size() && sgn(point_on_side(p1, p2, hit[0])) == 
            				  sgn(point_on_side(p1, p2, origin))) {
                maxim = r;
            } else {
                if (r > ans.r) {
                    ans.r = r;
                    ans.center = center;
                }
                minim = r;
            }
        }
    }    
}

bool zero(PT p, PT other) {
    cout << fixed << setprecision(9);
    if (p.x != 0 || p.y != 0) return false;
    if (!in_circle(PT(0, R/2), other, R/2)) {
        cout << R / 2 << "\n" << 0 << " " << R / 2 << "\n";
        return true;
    }

    if (!in_circle(PT(0, -R/2), other, R/2)) {
        cout << R / 2 << "\n" << 0 << " " << (-R / 2) << "\n";
        return true;
    }

    if (!in_circle(PT(R/2, 0), other, R/2)) {
        cout << R / 2 << "\n" << R / 2 << " " << 0 << "\n";
        return true;
    }

    if (!in_circle(PT(R/2, 0), other, R/2)) {
        cout << R / 2 << "\n" << (-R / 2) << " " << 0 << "\n";
        return true;
    }
    return false;
}

int main() {

    cin >> R;
    PT p1, p2; cin >> p1.x >> p1.y >> p2.x >> p2.y;

    if (p2 == origin) swap(p1, p2);
    if (p1 == origin) {
        if (zero(p1, p2))
            return 0;
    }

    single(p1, p2);
    single(p2, p1);

    touch_both(p1, p2);

    cout << fixed << setprecision(9);
    cout << ans.r << "\n" << ans.center.x << " " << ans.center.y << "\n";

    return 0;
}

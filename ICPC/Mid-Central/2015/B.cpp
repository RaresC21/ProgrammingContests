#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define x real()
#define y imag()
#define EPS 1e-8
const double PI = acos(-1);
typedef complex<double> PT;

struct Circle {
    PT start_;
    PT v;
    double r;
    Circle(PT s, PT v, double r) : start_(s), v(v), r(r) {}
};

PT move(PT p, PT v, double t) {
    return p + v * t;
}

double sq(double a) {
    return a * a;
}

double solve(double A, double B, double C) {
    double delta = B*B - 4 * A * C;
    if (delta < 0) return 1e20;
    double t1 = (-B + sqrt(delta)) / (2 * A);
    double t2 = (-B - sqrt(delta)) / (2 * A);
    if (t1 > t2) swap(t1, t2);
    if (t1 < 0) return 1e20;
    return t1;
}

double intersect(Circle a, Circle b) {
    double A = sq(a.v.x - b.v.x) + sq(a.v.y - b.v.y);
    double B = 2 * ((a.start_.x - b.start_.x) * (a.v.x - b.v.x) +
                    (a.start_.y - b.start_.y) * (a.v.y - b.v.y));
    double C = sq(a.start_.x - b.start_.x) + sq(a.start_.y - b.start_.y) - sq(a.r + b.r);
    return solve(A, B, C);
}

void translate_all(double t, vector<Circle>& circle) {
    for (int i = 0; i < circle.size(); i++) {
        circle[i].start_ = move(circle[i].start_, circle[i].v, t);
    }
}

int main() {

    int N;
    while (cin >> N) {
        vector<Circle> circle;
        for (int i = 0; i < N; i++) {
            double xx, yy, vx, vy, r; cin >> xx >> yy >> vx >> vy >> r;
            circle.pb(Circle(PT(xx, yy), PT(vx, vy), r));
        }

        double ans = 0;
        int amnt = 0;
        do {
            double early = 1e20;
            amnt = 0;
            int a = -1, b = -1;
            for (int i = 0; i < circle.size(); i++) {
                for (int k = i + 1; k < circle.size(); k++) {
                    double hit = intersect(circle[i], circle[k]);
                    if (hit > 1e15) continue;
                    if (hit < early) {
                        early = hit;
                        a = i, b = k;
                    }
                    amnt++;
                }
            }

            if (early > 1e15) break;
            translate_all(early, circle);

            vector<Circle> cur;
            for (int i = 0; i < circle.size(); i++) {
                if (a != i && b != i)
                    cur.pb(circle[i]);
            }
            double area_a = circle[a].r * circle[a].r;
            double area_b = circle[b].r * circle[b].r;
            double total = area_a + area_b;

            cur.pb(Circle(circle[a].start_ * (area_a / total) + circle[b].start_ * (area_b / total),
                            circle[a].v * (area_a / total) + circle[b].v * (area_b / total),
                            sqrt(circle[a].r * circle[a].r + circle[b].r * circle[b].r)));
            circle = cur;
            ans += early;
        } while (amnt != 0);

        cout << circle.size() << " " << fixed << setprecision(9) << ans << "\n";
    }

    return 0;
}
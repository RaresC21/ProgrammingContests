#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> PT;
#define x first
#define y second
const double EPS = 1e-9;
#define EQ(a, b) (fabs((a) - (b)) <= EPS)
#define LE(a, b) ((a) <= (b) + EPS)
#define GE(a, b) ((a) >= (b) - EPS)

double norm(const PT& a) { return a.x*a.x + a.y*a.y; }
double abs(const PT& a) { return sqrt(norm(a)); }

double dist(const PT& a, const PT& b) {
    return abs(PT(b.x - a.x, b.y - a.y));
}

double dist2(const PT& a, const PT& b) {
    return norm(PT(b.x - a.x, b.y - a.y));
}

bool cw(const PT& o, const PT& a, const PT& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x) > 0;
}

template<class It> vector<PT> convex_hull(It lo, It hi) {
    int k = 0;
    if (hi - lo <= 1) return vector<PT>(lo, hi);
    vector<PT> res(2 * (int)(hi - lo));
    sort(lo, hi);

    for (It it = lo; it != hi; ++it) {
        while (k >= 2 && !cw(res[k - 2], res[k - 1], *it)) k--;
        res[k++] = *it;
    }
    int t = k + 1;
    for (It it = hi - 2; it != lo - 1; --it) {
        while (k >= t && !cw(res[k - 2], res[k - 1], *it)) k--;
        res[k++] = *it;
    }
    res.resize(k - 1);
    return res;
}

double dist_line(const PT& p, const PT& a, const PT& b) {
    double ab2 = dist2(a, b);
    if (EQ(ab2, 0)) return dist(p, a);
    double u = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / ab2;
    return abs(PT(a.x + u *  (b.x - a.x) - p.x, a.y + u * (b.y - a.y) - p.y));
}

int main() {

    int N; cin >> N;
    vector<PT> v(N);
    for (int i = 0; i < N; i++) {
        double x, y; cin >> x >> y;
        v[i] = PT(x, y);
    }

    vector<PT> hull = convex_hull(v.begin(), v.end());

    double ans = 1e9;
    for (int i = 0; i < hull.size(); i++) {
        double cur = 0;
        for (int k = 0; k < hull.size(); k++) {
            if (i == k) continue;
            cur = max(cur, dist_line(hull[k], hull[i], hull[(i+1)%hull.size()]));
        }
        ans = min(ans, cur);
    }

    cout << fixed << setprecision(9) << ans << "\n";

    return 0;
}
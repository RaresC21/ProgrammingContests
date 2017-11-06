#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double PI = acos(-1);
typedef complex<double> PT;

struct Circle {
    PT p;
    double r;
    Circle () {}
    Circle(PT c, double r) : p(c), r(r) {}
};

struct Candidate {
    PT p;
    int indx;
    double x, y;
    Candidate() {}
    Candidate(PT p, int i) : p(p), indx(i) {
        x = real(p);
        y = imag(p);
    }

    bool operator < (const Candidate& other) const {
        if (fabs(x - other.x) < EPS) return y < other.y;
        return x < other.x;
    }
};

//change < 0 comparisons to > 0 to produce hull points in CCW order
double cw(const Candidate & o, const Candidate & a, const Candidate & b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x) < 0;
}

//convex hull from a range [lo, hi) of points
//monotone chain in O(n log n) to find hull points in CW order
//notes: the range of input points will be sorted lexicographically
template<class It> std::vector<Candidate> convex_hull(It lo, It hi) {
  int k = 0;
  if (hi - lo <= 1) return std::vector<Candidate>(lo, hi);
  std::vector<Candidate> res(2 * (int)(hi - lo));
  std::sort(lo, hi); //compare by x, then by y if x-values are equal
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

// rotate a about p
PT rotate(PT p, PT a, double sz, double theta) {
    PT c = (a-p) * polar(1.0, theta) + p;
    PT dir = (c - p) / abs(c - p);
    return p + dir * sz;
}

// return angle a-b-c
inline double angle(PT a, PT b, PT c) {
    return abs(remainder(arg(a-b) - arg(c-b), 2.0 * M_PI));
}

inline double sector_len(double theta, double r) {
    return theta * r;
}

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    vector<Circle> v(N);
    double ans = 0;
    double RR = 0;
    for (int i = 0; i < v.size(); i++) {
        int a, b; cin >> a >> b;
        int r; cin >> r;
        r += 10;
        RR = max(RR, 1.0 * r);
        v[i] = Circle(PT(a, b), r);
    }


    vector<Candidate> cand;
    for (int i = 0; i < v.size(); i++) {
        for (int k = i + 1; k < v.size(); k++) {
            int a = i, b = k;
            if (v[i].r > v[k].r) swap(a, b);
            double d = abs(v[a].p - v[b].p);

            if (d + v[a].r <= v[b].r) continue;

            double xx = d * v[a].r / (v[b].r - v[a].r);
            double theta = acos(v[a].r / xx);

            cand.push_back(Candidate(rotate(v[a].p, v[b].p, v[a].r, (PI - theta)), a));
            cand.push_back(Candidate(rotate(v[a].p, v[b].p, v[a].r, -(PI - theta)), a));

            cand.push_back(Candidate(rotate(v[b].p, v[a].p, v[b].r, theta), b));
            cand.push_back(Candidate(rotate(v[b].p, v[a].p, v[b].r, -theta), b));
        }
    }

    if (cand.size() == 0) {
        cout << 2 * PI * v[0].r << "\n";
        return 0;    
    }

     // remove duplicates. 
    sort(cand.begin(), cand.end());
    vector<Candidate> cur;
    for (int i = 0; i < cand.size(); i++) {
        bool bad = false;
        int k = (i + 1);
        if (norm(cand[i].p - cand[k].p) < EPS) continue;
        cur.push_back(cand[i]);
    }
    cand = cur;


    // if a candidate point exists in another circle, don't use it.
    vector<Candidate> hull = convex_hull(cand.begin(), cand.end());
    vector<Candidate> c;
    for (int i = 0; i < hull.size(); i++) {
        bool inside = false;
        for (int k = 0; k < v.size(); k++) {
            if (abs(v[k].p - hull[i].p) + EPS < v[k].r) {
                inside = true;
                break;
            }
        }
        if (!inside) {
            c.push_back(hull[i]);
        }
    }
    c = convex_hull(c.begin(), c.end());

    // calculate perimeter.
    for (int i = 0; i < c.size(); i++) {
        int k = (i + 1) % c.size();
        if (c[i].indx == c[k].indx) {
            int j = c[i].indx;
            Circle cc = v[j];

            double theta = angle(c[i].p, cc.p, c[k].p);
            ans += fabs(sector_len(theta, cc.r));
        } else {
            ans += abs(c[i].p - c[k].p);
        }
    }

    cout << fixed << setprecision(9);
    cout << max(2 * PI * RR, ans) << "\n";

    return 0;
}

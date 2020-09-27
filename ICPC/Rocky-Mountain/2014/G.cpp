/*
Given a range of PTs specifying a polygon on the Cartesian
plane, as well as two PTs specifying an infinite line, "cut"
off the right part of the polygon with the line and return the
resulting polygon that is the left part.
Time Complexity: O(n) on the number of PTs in the poylgon.
*/

#include <bits/stdc++.h>
using namespace std;
typedef complex<double> PT;
#define X real()
#define Y imag()

const double eps = 1e-9;

#define EQ(a, b) (fabs((a) - (b)) <= eps) /* equal to */
#define LT(a, b) ((a) < (b) - eps)        /* less than */
#define GT(a, b) ((a) > (b) + eps)        /* greater than */

double cross(const PT & a, const PT & b) {
    return imag(conj(a) * b);
}

int orientation(const PT & o, const PT & a, const PT & b) {
  double c = cross(a - o, b - o);
  return LT(c, 0) ? -1 : (GT(c, 0) ? 1 : 0);
}


//  intersection of lines a1-a2 and b1-b2
bool line_intersection(const PT a1, PT a2, PT b1, PT b2, PT &isect) {
    double d = cross(a2-a1, b2-b1);
    if (abs(d) < eps) return false;
    double t = cross(b2-b1, a1-b1) / d;
    isect = a1 + (a2-a1)*t;
    return true;
}

template<class It>
vector<PT> convex_cut(It lo, It hi, const PT & p, const PT & q) {
  vector<PT> res;
  for (It i = lo, j = hi - 1; i != hi; j = i++) {
    int d1 = orientation(p, q, *j), d2 = orientation(p, q, *i);
    if (d1 >= 0) res.push_back(*j);
    if (d1 * d2 < 0) {
      PT r;
      line_intersection(p, q, *j, *i, r);
      res.push_back(r);
    }
  }
  return res;
}

vector<PT> p;

inline double area(vector<PT> v) {
    double ans = 0;
    for (int i = 0; i < v.size(); i++) {
        int k = (i + 1) % v.size();
        ans += 0.5 * cross(v[i], v[k]);
    }
    return ans;
}

inline double area(double h) {
    vector<PT> remain = convex_cut(p.begin(), p.end(), PT(100, h), PT(-100, h));
    return area(remain);
}

int main() {
    int N; cin >> N;
    int D, L; cin >> D >> L;

    p.resize(N);
    for (int i = 0; i < N; i++) {
        double x, y; cin >> x >> y;
        p[i] = PT(x, y);
    }

    double minim = 0, maxim = 1000;
    for (int i = 0; i < 100; i++) {
        double mid = (minim + maxim) / 2;
        double a = area(mid);
        if (a * D < 1000 * L) {
            minim = mid;
        } else {
            maxim = mid;
        }
    }

    cout << fixed << setprecision(2) << minim << "\n";
    return 0;
}
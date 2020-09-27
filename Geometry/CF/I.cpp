#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define SZ(x) ((int)(x).size())
#define x real()
#define y imag()
const double EPS = 1e-8;
typedef complex<double> PT;

inline double dot(PT a, PT b) {
    return real(conj(a) * b);
}

inline double cross(PT a, PT b) {
    return imag(conj(a) * b);
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

int main() {
    freopen("distance4.in", "r", stdin);
    freopen("distance4.out", "w", stdout);

    PT A, P, Q;
    double xx, yy;
    cin >> xx >> yy; A = PT(xx, yy);
    cin >> xx >> yy; P = PT(xx, yy);
    cin >> xx >> yy; Q = PT(xx, yy);

    cout << fixed << setprecision(9);
    cout << abs(A - ProjectPointSegment(P, Q, A)) << "\n";

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define SZ(x) ((int)(x).size())
#define x real()
#define y imag()
typedef complex<double> PT;

inline double cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    freopen("distance2.in", "r", stdin);
    freopen("distance2.out", "w", stdout);

    PT A, P, Q;
    double xx, yy;
    cin >> xx >> yy; A = PT(xx, yy);
    cin >> xx >> yy; P = PT(xx, yy);
    cin >> xx >> yy; Q = PT(xx, yy);

    double cr = cross(P - Q, A - Q);
    double h = cr / abs(P - Q);

    cout << fixed << setprecision(9) << fabs(h) << "\n";

    return 0;
}
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
    // freopen("area1.in", "r", stdin);
    // freopen("area1.out", "w", stdout);

    PT a, b, c;
    double xx, yy;
    cin >> xx >> yy; a = PT(xx, yy);
    cin >> xx >> yy; b = PT(xx, yy);
    cin >> xx >> yy; c = PT(xx, yy);
    cout << fixed << setprecision(2) << abs(cross(b - a, c - a)) / 2.0 << "\n";

    return 0;
}
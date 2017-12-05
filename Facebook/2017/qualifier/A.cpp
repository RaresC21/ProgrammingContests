#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

typedef complex<double> PT;
const double PI = acos(-1);

// angle to a, around b, from c, CCW + CW -
double angle(const PT& a, const PT& b, const PT& c) {
    return remainder(arg(a-b) - arg(c-b), 2.0 * M_PI);
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";

        double P; cin >> P;
        int x, y; cin >> x >> y;

        if (P == 0) {
            cout << "white\n";
            continue;
        }

        if (x == 50 && y == 50) {
            cout << "black\n";
            continue;
        }

        P = 360 * P / 100;
        P = P * PI / 180;

        PT test = PT(x, y);
        PT center = PT(50, 50);
        PT top_pt = PT(50, 100);

        if (abs(center - test) > 50) {
            cout << "white\n";
        } else {
            double theta = angle(test, center, top_pt);
            if (theta > 0) theta = 2 * PI - theta;
            theta = abs(theta);

            if (theta <= P) {
                cout << "black\n";
            } else {
                cout << "white\n";
            }
        }

    }

    return 0;
}

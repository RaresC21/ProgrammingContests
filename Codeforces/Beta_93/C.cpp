#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define mp make_pair

int main() {

    lli t1, t2, x1, x2, t0; cin >> t1 >> t2 >> x1 >> x2 >> t0;

    lli dt = t2 - t0;
    if (dt == 0) {
        if (x1 != x2)
            cout << 0 << " " << x2 << "\n";
        else
            cout << x1 << " " << x2 << "\n";
        return 0;
    }

    pair<lli, lli> best = mp(-1, -1);
    pair<lli, lli> ans = mp(-1, -1);

    for (lli y1 = 1; y1 <= x1; y1++) {
        lli y2 = (y1 * (t0 - t1) + (dt - 1)) / dt;
        y2 = min(y2, x2);

        lli bottom = y1 + y2;

        if (t0 * bottom > t1 * y1 + t2 * y2) continue;

        lli top = t1 * y1 + t2 * y2 - t0 * bottom;

        if (best.first == -1) {
            best = mp(top, bottom);
            ans = mp(y1, y2);
        } else if (top * best.second < bottom * best.first) {
            best = mp(top, bottom);
            ans = mp(y1, y2);
        } else if (top * best.second == bottom * best.first) {
            if (top + bottom > best.first + best.second) {
                best = mp(top, bottom);
                ans = mp(y1, y2);
            }
        }
    }

    if (ans.first == -1) ans = mp(0, x2);
    cout << ans.first << " " << ans.second << "\n";

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

const int INF = 1e9;

bool inside(PII sq, PII pt, int R) {
    if (pt.A >= sq.A && pt.A - sq.A <= R) {
        if (pt.B <= sq.B && sq.B - pt.B <= R) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        int N; cin >> N;
        int R; cin >> R;
        vector<PII> v;
        for (int i = 0; i < N; i++) {
            int x, y; cin >> x >> y;
            v.pb(mp(x, y));
        }

        vector<PII> square;
        for (int i = 0; i < N; i++) {
            square.pb(v[i]);
            for (int k = i + 1; k < N; k++) {
                if (abs(v[i].A - v[k].A) > R || abs(v[i].B - v[k].B) > R) continue;
                square.pb(mp(min(v[i].A, v[k].A), max(v[i].B, v[k].B)));
            }
        }

        int ans = 0;
        for (int i = 0; i < square.size(); i++) {
            for (int k = i; k < square.size(); k++) {
                int cur = 0;
                for (int a = 0; a < N; a++) {
                    bool s1 = inside(square[i], v[a], R);
                    bool s2 = inside(square[k], v[a], R);
                    if (s1 || s2) {
                        cur++;
                    }
                }
                ans = max(ans, cur);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}

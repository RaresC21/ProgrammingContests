#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        int N; cin >> N;
        VI v(N);
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }

        sort(v.begin(), v.end());

        int i = 0;
        int ans = 0;
        for (int k = (int)v.size() - 1; k >= 0; k--) {
            int cur = v[k];
            while (cur < 50 && i < k) {
                cur += v[k];
                i++;
            }
            if (cur >= 50) {
                ans++;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}

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
#define io ios_base::sync_with_stdio(false)

void print_time(const clock_t& begin) {
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr << "elapsed time: ";
    cerr << fixed << setprecision(4) << elapsed_secs << "\n";
}

const int INF = 1e9;

int solve_single() {
    int N; cin >> N;
    VI v(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> v[i];
    }

    int ans = 0;
    VI dp(N + 1);
    for (int i = 1; i <= N; i++) {
        int amnt = 0;
        for (int k = i, add = 3; k >= 1 && add >= 0; k--, add--) {
            if (add == 3) {
                dp[i] = dp[i - 1] + add;
            } else if (add == 2) {
                if (v[k + 1] <= v[k]) break;
                if (v[k + 1] - v[k] > 30) break;
                else if (v[k + 1] - v[k] > 20) amnt += 2;
                else if (v[k + 1] - v[k] > 10) amnt++;
                if (amnt > add) break;

                dp[i] = min(dp[i], dp[k - 1] + add);
            } else if (add == 1) {
                if (v[k + 1] <= v[k]) break;
                if (v[k + 1] - v[k] > 20) break;
                else if (v[k + 1] - v[k] > 10) amnt++;
                if (amnt > add) break;

                dp[i] = min(dp[i], dp[k - 1] + add);
            } else {
                if (v[k + 1] <= v[k]) break;
                if (v[k + 1] - v[k] > 10) amnt++;
                if (amnt > add) break;

                dp[i] = min(dp[i], dp[k - 1] + add);
            }
        }
    }
    return dp[N];
}

int main() {
#ifdef TIMP
    clock_t start_time = clock();
#endif
    io;

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        int ans = solve_single();
        cout << ans << "\n";
    }

#ifdef TIMP
    print_time(start_time);
#endif
    return 0;
}

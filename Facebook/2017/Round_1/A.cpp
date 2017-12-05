#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";


        int N, M; cin >> N >> M;
        vector<vector<int> > c(N + 1, vector<int>(M + 1, 0));
        for (int i = 1; i <= N; i++) {
            for (int k = 1; k <= M; k++) {
                cin >> c[i][k];
            }
            sort(c[i].begin(), c[i].end());
        }

        vector<int> dp(N + 1, INF);
        dp[0] = 0;
        for (int i = 1; i <= N; i++) { // on day i
            vector<int> cur(N + 1, INF);
            for (int k = i; k <= N; k++) { // have bought k up until now
                int cost = 0;
                cur[k] = dp[k];
                for (int j = 1; j <= M; j++) { // bought j today
                    if (k - j < 0) break;
                    cost += c[i][j];
                    int tax = j*j;

                    cur[k] = min(cur[k], dp[k - j] + cost + tax);
                }
            }
            dp = cur;
        }

        cout << dp[N] << "\n";
    }

    return 0;
}

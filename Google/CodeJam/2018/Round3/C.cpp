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

const LL INF = 1e18;
const int MAX = 100005;
const int MAXLEN = 200;

VLL weight;
LL dp[MAX][MAXLEN];

int main() {
    io;

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {

        int N; cin >> N;
        weight.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> weight[i];
        }

        for (int i = 0; i < N; i++)
        for (int l = 2; l < MAXLEN; l++)
            dp[i][l] = INF;

        int ans = 1;
        for (int i = 0; i < N; i++) dp[i][1] = weight[i];
        for (int l = 1; l < MAXLEN; l++) {
            for (int i = 1; i < N; i++) {
                // do not place ant
                dp[i][l] = min(dp[i][l], dp[i - 1][l]);

                // place ant
                if (l == 1) continue;
                if (weight[i] * 6LL >= dp[i - 1][l - 1]) {
                    dp[i][l] = min(dp[i][l], dp[i - 1][l - 1] + weight[i]);
                    ans = max(ans, l);
                }
            }
        }

        cout << "Case #" << t << ": ";
        cout << ans << "\n";
    }

    return 0;
}

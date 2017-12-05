#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second

const LL INF = 1e12;
const int MAX = 111;

LL dist[MAX][MAX];
int s[5005], e[5005];
LL dp[100005][2];

void init() {
    for (int i = 0; i < MAX; i++) {
        for (int k = 0; k < MAX; k++)
            if (i != k)
                dist[i][k] = INF;
    }

    memset(dp, -1, sizeof(dp));
}

void floyd_warshall(int N) {
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

LL solve(int pos, bool carry, int K) {

    if (dp[pos][carry] != -1) return dp[pos][carry];
    if (pos == K) {
        if (!carry)
            return dist[s[pos]][e[pos]];
        else
            return dist[s[pos]][e[pos - 1]] + dist[e[pos - 1]][e[pos]];
    }

    LL res;
    if (!carry) {
        // drop off immediately, then go to pos + 1
        res = solve(pos + 1, false, K) + dist[s[pos]][e[pos]] + dist[e[pos]][s[pos + 1]];

        // go to next client, keeping current furniture.
        res = min(res, solve(pos + 1, true, K) + dist[s[pos]][s[pos + 1]]);
    } else {
        // must drop off previous furniture.
        LL must = dist[s[pos]][e[pos - 1]];

        // drop off current furniture, then go to next house
        res = solve(pos + 1, false, K) + dist[e[pos - 1]][e[pos]] + dist[e[pos]][s[pos + 1]];

        // go directly to next house, keeping current furniture
        res = min(res, solve(pos + 1, true, K) + dist[e[pos - 1]][s[pos + 1]]);

        res += must;
    }

    return dp[pos][carry] = res;
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        int N, M, K; cin >> N >> M >> K;

        init();

        for (int k = 0; k < M; k++) {
            int a, b, c; cin >> a >> b >> c;
            dist[a][b] = min(dist[a][b], c*1LL);
            dist[b][a] = dist[a][b];
        }
        floyd_warshall(N);
        for (int k = 1; k <= K; k++) {
            cin >> s[k] >> e[k];
        }
        LL ans = solve(1, false, K) + dist[1][s[1]];
        if (ans >= INF) ans = -1;
        cout << ans << "\n";
    }

    return 0;
}

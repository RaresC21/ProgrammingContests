#include <bits/stdc++.h>
using namespace std;

const int MAX = 1003;
int N, M;
int dp[MAX][MAX];
int gold[MAX], decrease[MAX];
vector<pair<int, int> > path[MAX];

int main() {
    ios_base::sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> gold[i] >> decrease[i];
    }

    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        path[a].push_back(make_pair(b, c));
        path[b].push_back(make_pair(a, c));
    }

    for (int i = 0; i <= N; i++) {
        for (int k = 0; k <= M; k++) {
            dp[i][k] = -1000000000;
        }
    }

    dp[1][1] = gold[1];
    int ans = gold[1];
    for (int day = 2; day < MAX; day++) {
        for (int i = 1; i <= N; i++) {
            for (pair<int, int> prev : path[i]) {
                int prev_mine = prev.first;
                int prev_day = day - prev.second;
                int cur_gold = gold[i] - decrease[i] * (day - 1);

                if (prev_day <= 0) continue;
                if (cur_gold < 0) cur_gold = 0;

                dp[i][day] = max(dp[i][day], dp[prev_mine][prev_day] + cur_gold);
                ans = max(ans, dp[i][day]);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
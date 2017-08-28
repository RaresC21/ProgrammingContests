#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 1003
#define INF 1000000000000000009

lli timp[MAX];
lli dp[MAX];

int main() {

    lli N, D, C;
    cin >> N >> D >> C;

    for (int i = 1; i <= N; i++) {
        cin >> timp[i];
        dp[i] = N * D;
    }


    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        lli cur = 0;
        for (int k = i - 1; k >= 0; k--) {
            lli t = timp[i] - timp[k + 1];
            cur += t * C;

            dp[i] = min(dp[i], dp[k] + cur + D);
        }
    }

    cout << dp[N] << "\n";

    return 0;
}
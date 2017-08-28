#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 200005

#define INF 1000000
map<lli, lli> sum;
lli a[MAX];

int main() {
    #define int lli

    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    pair<int, int> ans = {INF, INF};

    sum[0] = 0;
    int cur = 0;
    for (int i = 1; i <= N; i++) {
        cur += a[i];
        if (sum.count(cur)) {
            ans = min(ans, mp(i - sum[cur], sum[cur]));
        }
        sum[cur] = i;
    }

    if (ans.first == INF) {
        cout << "-1\n";
    } else
        cout << ans.second + 1 << " " << ans.first << "\n";

    return 0;
}
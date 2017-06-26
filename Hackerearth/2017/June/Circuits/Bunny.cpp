#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define MAX 25
int d;
string s;
lli dp[1 << MAX][MAX];

lli solve(lli mask, lli pos) {
    if (mask == (1 << s.size()) - 1)
	if (pos == s.size() - 1)
	    return dp[mask][pos] = 1;
	else
	    return dp[mask][pos] = 0;
    
    if (dp[mask][pos] != -1)
	return dp[mask][pos];

    int ans = 0;
    for (int i = -d; i <= d; i++) {
	if (i == 0) continue;
	int cur = pos + i;
	if (cur < 0 || cur >= s.size()) continue;

	if (s[pos] != '?' && abs(i) != s[pos] - '0') continue;

	if (mask & (1 << cur)) continue;
	ans += solve(mask | (1 << cur), cur);
    }
    return dp[mask][pos] = ans;
}

int main() {

    memset(dp, -1, sizeof(dp));
    
    cin >> s;
    cin >> d;

    if (s.size() > MAX) return 0;

    solve(1, 0);
    cout << dp[1][0] << "\n";
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define MP make_pair
#define PB push_back
#define A first
#define B second

const int MOD = 1000000007;
const int MAX = 1003;
string s;
int dp[MAX][MAX][30];

int solve(int l, int r, int c) {
    if (dp[l][r][c] != -1) return dp[l][r][c];
    if (l == r && s[l] == s[r] && s[l] - 'a' == c) return 1;
    else if (l == r) return 0;
    if (l > r) return 0;
    if (s[l]-'a' != c || s[r]-'a' != c) {
        return dp[l][r][c] = (solve(l + 1, r, c) + solve(l, r - 1, c) - solve(l + 1, r - 1, c)) % MOD;
    } else {
        int ans = 0;
        for (int a = 0; a < 26; a++) {
            ans = (ans + solve(l + 1, r - 1, a)) % MOD;
        }
        return dp[l][r][c] = ans + 2;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    memset(dp, -1, sizeof(dp));

    cin >> s;
    int ans = 0;
    for (int a = 0; a < 26; a++)
        ans = (ans + solve(0, s.size(), a)) % MOD;

    cout << (ans + MOD) % MOD << "\n";

    return 0;
}
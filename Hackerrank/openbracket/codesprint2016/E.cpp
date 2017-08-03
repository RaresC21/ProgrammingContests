#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

const lli mod = 1000 * 1000 * 1000 + 7;
#define MOD mod

int S[12][12];


inline lli exponent_(lli a, lli x, lli p) {
    lli ans = 1;
    while (x > 0) {
        if (x % 2 == 1)
            ans = (ans * a) % p;
        x /= 2;
        a = (a * a) % p;
    }
    return ans;
}

inline lli add(lli a, lli b) { return a + b >= mod ? a + b - mod : a + b; }
inline lli sub(lli a, lli b) { return a - b < 0 ? a - b + mod : a - b; }
inline lli mul(lli a, lli b) { return a * 1ll * b % mod; }

void Generate(){
    int i, j;
    for (i = 1, S[0][0] = 1; i < 12; i++){
        for (j = 1, S[i][0] = 0; j <= i; j++){
            S[i][j] = ( ((long long)S[i - 1][j] * j) + S[i - 1][j - 1]) % MOD;
        }
    }
}

long long faulhaber(long long n, int k){
    if (!k) return (n % MOD);

    int i, j, l;
    long long z, res = 0;
    for (j = 0; j <= k; j++){
        for (l = j + 1, i = 0, z = 1; (i - 1) < j; i++){
            if ((l > 1) && !((n - i + 1) % l)){
                z = (z * (((n - i + 1) / l) % MOD) ) % MOD;
                l = 1;
            }
            else z = (z * ((n - i + 1) % MOD) ) % MOD;
        }
        res = (res + (z * S[k][j])) % MOD;
    }
    return res;
}

#define pb push_back
lli M, N, K;
lli val[60];
lli sum;
lli dp[60][100005];

lli solve(lli n, lli m, lli k) {
    if (n == 0) return faulhaber(m, k);
    if (m < 100005 && dp[n][m] != -1) return dp[n][m];
    lli res = sub(solve(n - 1, m, k), mul(exponent_(val[n], k, mod), solve(n - 1, m / val[n], k)));
    if (m < 100005) dp[n][m] = res;
    return res;
}

int main() {

    Generate();
    
    int T; cin >> T;
    while (T--) {
	cin >> N >> K >> M;
	memset(dp, -1, sizeof(dp));

	for (int i = 1; i <= N; i++)
	    cin >> val[i];

	cout << solve(N, M, K) << "\n";
    }

    
    return 0;
}

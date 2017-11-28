#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
#define PB push_back
#define A first
#define B second
#define INF 1000000011

const int MAX = 100005;
const int MOD = 1e9 + 7;
map<int, int> amnt, d;
int dp[(1 << 13)][71][2];
int fact[MAX], inv_fact[MAX];
bool is_p[80];
VI v;

inline int mult(int a, int b) {
    long long x = (a * 1LL * b);
    if (x > MOD) return x % MOD;
    return x;
}

inline int add(int a, int b) {
    int x = a + b;
    if (x > MOD) x -= MOD;
    return x;
}

inline int exp(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2 == 1)
            ans = mult(ans, a);
        x /= 2;
        a = mult(a, a);
    }
    return ans;
}

inline int comb(int a, int b) {
    return mult(fact[a], mult(inv_fact[b], inv_fact[a - b]));
}

inline int even(int indx) {
    int ans = 0;
    int n = amnt[v[indx]];
    for (int i = 2; i <= n; i += 2) {
        ans = add(ans, comb(n, i));
    }
    return ans;
}

inline int odd(int indx) {
    int ans = 0;
    int n = amnt[v[indx]];
    for (int i = 1; i <= n; i += 2) {
        ans = add(ans, comb(n, i));
    }
    return ans;
}

inline int solve(int mask, int pos, bool use) {
    if (dp[mask][pos][use] != -1) return dp[mask][pos][use];
    if (pos == 0) {
        if (d[v[pos]] == 0 && mask == 0) {
            dp[mask][pos][use] = add(even(pos), odd(pos));
            if (use) dp[mask][pos][use] ++;
            return dp[mask][pos][use];
        }
        if (mask == 0) {
            dp[mask][pos][use] = even(pos);
            if (use) dp[mask][pos][use] += 1;
            return dp[mask][pos][use];
        }
        if (mask == d[v[pos]]) {
            return dp[mask][pos][use] = odd(pos);
        }
        return dp[mask][pos][use] = 0;
    }

    int ans = add(solve(mask, pos - 1, use), // don't use current number
                mult(solve(mask, pos - 1, true), even(pos))); // use this an even number of times
    if (!(is_p[v[pos]] && v[pos] >= 36))
    ans = add(ans, mult(solve(mask ^ d[v[pos]], pos - 1, true), odd(pos))); // use this an odd number of times.
    return dp[mask][pos][use] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);

    fact[0] = 1;
    inv_fact[0] = 1;
    FOR(i,1,MAX) {
        fact[i] = mult(fact[i - 1], i);
        inv_fact[i] = exp(fact[i], MOD - 2);
    }

    VI prime;
    for (int i = 2; i <= 70; i++) {
        bool p = true;
        for (int k = 2; k < i; k++) {
            if (i % k == 0) {
                p = false;
                break;
            }
        }
        if (p) prime.push_back(i);
        is_p[i] = p;
    }

    int N; cin >> N;
    FOR(i,0,N) {
        int x; cin >> x;
        amnt[x] ++;

        int num = x;
        int mask = 0;
        while (x > 1) {
            FOR(k,0,SZ(prime)) {
                while (x % prime[k] == 0) {
                    mask ^= (1 << k);
                    x /= prime[k];
                }
            }
        }
        d[num] = mask;
    }

    for (auto a : amnt) {
        v.push_back(a.A);
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0, SZ(v) - 1, false) << "\n";

    return 0;
}

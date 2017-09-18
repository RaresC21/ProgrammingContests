#include "bits/stdc++.h"
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define A first
#define B second

const int MAX = 100005;
const LL MOD = 1000000007;
LL fact[MAX];

LL exp_(LL a, LL x) {
	LL ans = 1;
	while (x) {
		if (x % 2 == 1) {
			ans = (ans * a) % MOD;
		}
		x /= 2;
		a = (a * a) % MOD;
	}
	return ans;
}

LL inverse_(LL a) {
	return exp_(a, MOD - 2);
}

LL comb(LL N, LL R) {
	LL denom = (fact[R] * fact[N - R]) % MOD;
	return (fact[N] * inverse_(denom)) % MOD;
}

int main() {
	ios_base::sync_with_stdio(false);

	fact[0] = 1;
	FOR(i,1,MAX)
		fact[i] = (fact[i - 1] * i) % MOD;

	int T; cin >> T;
	while (T--) {
		LL a, b; cin >> a >> b;
		cout << (2 * comb(a - 1, b) + MOD) % MOD << "\n";
	}

	return 0;
}
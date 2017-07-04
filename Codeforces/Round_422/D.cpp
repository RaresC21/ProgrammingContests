#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define INF 100000000000000000
#define MOD 1000000007
#define MAX 5000006

lli F[MAX];
lli div_[MAX];
bool met[MAX];

lli solve(lli n) {
    if (n == 1) return 0;
    if (F[n]) return F[n];
    lli x = div_[n];
    return F[n] = (solve(n / x) + (n * (x - 1)) / 2) % MOD;
}

int main() {

    for (int i = 2; i < MAX; i++) {
	if (met[i]) continue;
	for (int k = i; k < MAX; k += i) {
	    if (div_[k] == 0)
		div_[k] = i;
	    met[k] = true;
	}
    }

    lli T, L, R; cin >> T >> L >> R;
    lli tt = 1, ans = 0;
    for (int i = L; i <= R; i++) {
	ans += (tt * solve(i)) % MOD;
	tt = (tt * T) % MOD;
    }

    cout << (ans + MOD) % MOD << "\n";
    
    return 0;
}

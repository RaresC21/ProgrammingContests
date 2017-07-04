#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
#define MOD 1000000007
#define pb push_back

long long dp[MAX];
long long lazy[MAX];

int main() {

    int T; cin >> T;
    while (T--) {
	int N; cin >> N;
	vector<long long> v; v.pb(0);
	for (int i = 1; i <= N; i++) {
	    int x; cin >> x;
	    v.pb(x);
	    dp[i] = 1;
	}

	memset(lazy, 0, sizeof(lazy));

	long long largest = v[N];
	int k = N - 1;
	for (int i = N - 1; i >= 1; i--) {
	    while (k > 0 && v[k] < largest)
		k--;

	    lazy[k] = (lazy[k] + dp[i + 1]) % MOD;
	    lazy[i - 1] = (lazy[i - 1] + lazy[i]) % MOD;
	    dp[i] = (dp[i] + lazy[i]) % MOD;
	    
	    largest = max(largest, v[i]);
	    k = min(k, i - 1);
	}
	cout << (dp[1] + MOD) % MOD  << "\n";
    }

    return 0;
}

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


int main() {
	ios_base::sync_with_stdio(false);

	int N; cin >> N;
	int ans = 1000000009;
	for (int i = 1; i <= N; i++) {
		int a = i;
		int b = (N + a - 1) / a;
		if (a * b >= N)
			ans = min(ans, 2 * a + 2 * b);
	}

	cout << ans << "\n";

	return 0;
}
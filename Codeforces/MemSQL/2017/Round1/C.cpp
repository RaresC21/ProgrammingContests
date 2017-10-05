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

#define MAX 100
int val[MAX];
int dp[MAX][2];
int sum[MAX];

int main() {
	ios_base::sync_with_stdio(false);

	int N; cin >> N;
	int total = 0;
	for (int i = 1; i <= N; i++) {
		cin >> val[i];
	}

	for (int i = N; i >= 1; i--)
		sum[i] = sum[i + 1] + val[i];

	dp[N][0] = val[N];
	dp[N][1] = val[N];
	for (int i = N - 1; i >= 1; i--) {
		dp[i][0] = max(val[i] + sum[i + 1] - dp[i + 1][1], dp[i + 1][0]);
		dp[i][1] = max(val[i] + sum[i + 1] - dp[i + 1][0], dp[i + 1][1]);
	}

	cout << sum[1] - dp[1][0] << " " << dp[1][0] << "\n";

	return 0;
}
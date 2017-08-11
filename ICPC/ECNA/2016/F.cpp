/* 
   /home/rares/ProgrammingContests/ICPC/ECNA/2016/
   F.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 202
#define INF 1000000009
int val[MAX];
int dp[MAX][MAX];

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int solve(int l, int r) {
    if (l + 1 == r) return dp[l][r] = 0;
    if (l + 2 == r) return dp[l][r] = gcd(val[l], val[r]);
    if (dp[l][r] != -1) return dp[l][r];
    
    int res = INF;
    for (int i = l + 1; i < r; i++) {
	int a = solve(l, i);
	int b = solve(i, r);
	res = min(res, a + b);
    }
    res += gcd(val[l], val[r]);

    return dp[l][r] = res;
}

int main() {

    int N;
    while (cin >> N && N) {
	
	for (int i = 1; i <= N; i++) {
	    cin >> val[i];
	}
	for (int i = N + 1; i <= 2 * N; i++)
	    val[i] = val[i - N];
	
	memset(dp, -1, sizeof(dp));
	
	int ans = INF;
	for (int i = 1; i <= N; i++) {
	    for (int k = i + 1; k <= N; k++) {
		ans = min(ans, solve(i, k) + solve(k, i + N) + gcd(val[i], val[k]));
	    }
	}
	    
	cout << ans << "\n";
    }
    
    return 0;
}

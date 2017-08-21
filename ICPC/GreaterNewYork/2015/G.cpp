/* 
   /home/rares/ProgrammingContests/ICPC/GreaterNewYork/2015/
   G.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

bool bad[40];
lli dp[40];

int main() {
    
    int T; cin >> T;
    while (T--) {
	int t; cin >> t;
	int N; cin >> N;
	int M, K; cin >> M >> K;

	memset(bad, 0, sizeof(bad));
	memset(dp, 0, sizeof(dp));
	
	bad[M] = true;
	for (int i = 0; M <= N; i++) {
	    M += K;
	    bad[M] = true;
	}

	dp[0] = 1;
	for (int i = 1; i <= N; i++) {
	    for (int j = 1; j <= i; j++) {
		if (bad[j]) continue;
		dp[i] += dp[i - j];
	    }
	}
	cout <<t << " " <<  dp[N] << "\n";
    }
    
    return 0;
}

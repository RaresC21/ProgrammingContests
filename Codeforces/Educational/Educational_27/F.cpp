/* 
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   F.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MOD 1000000007
#define MAX 251
int dp[MAX][1 << 15][2][2];
char grid[MAX][MAX];
int N, M;

lli solve(int c, int r, int mask, bool protected_from_above, bool miss) {
    if (c == M) return 1;

    int num = r + N * c;
    if (dp[num][mask][protected_from_above][miss] != -1)
	return dp[num][mask][protected_from_above][miss];
    
    int next_c = c;
    int next_r = r + 1;
    if (r == N - 1) next_c ++, next_r = 0;
    
    lli res = 0;
    if (grid[r][c] == 'x') {
	if (mask & (1 << r))
	    res = solve(next_c, next_r, mask ^= (1 << r), 0, miss);
	else 
	    res = solve(next_c, next_r, mask, 0, miss);
    } else if (next_c == c) {
	// add a guard here
	res = solve(next_c, next_r, mask | (1 << r), true, miss);
	
	// spot already protected, no need to add guard
	if (protected_from_above || mask & (1 << r))
	    res = (res + solve(next_c, next_r, mask, protected_from_above, miss)) % MOD;
	else if (!miss) // not protected, and choosing not to put a guard
	    res = (res + solve(next_c, next_r, mask, protected_from_above, true)) % MOD;	
    } else { // move on to the next column, so proted_from_above = false
	// add guard here
	res = solve(next_c, next_r, mask | (1 << r), false, miss);
	
	// cell is protected
	if (protected_from_above || mask & (1 << r))
	    res = (res + solve(next_c, next_r, mask, false, miss)) % MOD;
	else if (!miss)
	    res = (res + solve(next_c, next_r, mask, false, true)) % MOD;
    }

    return dp[num][mask][protected_from_above][miss] = res;
}
	
int main() {
    
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
	string s; cin >> s;
	for (int k = 0; k < M; k++) {
	    char x = s[k];
	    if (N > M) {
		grid[k][i] = x;
	    } else {
		grid[i][k] = x;
	    }
	}
    }
    if (N > M) swap(N, M);

    memset(dp, -1, sizeof(dp));
    cout << solve(0, 0, 0, 0, 0) << "\n";
    
    return 0;
}

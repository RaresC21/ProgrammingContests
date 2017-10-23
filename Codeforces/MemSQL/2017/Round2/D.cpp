/* 
   /home/rares/ProgrammingContests/Codeforces/MemSQL/2017/Round2/
   D.cpp
*/

#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<int> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
#define MP make_pair
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define A first
#define B second

const int MAX = 101;
int N, R;
int a[MAX], b[MAX];
bool met[MAX][MAX*MAX];
double prob[MAX];
double dp[MAX][MAX*MAX];

double solve(double ans, int pos, int timp) {
    if (timp > R) return ans;
    if (pos == N) return 0;
    if (met[pos][timp]) return dp[pos][timp];
    met[pos][timp] = true;

    double nxt_a = solve(ans, pos+1, timp + a[pos]);
    double nxt_b = solve(ans, pos+1, timp + b[pos]);
    dp[pos][timp] = prob[pos] * (a[pos] + min(ans, nxt_a)) +
	(1.0 - prob[pos]) * (b[pos] + min(ans, nxt_b));
    return dp[pos][timp];
}

int main() {
    ios_base::sync_with_stdio(false);
    
    cin >> N >> R;
    FOR(i,0,N) {
	cin >> a[i] >> b[i] >> prob[i];
	prob[i] /= 100.0;
    }

    double minim = 0, maxim = 1e9;
    FOR(t,0,100) {
	double mid = (minim + maxim) / 2.0;
	memset(met, 0, sizeof(met));
	if (solve(mid, 0, 0) >= mid) {
	    minim = mid;
	} else {
	    maxim = mid;
	}
    }

    cout << fixed << setprecision(9) << minim << "\n";
    
    return 0;
}

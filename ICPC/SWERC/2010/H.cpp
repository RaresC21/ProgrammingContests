/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2010/
   H.cpp
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

const int INF = 1000000009;
const int MAX = 30;
const int LEN = 201;
char type[MAX];
int conv[500];
int dp[LEN][LEN][MAX];
int cost[MAX][MAX], result[MAX][MAX];
char s[LEN];
int cnt;
int N;

inline void solve(int len) {
    ROF(i,0,len) {
	FOR(k,i+1,len) {
	    FOR(mid,i,k) {
		FOR(a,0,N) {
		    FOR(b,0,N) {
			int res = result[a][b];
			int amnt = dp[i][mid][a] + dp[mid+1][k][b] + cost[a][b];
			if (amnt < dp[i][k][res])
			    dp[i][k][res] = amnt;
		    }
		}
	    }
	}
    }
}

int main() {
    clock_t begin = clock();
    
    scanf("%d", &N);
    while (N != 0) {
	cnt = 0;
	FOR(i,0,N) {
	    scanf(" %c", &type[i]);
	    conv[type[i]] = cnt++;
	}
	FOR(i,0,N) {
	    FOR(k,0,N) {
		int c; char t;
		scanf(" %d-%c", &c, &t);
		cost[i][k] = c;
		result[i][k] = conv[t];
	    }
	}

	int Q; cin >> Q;
	FOR(q,0,Q) {
	    scanf("%s", s);
	    int len = strlen(s);

	    memset(dp, 30, sizeof(dp));
	    FOR(i,0,len) {
		dp[i][i][conv[s[i]]] = 0;
	    }

	    int best = INF;
	    int res = INF;
	    solve(len);
	    
	    FOR(t,0,cnt) {
		int cur = dp[0][len-1][t];;
		if (cur < best) {
		    best = cur;
		    res = t;
		} else if (cur == best)
		    res = min(res, t);
	    }

	    printf("%d-%c\n", best, type[res]);
	}
	printf("\n");
	cin >> N;
    }
    
    return 0;
}

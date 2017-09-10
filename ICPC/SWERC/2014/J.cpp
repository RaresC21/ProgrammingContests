/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2014/
   J.cpp
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

#define FOR(i,m,n) for(int i = (m); i < (n); i++)
#define ROF(i,m,n) for(int i = (n)-1; i >= (m); i--)
#define foreach(x,i) for( __typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
typedef long long LL;
typedef unsigned long long uLL;
typedef vector<LL> VI;
typedef vector<LL> VLL;
#define SZ(x) ((int)(x).size())
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
typedef complex<double> point;
#define A first
#define B second
#define X real()
#define Y imag()

const int MAX = 2003;
const int MOD = 1000000007;
const int MOD2 = 1000000009;
const int PRIME = 71;
const int PRIME2 = 5;

int match(const VI& S, const VI& T) {
    LL x_power = 1;
    FOR(i,0,SZ(T)-1)
	x_power = (x_power * PRIME2) % MOD2;
     
    LL s = 0, t = 0;
    FOR(i,0,SZ(T)) {
	s = (s * PRIME2 + S[i]) % MOD2;
	t = (t * PRIME2 + T[i]) % MOD2;
    }
    t = (t + MOD2) % MOD2;
    
    int amnt = 0;
    int N = SZ(S), M = SZ(T);
    FOR(i, M, N) {	
	if (s == t)
	    amnt++;
	s = (PRIME2 * (s - 1LL * x_power * S[i-M]) + S[i]) % MOD2;
	s = (s + MOD2) % MOD2;
    }
    if (s == t)
	amnt++;
    return amnt;
}

void pref(const VI& S, VI& ans, int M) {
    LL x_power = 1;
    FOR(i,0,M-1)
	x_power = (x_power * PRIME) % MOD;
    LL s = 0;
    FOR(i,0,M)
	s = (s * PRIME + S[i]) % MOD;
    s = (s % MOD + MOD) % MOD;
    ans.push_back(s);
    FOR(i, M, SZ(S)) {
	s = (PRIME * (s - 1LL * x_power * S[i - M]) + S[i]) % MOD;
	s = (s + MOD) % MOD;
	ans.push_back(s);
    }
}

int hash_(const VI& v) {
    LL h = 0;
    FOR(i, 0, SZ(v)) {
	h = (h * PRIME + v[i]) % MOD;
    }
    return (h + MOD) % MOD;
}

VI goal[MAX], board[MAX];

#undef int
int main() {
#define int LL
    
    int H, W, N, M;
    cin >> H >> W >> N >> M;
    FOR (i, 0, H) {
	goal[i].resize(W);
	string temp; cin >> temp;
	FOR (k, 0, W) {
	    goal[i][k] = temp[k] == 'o' ? 0 : 1;
	}
    }

    FOR(i, 0, N) {
	board[i].resize(M);
	string temp; cin >> temp;
	FOR(k, 0, M) {
	    board[i][k] = temp[k] == 'o' ? 0 : 1;
	}
    }

    VI target(H);
    for (int i = 0; i < H; i++) {
	target[i] = hash_(goal[i]);
    }
    
    vector<VI> painting;
    FOR(i,0,N) {
	VI r;
	pref(board[i], r, W);
	painting.push_back(r);
    }

    int ans = 0;
    FOR(c,0,SZ(painting[0])) {
	VI cur_row(SZ(painting));
	FOR(i,0,SZ(painting)) {
	    cur_row[i] = painting[i][c];
	}
	VI temp;
	ans += match(cur_row, target);
    }

    cout << ans << "\n";
    
    return 0;
}

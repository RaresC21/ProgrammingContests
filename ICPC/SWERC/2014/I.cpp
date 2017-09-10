/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2014/
   I.cpp
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
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
#define FR first
#define SC second
typedef complex<double> point;
#define X first
#define Y second
//#define X real()
//#define Y imag()

const int MAX = 404;
LL minim[MAX][MAX], maxim[MAX][MAX];
bool met[MAX][MAX];
int num[MAX];
char op[MAX];

void solve(int l, int r) {
    if (l == r) return;
    if (met[l][r]) return;
    met[l][r] = true;
    FOR(i,l,r) {
	solve(l, i);
	solve(i + 1, r);
	if (op[i] == '+' || op[i] == '?') {
	    minim[l][r] = min(minim[l][r], minim[l][i] + minim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], maxim[l][i] + minim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], minim[l][i] + maxim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], maxim[l][i] + maxim[i + 1][r]);
	    
	    maxim[l][r] = max(maxim[l][r], minim[l][i] + minim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], maxim[l][i] + minim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], minim[l][i] + maxim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], maxim[l][i] + maxim[i + 1][r]);
	}
	if (op[i] == '*' || op[i] == '?') {
	    minim[l][r] = min(minim[l][r], minim[l][i] * minim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], maxim[l][i] * minim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], minim[l][i] * maxim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], maxim[l][i] * maxim[i + 1][r]);
	    
	    maxim[l][r] = max(maxim[l][r], minim[l][i] * minim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], maxim[l][i] * minim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], minim[l][i] * maxim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], maxim[l][i] * maxim[i + 1][r]);
	}
	if (op[i] == '-' || op[i] == '?') {
	    minim[l][r] = min(minim[l][r], minim[l][i] - minim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], maxim[l][i] - minim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], minim[l][i] - maxim[i + 1][r]);
	    minim[l][r] = min(minim[l][r], maxim[l][i] - maxim[i + 1][r]);
	    
	    maxim[l][r] = max(maxim[l][r], minim[l][i] - minim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], maxim[l][i] - minim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], minim[l][i] - maxim[i + 1][r]);
	    maxim[l][r] = max(maxim[l][r], maxim[l][i] - maxim[i + 1][r]);
	}
    }
}

int main() {
    
    int N; cin >> N;
    FOR(i, 0, 2*N) {
	cin >> num[i] >> op[i];
    }
    FOR(i, N, 2*N) {
	num[i] = num[i - N];
	op[i] = op[i - N];
    }
    
    FOR(i,0,2*N) {
	FOR(k,0,2*N) {
	    minim[i][k] = (1LL << 63) - 1;
	    maxim[i][k] = -minim[i][k];
	}
	minim[i][i] = maxim[i][i] = num[i];
    }

    FOR(i,0,N)
	solve(i, i + N);
    FOR(i,0,N)
	cout << abs(minim[i][i+N-1]) << abs(maxim[i][i+N-1]);
    
    return 0;
}

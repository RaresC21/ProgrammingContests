/* 
   /home/rares/ProgrammingContests/ICPC/SWERC/2010/
   C.cpp
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

const int MAX = 1003;
int a[MAX][MAX], b[MAX][MAX];
int v[MAX];
int N;

bool same() {
    VI temp(N);
    FOR(i,0,N) {
	FOR(k,0,N) {
	    temp[i] += v[k] * a[i][k];
	}
    }

    VI ans(N);
    FOR(i,0,N) {
	FOR(k,0,N) {
	    ans[i] += temp[k] * a[i][k];
	}
    }

    VI goal(N);
    FOR(i,0,N) {
	FOR(k,0,N) {
	    goal[i] += v[k] * b[i][k];
	}
    }

    return ans == goal;
}

int main() {
    ios_base::sync_with_stdio(false);

    FOR(i,0,MAX)
	v[i] = rand();
    
    cin >> N;
    while (N != 0) {
	FOR(i,0,N) {
	    FOR(k,0,N) {
		cin >> a[i][k];
	    }
	}
	FOR(i,0,N) {
	    FOR(k,0,N) {
		cin >> b[i][k];
	    }
	}

	if (same()) {
	    cout << "YES\n";
	} else {
	    cout << "NO\n";
	}
	
	cin >> N;
    }
    
    return 0;
}

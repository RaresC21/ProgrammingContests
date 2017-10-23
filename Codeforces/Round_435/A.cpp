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

const int MAX = 200005;
const int INF = 1000000009;
int val[MAX];

int main() {
	ios_base::sync_with_stdio(false);

	int N, X; cin >> N >> X;
	set<int> have;
	FOR(i,0,N) {
		int x; cin >> x;
		have.insert(x);
	}

	int ans = 0;
	FOR(i,0,X) {
		if (!have.count(i)) 
			ans++;
	}
	if (have.count(X)) 
		ans++;

	cout << ans << "\n";
	
	return 0;
}
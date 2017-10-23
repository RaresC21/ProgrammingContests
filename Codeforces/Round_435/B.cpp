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
VI path[MAX];	
LL amnt[2];
int color[MAX];

void dfs(int node, int par, int c) {
	color[node] = c;
	for (int adj : path[node]) {
		if (adj == par) continue;
		dfs(adj, node, 1 - c);
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	int N; cin >> N;
	FOR(i,1,N) {
		int a, b; cin >> a >> b;
		path[a].push_back(b);
		path[b].push_back(a);
	}
	
	dfs(1, 1, 0);
	LL ans = 0;

	FOR(i,1,N+1) {
		amnt[color[i]]++;
	}

	for (int i = 1; i <= N; i++) {
		LL deg = path[i].size();
		LL remain = amnt[(color[i] + 1) % 2] - deg;
		ans += remain;
	}

	cout << ans / 2 << "\n";

	return 0;
}
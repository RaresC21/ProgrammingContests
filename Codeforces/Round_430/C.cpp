/* 
   /home/rares/ProgrammingContests/Codeforces/Round_430/
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

const int MAX = 200005;
int a[MAX];
int ans[MAX];
int amnt[MAX];
VI div_;
VI path[MAX];


int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

void dfs(int node, int par) {
    for (int adj : path[node]) {
	if (adj == par) continue;
	ans[adj] = gcd(a[adj], ans[node]);
	dfs(adj, node);
    }
}

void dfs1(int node, int par, int dep) {
    for (int d : div_) {
	if (a[node] % d == 0)
	    amnt[d]++;
	if (amnt[d] >= dep - 1)
	    ans[node] = max(ans[node], d);
    }
    
    for (int adj : path[node]) {
	if (adj == par) continue;
	dfs1(adj, node, dep + 1);
    }

    for (int d : div_) {
	if (a[node] % d == 0) {
	    amnt[d]--;
	}
    }

}

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    FOR(i,1,N+1) {
	cin >> a[i];
    }

    FOR(i,1,N) {
	int a, b; cin >> a >> b;
	path[a].push_back(b);
	path[b].push_back(a);
    }
    
    ans[1] = a[1];
    for (int adj : path[1]) {
	ans[adj] = a[adj];
	dfs(adj, 1);
    }

    FOR(i,2,a[1]+1) {
	if (a[1] % i == 0) {
	    div_.push_back(i);
	}
    }

    dfs1(1, 1, 1);

    FOR(i,1,N+1)
	cout << ans[i] << " ";
    cout << "\n";
   
    return 0;
}

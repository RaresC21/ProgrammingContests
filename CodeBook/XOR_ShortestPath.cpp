/*
   /home/rares/ProgrammingContests/Codeforces/Educational_27/
   G.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair
#define MAX 100005
bool met[MAX];
int dist[MAX], bit[40];
vector<pair<int, int> > path[MAX];

void add_cycle(int v) {
    for (int i = 30; i >= 0; i--) {
		if (v & (1 << i)) {
	    	if (bit[i] == 0) {
				bit[i] = v;
				return;
	    	}
	    	v ^= bit[i];
		}
    }
}

void dfs(int node) {
    met[node] = true;
    for (pair<int, int> v : path[node]) {
		int adj = v.first;
		int w = v.second;
		if (met[adj]) {
		    add_cycle(dist[node] ^ dist[adj] ^ w);
		} else {
	    	dist[adj] = dist[node] ^ w;
	    	dfs(adj);
		}
    }
}

int main() {

    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i++) {
		int x, y, w; cin >> x >> y >> w;
		path[x].pb(mp(y, w));
		path[y].pb(mp(x, w));
    }

    dfs(1);
    int ans = dist[N];
    for (int i = 30; i >= 0; i--) {
	if (ans & (1 << i) && bit[i] != 0)
	    ans ^= bit[i];
    }

    cout << ans << "\n";

    return 0;
}
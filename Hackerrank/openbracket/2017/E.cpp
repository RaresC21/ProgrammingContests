/* 
   /home/rares/ProgrammingContests/Hackerrank/openbracket/2017/
   E.cpp
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define mp make_pair

#define MAX 200005
int N, M;
int parent[MAX];
int A[MAX][30]; // A[k][i] 2^i-th ancestor of k
int depth[MAX], dist[MAX];
vector<int> edge[MAX];

void dfs(int x, int depth_) {
    if (depth[x] != -1) return;
    depth[x] = depth_;
    for (int next_ : edge[x]) {
        if (parent[next_] == -1)
            parent[next_] = x;
        dfs(next_, depth_ + 1);
    }
}

int color[MAX];

int main() {
    
    cin >> N;
    for (int i = 1; i < N; i++) {
	int a; scanf("%d", &a);
	edge[a].pb(i + 1);
	edge[i + 1].pb(a);
    }

    for (int i = 1; i <= N; i++) {
	cin >> color[i];
	parent[i] = -1;
	depth[i] = -1;
    }

    dfs(1, 0);
    
    int ans = 0;
    for (int i = 1; i <= N; i++) {
	for (int k = i + 1; k <= N; k++) {
	    if (color[i] == color[k]) continue;
	    int a = i, b = k;

	    if (depth[a] < depth[b]) swap(a, b);
	    
	    set<int> col_met;
	    int amnt = 1;
	    
	    while (depth[a] > depth[b]) {
		col_met.insert(color[a]);
		amnt++;
		a = parent[a];
	    }
	    
	    while (a != b) {
		col_met.insert(color[a]);
		col_met.insert(color[b]);
		
		amnt += 2;
		a = parent[a];
		b = parent[b];
	    }
	    
	    col_met.insert(color[a]);
	    
	    if (col_met.size() == amnt)
		ans += 2;
	}
    }

    cout << ans + N << "\n";
    
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000
#define MAX 202
#define SZ 23
int N, M;
int cost[MAX][MAX];
bool met[MAX];
vector<int> path[MAX];
vector<int > group[MAX];
int dp[1 << 23];

inline void dfs(int node, vector<int>& cur) {
    if (met[node]) return;
    met[node] = true;
    cur.push_back(node);
    for (int adj : path[node])
	dfs(adj, cur);
}

inline int solve(int mask, int goal, vector<int>& g) {
    if (mask == goal) return 0;
    if (dp[mask] != -1) return dp[mask];
    
    int res = INF;
    int gs = g.size();
    for (int i = 0; i < gs; i++) {
	if (mask & (1 << (g[i] % SZ))) continue;
	for (int k = i + 1; k < gs; k++) {
	    if (mask & (1 << (g[k] % SZ))) continue;
	    res = min(res, cost[g[i]][g[k]] + solve((mask | (1 << (g[i] % SZ))) |
						    (1 << (g[k] % SZ)), goal, g));
	}
    }
    return dp[mask] = res;
}

int main() {

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
	int a, b, c; cin >> a >> b >> c;
	path[a].push_back(b);
	path[b].push_back(a);
	cost[a][b] = cost[b][a] = c;
    }

    int cur = 0;
    bool impossible = false;
    for (int i = 1; i <= N; i++) {
	if (!met[i]) {
	    dfs(i, group[cur]);
	    if (group[cur].size() % 2 == 1) {
		cout << "impossible\n";
		impossible = true;
		break;
	    }
	    cur++;
	}
    }

    if (impossible)
	return 0;

    int ans = 0;
    for (int g = 0; g < cur; g++) {
	memset(dp, -1, sizeof(dp));
	int mask = 0;
	for (int i = 0; i < group[g].size(); i++)
	    mask |= (1 << (group[g][i] % SZ));
	solve(0, mask, group[g]);
	ans += dp[0];
    }

    cout << ans << "\n";

    return 0;
}

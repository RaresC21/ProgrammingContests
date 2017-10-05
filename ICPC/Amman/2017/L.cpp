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

const LL INF = 20000000000000009;
const int MAX = 2003;
int N, M;
LL dist[MAX];
LL dp[MAX];
bool met[MAX];
vector<PII> path[MAX];

struct Edge {
    int u, v, c;
    Edge(int u, int v, int c) : u(u), v(v), c(c) {}
};
vector<Edge> edges;

LL dfs(int node) {
    if (met[node]) return dp[node];
    met[node] = true;
    LL res = INF;
    for (auto adj : path[node]) {
        LL cur = dfs(adj.A);
        if (cur < 0) res = min(res, 1LL * adj.B + cur);
        else res = min(res, 1LL * adj.B);
    }
    return dp[node] = res;
}

bool bellman_ford() {
    FOR(i,1,N+1) dist[i] = INF;
    dist[1] = 0;
    FOR(counter,1,N) {
        for (Edge e : edges) {
            dist[e.v] = min(dist[e.v], dist[e.u] + e.c);
        }
    }
    for (Edge e : edges) {
        if (dist[e.u] + e.c < dist[e.v]) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        cin >> N >> M;
        FOR(i,1,MAX) path[i].clear();
        edges.clear();

        int min_edge = 1000000009;
        FOR(i,0,M) {
            int u, v, c; cin >> u >> v >> c;
            min_edge = min(min_edge, c);

            edges.push_back(Edge(u, v, c));
            path[u].push_back(MP(v, c));
        }

        bool neg_cycle = bellman_ford();
        if (neg_cycle) {
            cout << "-inf\n";
            continue;
        }

        LL ans = min_edge;
        FOR(i,1,N+1) {
            FOR(k,1,N+1) dp[k] = INF, met[k] = false;
            ans = min(ans, dfs(i));
        }
        cout << ans << "\n";
    }

    return 0;
}
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

const LL MOD = 1000000007;
#define MAX 500005
vector<int> path[MAX];
int par[MAX];
int sz[MAX];
bool cycle[MAX];
bool met[MAX];
bool inspect[MAX];
bool single[MAX];

int find(int a) {
    if (a != par[a])
        par[a] = find(par[a]);
    return par[a];
}

void merge(int a, int b) {
    bool cyc = cycle[a] || cycle[b];
    bool s =  single[a] || single[b];

    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;

    cycle[a] |= cyc || cycle[b];
    single[a] |= s || single[b];
    sz[a] += sz[b];
}

void dfs(int node, int par) {
    merge(node, par);
    if (met[node]) {
        int p = find(node);
        cycle[p] = true;
        merge(p, par);
        return;
    }

    met[node] = true;
    for (int adj : path[node]) {
        if (adj == par) continue;
        dfs(adj, node);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        if (a == b) single[a] = true;
        path[a].push_back(b);
        path[b].push_back(a);
    }
    for (int i = 1; i <= 2*N; i++) {
        sz[i] = 1;
        par[i] = i;
    }

    for (int i = 1; i <= 2*N; i++) {
        if (met[i]) continue;
        dfs(i, i);
    }

    LL ans = 1;
    for (int i = 1; i <= 2*N; i++) {
        int p = find(i);
        if (inspect[p]) continue;
        inspect[p] = true;

        if (single[p]) ans = ans;
        else if (cycle[p]) ans = (ans * 2LL) % MOD;
        else
            ans = (ans * (1LL * sz[p])) % MOD;
    }

    cout << (ans + MOD) % MOD << "\n";

    return 0;
}
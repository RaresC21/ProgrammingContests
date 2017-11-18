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

const int MAX = 50005;
int bad[MAX];
VI path[MAX];
map<int, VI> color[MAX];

void dfs(int node, int par) {
    if (bad[node] == 2) return;
    bad[node]++;
    for (int adj : path[node]) {
        if (adj == par) continue;
        dfs(adj, node);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b, c; cin >> a >> b >> c;
        path[a].push_back(b);
        path[b].push_back(a);
        color[a][c].push_back(b);
        color[b][c].push_back(a);
    }

    for (int i = 1; i <= N; i++) {
        for (auto adj : color[i]) {
            if (SZ(adj.B) > 1) {
                for (int v : adj.B) {
                    if (bad[v] < 2) {
                        dfs(v, i);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        ans += !bad[i];
    }

    cout << ans << "\n";
    for (int i = 1; i <= N; i++) {
        if (!bad[i]) cout << i << "\n";
    }

    return 0;
}

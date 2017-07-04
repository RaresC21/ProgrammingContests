#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9
#define pb push_back
#define mp make_pair
#define MAX 400011

int N, M;
int color[MAX], temp[2][MAX];
vector<int> path[MAX];
vector<pair<int, int> > type[3];

void dfs(int node, int c) {
    if (color[node] != -1) return;
    color[node] = c;
    for (int adj : path[node]) {
        dfs(adj, 1 - c);
    }
}

int amnt = 0;
int dfs2(int node, int c, int indx) {
    if (temp[indx][node] != -1) return 0;
    amnt++;
    temp[indx][node] = c;
    int res = c;
    for (int adj : path[node]) {
        if (temp[indx][adj] == -1) {
            res += dfs2(adj, 1 - c, indx);
        }
    }
    return res;
}

bool check() {
    for (int i = 0; i < type[0].size(); i++) {
        if (color[type[0][i].first] != 0 || color[type[0][i].second] != 0) return false;
    }
    for (int i = 0; i < type[2].size(); i++) {
        if (color[type[2][i].first] != 1 || color[type[2][i].second] != 1) return false;
    }
    for (int i = 0; i < type[1].size(); i++) {
        if (!(color[type[1][i].first] ^ color[type[1][i].second])) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);

    // ifstream cin ("input.txt");

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, t; cin >> a >> b >> t;
        path[a].pb(b);
        path[b].pb(a);
        type[t].pb(mp(a, b));
    }
    for (int i = 1; i <= N; i++)
        color[i] = -2;

    for (int i = 0; i < type[0].size(); i++) {
        color[type[0][i].first] = color[type[0][i].second] = 0;
    }
    for (int i = 0; i < type[2].size(); i++) {
        color[type[2][i].first] = color[type[2][i].second] = 1;
    }

    int cnt = 0;
    for (int i = 0; i < type[1].size(); i++) {
        if (color[type[1][i].first] == -2) color[type[1][i].first] = -1, cnt++;
        if (color[type[1][i].second] == -2) color[type[1][i].second] = -1, cnt++;
    }

    for (int i = 1; i <= N; i++) {
        if (color[i] != -1) {
            for (int adj : path[i]) dfs(adj, 1 - color[i]);
        }
    }

    int cur = 0;
    for (int i = 1; i <= N; i++)
        if (color[i] == 1) cur++;

    memset(temp, -1, sizeof(temp));

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (color[i] == -1) {
            int c1 = dfs2(i, 0, 0);
            int c2 = dfs2(i, 1, 1);

            if (c1 > c2) {
                for (int k = 1; k <= N; k++) if (temp[1][k] != -1) { color[k] = temp[1][k]; temp[1][k] = -1; }
                ans += c2;
            } else {
                for (int k = 1; k <= N; k++) if (temp[0][k] != -1) { color[k] = temp[0][k]; temp[0][k] = -1; }
                ans += c1;
            }
        }
    }

    if (check()) {
        cout << ans + cur << "\n";
    } else {
        cout << "impossible\n";
    }

    return 0;
} 

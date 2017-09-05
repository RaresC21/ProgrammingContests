#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
bool leaf[MAX];
int amnt[MAX];
vector<int> path[MAX];

void dfs(int node, int par) {
    if (leaf[node]) return;
    if (path[node].size() > 2) return;
    leaf[node] = true;
    for (int adj : path[node]) {
        if (adj == par) continue;
        dfs(adj, par);
    }
}

int main() {

    int N; cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        path[a].push_back(b);
        path[b].push_back(a);
    }

    for (int i = 1; i <= N; i++) {
        if (path[i].size() <= 1) {
            dfs(i, i);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (leaf[i]) continue;
        for (int adj : path[i]) {
            if (leaf[adj]) continue;
            amnt[i] ++;
            if (amnt[i] > 2) {
                cout << "NO\n";
                return 0;
            }
        }
    }


    cout << "YES\n";

    return 0;
}
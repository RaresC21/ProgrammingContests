#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

#define pb push_back
#define MAX 2000006

struct Edge {
    int a, b;
    Edge() {}
    Edge(int a, int b) : a(a), b(b) {}
};

set<int> path[MAX];
bool met[MAX];
vector<int> v;
int pos = 0;
int circuit[MAX];
Edge edge[MAX];

void find_circuit(int node) {
    if (path[node].empty()) {
        circuit[pos] = node;
        pos++;
    } else {
        while (!path[node].empty()) {
            int indx = *path[node].begin();
            int adj = edge[indx].a;
            if (adj == node) adj = edge[indx].b;

            path[node].erase(indx);
            path[adj].erase(indx);
            find_circuit(adj);
        }
        circuit[pos] = node;
        pos++;
    }
}

void dfs(int node) {
    if (met[node]) return;
    met[node] = true;
    if (path[node].size() % 2 == 1) {
        v.pb(node);
    }
    for (int adj : path[node]) {
        dfs(edge[adj].a);
        dfs(edge[adj].b);
    }
}

int main() {

    int N, M; cin >> N >> M;
    int cnt = 0;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        path[a].insert(cnt);
        path[b].insert(cnt);
        edge[cnt] = Edge(a, b);
        cnt++;
    }

    for (int i = 1; i <= N; i++) {
        if (path[i].size() == 0) continue;
        if (met[i]) continue;
        v.clear();
        dfs(i);

        for (int k = 2; k < v.size(); k += 2) {
            path[v[k]].insert(cnt);
            path[v[k + 1]].insert(cnt);
            edge[cnt] = Edge(v[k], v[k + 1]);
            cnt++;
        }
        if (v.size()) {
            find_circuit(v[0]);
        }
        else
            find_circuit(i);
    }

    cout << pos << "\n";
    for (int i = 0; i < pos; i++)
        cout << circuit[i] << " ";
    cout << "\n";

    return 0;
}
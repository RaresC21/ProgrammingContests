#include <bits/stdc++.h>
using namespace std;

#define MAX 1000006
int val[MAX];
vector<int> adj[MAX];

int main() {

    int N, M;
    while (cin >> N >> M) {
	for (int i = 0; i < MAX; i++)
	    adj[i].clear();
	for (int i = 1; i <= N; i++) {
	    int v; cin >> v;
	    adj[v].push_back(i);
	}
	for (int i = 0; i < M; i++) {
	    int v, k; cin >> k >> v;
	    if (adj[v].size() < k) cout << "0\n";
	    else cout << adj[v][k - 1] << "\n";
	}
    }
    
    return 0;
}

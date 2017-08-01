#include <bits/stdc++.h>
using namespace std;


const int N = 1005;
const int M = 10005;

int t, n, m;

/*
	Hopcroft Karp Max Matching in O(E * sqrt(V))
	N = Number of Nodes, M = Number of Edges
	n1 = Size of left partite, n2 = Size of right partite
	Nodes are numbered from [0, n1 - 1] and [0, n2 - 1]

	init(n1, n2) declares the two partite sizes and resets arrays
	addEdge(x, y) adds an edge between x in left partite and y in right partite
	maxMatching() returns the maximum matching

	Maximum Matching = Minimum Vertex Cover (Konig's Theorem)
	N - Maximum Matching = Maximal Independent Set
*/


int n1, n2, edges, last[N], previous[M], head[M];
int matching[N], dist[N], Q[N];
bool used[N], vis[N];

inline void init(int _n1, int _n2) {
    n1 = _n1;
    n2 = _n2;
    edges = 0;
    fill(last, last + n1, -1);
}

inline void addEdge(int u, int v) {
    head[edges] = v;
    previous[edges] = last[u];
    last[u] = edges++;
}

inline void bfs() {
    fill(dist, dist + n1, -1);
    int sizeQ = 0;
    for(int u = 0; u < n1; ++u){
	if(!used[u]){
	    Q[sizeQ++] = u;
	    dist[u] = 0;
	}
    }
    for(int i = 0; i < sizeQ; i++){
	int u1 = Q[i];
	for(int e = last[u1]; e >= 0; e = previous[e]){
	    int u2 = matching[head[e]];
	    if(u2 >= 0 && dist[u2] < 0){
		dist[u2] = dist[u1] + 1;
		Q[sizeQ++] = u2;
	    }
	}
    }
}

inline bool dfs(int u1) {
    vis[u1] = true;
    for(int e = last[u1]; e >= 0; e = previous[e]){
	int v = head[e];
	int u2 = matching[v];
	if(u2 < 0 || !vis[u2] && dist[u2] == dist[u1] + 1 && dfs(u2)){
	    matching[v] = u1;
	    used[u1] = true;
	    return true;
	}
    }
    return false;
}

inline int maxMatching() {
    fill(used, used + n1, false);
    fill(matching, matching + n2, -1);
    for(int res = 0; ;){
	bfs();
	fill(vis, vis + n1, false);
	int f = 0;
	for(int u = 0; u < n1; ++u)
	    if(!used[u] && dfs(u))
		++f;
	if(!f) return res;
	res += f;
    }
}


#define mp make_pair
#define pb push_back

const int SUIT = 4;
const int RANK = 13;
bool A[RANK + 1][SUIT + 1];
vector<pair<int, int> > p1, p2;

int main() {
    
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
	int rank; cin >> rank;
	char suit; cin >> suit;
	if (suit == 'C') suit = 1;
	else if (suit == 'D') suit = 2;
	else if (suit == 'H') suit = 3;
	else suit = 4;

	A[rank][suit] = true;
	p1.pb(mp(rank, suit));
    }
    
    for (int i = 1; i <= RANK; i++) {
	for (int k = 1; k <= SUIT; k++) {
	    if (!A[i][k])
		p2.pb(mp(i, k));
	}
    }

    if (p1.size() < 26) {
	cout << "impossible\n";
	return 0;
    } else if (p1.size() > 26) {
	cout << "possible\n";
	return 0;
    }

    for (int i = 0; i < p1.size(); i++) {
	for (int k = 0; k < p2.size(); k++) {
	    if (p2[k].second != p1[i].second) continue;
	    if (p2[k].first >= p1[i].first) continue;

	    init(52, 52);

	    for (int a = 0; a < p1.size(); a++) {
		if (a == i) continue;
		for (int b = 0; b < p2.size(); b++) {
		    if (b == k) continue;
		    if (p1[a].second != p2[b].second) {
			addEdge(a, b);
		    }
		}
	    }
	    
	    int match = maxMatching();
	    if (match == p2.size() - 1) {
		cout << "possible\n";
		return 0;
	    }
	}
    }

    cout << "impossible\n";
    
    return 0;
}

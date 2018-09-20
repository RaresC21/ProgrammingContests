#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define VI vector<int>
#define VLL vector<LL>
#define mp make_pair
#define pb push_back
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
#define A first
#define B second
#define io ios_base::sync_with_stdio(false)

const int INF = 1e9;
const int MAX = 10004;

int N, M;
int root;
int edge_count = 0, root_children = 0;
int dfs_num[MAX], dfs_low[MAX], dfs_parent[MAX];
vector<int> path[MAX];

struct Edge {
    int a, b;
    Edge(int a, int b) : a(a), b(b) {}
};
vector<Edge> bridge;
vector<int> articulation;

map<PII, bool> cut;
bool met[MAX];

// find cut edges and vertices
void dfs(int cur) {
  dfs_low[cur] = dfs_num[cur] = edge_count ++;
  for (int v : path[cur]) {
    if (dfs_num[v] == -1) { // unvisited
      dfs_parent[v] = cur;
      if (cur == root) root_children++;
      
      dfs(v);
      
      if (dfs_low[v] >= dfs_num[cur]) {
	articulation.push_back(cur);
      }
      if (dfs_low[v] > dfs_num[cur]) {
	bridge.push_back(Edge(v, cur));
      }
      dfs_low[cur] = min(dfs_low[cur], dfs_low[v]);
      
    } else if (v != dfs_parent[cur]) {
      dfs_low[cur] = min(dfs_low[cur], dfs_num[v]);
    }
  }
}

int ans = 0;
void reach(int node) {
  if (met[node]) return;
  met[node] = true;
  ans++;
  for (int adj : path[node]) {
    if (cut.count(mp(node, adj))) continue;
    reach(adj);
  }
}

int main() {
  io;

  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    path[a].pb(b);
    path[b].pb(a);
  }
  memset(dfs_num, -1, sizeof(dfs_num));
  root = 0;
  dfs(0);
  
  for (auto e : bridge) {
    cut[mp(e.a, e.b)] = cut[mp(e.b, e.a)] = true;
  }
  
  reach(0);
  cout << ans << "\n";
  
  return 0;
}

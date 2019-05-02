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
const int MAX = 16003;

VI path[MAX];
int sz[MAX];
int sub[MAX];

int dfs(int node, int par) {

  int m = 0;
  int all = 0;
  for (int adj : path[node]) {
    if (adj == par) continue;
    int cur = dfs(adj, node);
    m = max(m, cur);
    all += cur;
  }

  sz[node] = m;
  sub[node] = all;
  return all + 1;
}

int main() {
  io;

  int N; cin >> N;
  set<int> all;
  vector<PII> edge;
  for (int i = 0; i < N-1; i++) {
    int a, b; cin >> a >> b;
    all.insert(a);
    all.insert(b);
    edge.pb(mp(a, b));
  }

  map<int, int> conv, back;
  int cnt = 1;
  for (int a : all) {
    conv[a] = cnt;
    back[cnt] = a;
    cnt++;
  }
  
  
  for (auto e : edge) {
    path[conv[e.A]].pb(conv[e.B]);
    path[conv[e.B]].pb(conv[e.A]);
  }
  
  dfs(1, 1);

  for (int i = 1; i <= N; i++) {
    sz[i] = max(sz[i], N - sub[i] - 1);
  }
  
  int best = N;
  for (int i = 1; i <= N; i++) {
    best = min(best, sz[i]);
  }

  VI ans;
  for (int i = 1; i <= N; i++) {
    if (sz[i] == best) {
      ans.pb(back[i]);
    }
  }
  sort(ans.begin(), ans.end());
  
  cout << best << " " << ans.size() << "\n";
  for (int a : ans) cout << a << " ";
  cout << "\n";
  
  return 0;
}

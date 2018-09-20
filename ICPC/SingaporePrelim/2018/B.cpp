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
const int MAX = 1e6 + 10;

int component[MAX];
VI edge[MAX];

void dfs(int node, int c) {
  if (component[node] != -1) return;
  component[node] = c;
  for (int adj : edge[node]) {
    dfs(adj, c);
  }
}

int main() {
  io;

  int N, K; cin >> N >> K;
  for (int i = 0; i < K; i++) {
    int a, b; cin >> a >> b;
    a = N - a + 1;
    b = N - b + 1;
    edge[a].pb(b);
    edge[b].pb(a);
  }

  int c = 1;
  memset(component, -1, sizeof(component));
  for (int i = 1; i <= N; i++) {
    if (component[i] == -1) {
      dfs(i, c++);
    }
  }

  for (int i = 1; i <= N; i++) {
    int want = N - i + 1;
    if (component[want] != component[i]) {
      cout << "NO\n";
      return 0;
    }
  }

  cout << "YES\n";
  
  return 0;
}

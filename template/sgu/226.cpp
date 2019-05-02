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
const int MAX = 203 * 4 + 10;
int N, M;
vector<int> adj[MAX];
int col[MAX][MAX];
bool met[MAX];
vector<int> path[MAX];

int main() {
  io;

  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int a, b, c; cin >> a >> b >> c;
    adj[a].pb(b);
    col[a][b] = c;
  }

  for (int i = 1; i <= N; i++) {
    for (int c = 1; c <= 3; c++) {
      for (int a : adj[i]) {
	if (c == col[i][a]) continue;
	path[4*i + c].pb(4*a + col[i][a]);
      }
    }
  }

  for (int a : adj[1]) {
    path[4*1 + 0].pb(4*a + col[1][a]);
  }

  queue<PII> q;
  q.push(mp(4, 0));
  while (q.size()) {
    auto cur = q.front();
    q.pop();

    if (met[cur.A])  continue;
    met[cur.A] = true;
    if (cur.A > 4*N) {
      cout << cur.B << "\n";
      return 0;
    }

    for (int a : path[cur.A]) {
      q.push(mp(a, cur.B + 1));
    }
  }

  cout << "-1\n";
  
  return 0;
}

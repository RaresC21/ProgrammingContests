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

const int INF = (1LL << 31) - 1;
const int MAX = 50004;
int par[MAX];
vector<int> child[MAX];
set<int> leaves[MAX];
int sol[MAX], best[MAX];
int val[MAX];

int solve(int node) {

  if (child[node].size() == 0) {
    leaves[node].insert(val[node]);
    best[node] = node;
    return INF;
  }

  int ans = INF;
  int indx = -1;
  for (int c : child[node]) {
    ans = min(ans, solve(c));
    if (indx == -1 || leaves[best[c]].size() > leaves[best[indx]].size()) {
      indx = c;
    }
  }

  for (int c : child[node]) {
    if (c == indx) continue;
    for (int x : leaves[best[c]]) {

      auto it = leaves[best[indx]].lower_bound(x);
      if (it != leaves[best[indx]].end()) {
	ans = min(ans, abs(*it - x));
      }
      if (it != leaves[best[indx]].begin()) {
	--it;
	ans = min(ans, abs(*it - x));
      }
      
      leaves[best[indx]].insert(x);
    }
  }
  best[node] = best[indx];
  return sol[node] = ans;
}

int main() {
  io;

  int N, M; cin >> N >> M;
  for (int i = 2; i <= N; i++) {
    cin >> par[i];
    child[par[i]].pb(i);
  }

  for (int i = N-M+1; i <= N; i++) {
    cin >> val[i];
  }
  
  solve(1);

  for (int i = 1; i <= N-M; i++) {
    cout << sol[i] << " ";
  }
  cout << "\n";
  
  return 0;
}

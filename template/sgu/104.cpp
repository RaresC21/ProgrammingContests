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
const int MAX = 101;

int val[MAX][MAX];;
int dp[MAX][MAX], best[MAX][MAX];

int main() {
  io;

  int F, V; cin >> F >> V;
  for (int i = 1; i <= F; i++) {
    for (int k = 1; k <= V; k++) {
      cin >> val[i][k];
    }
  }

  for (int i = 1; i <= F; i++) {
    for (int k = 1; k <= V; k++) {
      dp[i][k] = -INF;
    }
  }
  for (int k = 1; k <= V; k++)
    dp[1][k] = val[1][k];

  for (int i = 2; i <= F; i++) {
    for (int k = i; k <= V; k++) {
      for (int j = i - 1; j < k; j++) {
	if (dp[i - 1][j] + val[i][k] > dp[i][k]) {
	  dp[i][k] = dp[i - 1][j] + val[i][k];
	  best[i][k] = j;
	}
      }
    }
  }

  int ans = -INF;
  int s = -1;
  for (int k = F; k <= V; k++) {
    if (dp[F][k] > ans) {
      ans = dp[F][k];
      s = k;
    }
  }

  cout << ans << "\n";
  vector<int> sol;
  while (s) {
    sol.pb(s);
    s = best[F--][s];
  }

  for (int i = sol.size() - 1; i >= 0; i--)
    cout << sol[i] << " ";
  cout << "\n";
  
  return 0;
}

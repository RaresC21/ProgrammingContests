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

int val[205];
bool dp[10004];

int main() {
  io;

  int N, X; cin >> N >> X;
  for (int i = 1; i <= N; i++)
    cin >> val[i];

  int ans = 0;
  VI sol;
  for (int a = 1; a <= N; a++) {
    int t = val[a];
    val[a] = 0;
    memset(dp, 0, sizeof(dp));

    dp[0] = true;
    for (int i = 1; i <= N; i++) {
      for (int k = X; k >= 1; k--) {
	if (k - val[i] >= 0 && dp[k - val[i]])
	  dp[k] = true;
      }
    }

    if (!dp[X]) {
      sol.pb(t);
      ans++;
    }
    
    val[a] = t;
  }

  cout << ans << "\n";
  if (ans) {
    sort(sol.begin(), sol.end());
    for (int a : sol)
      cout << a << " ";
    cout << "\n";
  }
  
  return 0;
}

/*
  Acolo este ţara mea,
  Şi neamul meu cel românesc!
  Acolo eu să mor aş vrea,
  Acolo vreau eu să trăiesc!
*/

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
const int MAX = 55;

int N, M, K;
int dp[32][32][52];

int solve(int r, int c, int k) {
  if (dp[r][c][k] != -1) return dp[r][c][k];
  if (r*c == k) return 0;
  if (k == 0) return 0;

  int ans = INF;
  for (int i = 1; i < r; i++) { // cut along column
    for (int cur = 0; cur <= k; cur++) {
      // use cur for left half. k-cur for other half

      if (i * c >= cur && (r-i) * c >= k-cur) {
	ans = min(ans, solve(i, c, cur) + solve(r - i, c, k - cur) + c*c);
      }
    }
  }

  for (int i = 1; i < c; i++) { // cut along row
    for (int cur = 0; cur <= k; cur++) {

      if (i * r >= cur && (c-i) * r >= k-cur) {
	ans = min(ans, solve(r, i, cur) + solve(r, c - i, k - cur) + r*r);
      }
    }
  }

  return dp[r][c][k] = ans;
}

int main() {

  memset(dp, -1, sizeof(dp));
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &N, &M, &K);

    cout << solve(N, M, K) << "\n";
  }

  
  return 0;
}

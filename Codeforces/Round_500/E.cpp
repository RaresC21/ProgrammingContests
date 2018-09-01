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
const int MAX = 5005;

int h[MAX];
PII dp[MAX][MAX][2];

int main() {
  io;

  int N; cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> h[i];
  }

  for (int i = 0; i <= N; i++)
    for (int k = 0; k <= N; k++)
      dp[i][k][1] = dp[i][k][0] = mp(INF, -INF);
  dp[0][0][0].A = 0;
  
  for (int i = 1; i <= N; i++) {
    for (int k = 0; k <= (i+1)/2; k++) {

      // don't build
      LL lower_cur = 0;
      if (dp[i-1][k][1].B <= h[i]) {
	lower_cur = h[i] - dp[i-1][k][1].B + 1;
      }
      
      if (dp[i-1][k][0].A < dp[i-1][k][1].A + lower_cur) {
	dp[i][k][0] = mp(dp[i-1][k][0].A, h[i]);
      } else {
	int xx = h[i];
	if (lower_cur != 0) xx = dp[i-1][k][1].B - 1;
	dp[i][k][0] = mp(dp[i-1][k][1].A + lower_cur, xx);
      }

      // build here -> can't build on previous
      if (k >= 1) {
	int prev_height = dp[i-1][k-1][0].B;
	int tmp = 0;
	if (prev_height >= h[i]) tmp = prev_height - h[i] + 1;
	dp[i][k][1] = mp(dp[i-1][k-1][0].A + tmp, h[i]);
      }

    }
  }

  for (int k = 1; k <= (N + 1) / 2; k++) {
    cout << min(dp[N][k][0].A, dp[N][k][1].A) << " ";
  }
  cout << "\n";
  
  return 0;
}

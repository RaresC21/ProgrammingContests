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
const int MAX = 111;

int grid[MAX][MAX];

int main() {
  io;

  int N, M; cin >> N >> M;
  int amnt = 0;
  for (int i = 1; i <= N; i++) {
    string s; cin >> s;
    for (int k = 1; k <= M; k++) {
      grid[i][k] = s[k-1] - '0';
      if (grid[i][k] != 0) amnt++;
    }
  }

  int ans = amnt * 2;
  for (int i = 1; i <= N; i++) {
    for (int k = 1; k <= M; k++) {

      for (int a = -1; a <= 1; a++) {
	for (int b = -1; b <= 1; b++) {
	  if (abs(a) + abs(b) == 1) {
	    ans += max(0, grid[i][k] - grid[i + a][k + b]);
	  }
	}
      }
      
    }
  }

  cout << ans << "\n";
  
  return 0;
}

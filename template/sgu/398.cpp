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
const int MAX = 100;

bool f[MAX][MAX];

int main() {
  io;

  int N; cin >> N;
  int X; cin >> X;
  for (int i = 1; i <= N; i++) {
    int d; cin >> d;
    for (int k = 0; k < d; k++) {
      int x; cin >> x;
      f[i][x] = f[x][i] = true;
    }
  }


  VI ans;
  for (int k = 1; k <= N; k++) {
    if (k == X) continue;
    if (f[X][k]) continue;
    
    bool ff = false;
    for (int j = 1; j <= N; j++) {
      if (X == j || k == j) continue;
      if (f[X][j] && f[k][j]) {
	ff = true;
      }
    }
    
    if (ff) {
      ans.pb(k);
    }
  }

  cout << ans.size() << "\n";
  if (ans.size()) {
    for (int a : ans) cout << a << "\n";
  }
  
  return 0;
}

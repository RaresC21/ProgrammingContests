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
const int MAX = 100005;

int X[MAX], Y[MAX];
int d[MAX];

int main() {
  io;

  int N, M; cin >> N >> M;

  vector<PII> edge;
  for (int i = 0; i < M; i++) {
    cin >> X[i] >> Y[i];
    d[X[i]]++;
    d[Y[i]]++;
  }

  int ans = 0;
  for (int i = 0; i < M; i++) {
    ans += d[X[i]] +d[Y[i]];
  }

  cout << ans << "\n";
  
  return 0;
}

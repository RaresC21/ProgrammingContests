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

int main() {
  io;

  int N; cin >> N;
  VI v(2*N);
  for (int i = 0; i < 2*N; i++) {
    cin >> v[i];
  }

  sort(v.begin(), v.end());

  LL ans = 1LL * (v[N - 1] - v[0]) * (v[2*N - 1] - v[N]);
  ans = min(ans, 1LL * (v[N] - v[0]) * (v[2*N - 1] - v[N - 1]));

  int dx = v[2*N - 1] - v[0];
  for (int i = 1; i <= N - 1; i++) {
    int dy = v[i + N - 1] - v[i];
    ans = min(ans, 1LL * dx * dy);
  }

  cout << ans << "\n";
  
  return 0;
}
